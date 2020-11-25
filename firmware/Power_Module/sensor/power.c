// Power.c  (version 2.0 - Pierre)

#include "power.h"
#include <math.h>
#include "../system/adcc.h"

/* == DEFINE == */

#ifdef SENSOR_TYPE
#if (SENSOR_TYPE == POWER)
#warning "Compiling for Power sensor"

#define SOL_VOLT   0x13
#define BAT_VOLT   0x14

//#define DEBUG

#define ENABLE  1
#define DISABLE 0

/* == FUNCTIONS PROTOTYPES == */

void ADC_Init(void);
void WDT_Init(void);
void generateIntPower(void);
void measure(void);
void ledBlink(void);
void enterSleep(void);

/* == GLOBAL VARIABLES == */

bool PollingMeasurement = false;
bool MeasurementRunning = false;
volatile uint8_t measurementData[2* M_NR]; // 2*M_NR = 6
float AfterMeasure = 0.0;

uint16_t voltageBatMeasured = 0;
uint16_t voltageLDRMeasured = 0;
uint16_t tempValue = 0;
float floatVoltageBatMeasured = 0.0;
float floatVoltageLDRMeasured = 0.0;

bool batThresholdEnabled = false;
bool alertThreshold = false;
uint16_t batThresholdLevel = 0;
float floatBatThresholdLevel = 0.0;


/* == FUNCTIONS ==*/

void ADC_Init(void){
	// Enable Fixed voltage reference with voltage of 2.048 V
    FVRCON = 0x82;
    // Enable ADC peripheral
    PMD3bits.ADCMD = 0; 		
    // set the ADCC to the options selected in the User Interface
    // ADLTH 0; 
    ADLTHL = 0x00;
    // ADLTH 0; 
    ADLTHH = 0x00;
    // ADUTH 0; 
    ADUTHL = 0x00;
    // ADUTH 0; 
    ADUTHH = 0x00;
    // ADSTPT 0; 
    ADSTPTL = 0x00;
    // ADSTPT 0; 
    ADSTPTH = 0x00;
    // ADACC 0; 
    ADACCU = 0x00;
    // ADRPT 0; 
    ADRPT = 0x00;
    // ADPCH ANA0; 
    ADPCH = 0x00;
    // ADACQ 0; 
    ADACQL = 0x00;
    // ADACQ 0; 
    ADACQH = 0x00;
    // ADCAP Additional uC disabled; 
    ADCAP = 0x00;
    // ADPRE 0; 
    ADPREL = 0x00;
    // ADPRE 0; 
    ADPREH = 0x00;
    // ADDSEN disabled; ADGPOL digital_low; ADIPEN disabled; ADPPOL Vss; 
    ADCON1 = 0x00;
    // ADCRS 0; ADMD Basic_mode; ADACLR disabled; ADPSIS RES; 
    ADCON2 = 0x00;
    // ADCALC First derivative of Single measurement; ADTMD disabled; ADSOI ADGO not cleared; 
    ADCON3 = 0x00;
    // ADMATH registers not updated; 
    ADSTAT = 0x00;
    // ADNREF VSS; ADPREF FVR; 
    ADREF = 0x03;
    // ADACT disabled; 
    ADACT = 0x00;
    // ADCS FOSC/16; 
    ADCLK = 0x00;
    // ADGO stop; ADFM right; ADON enabled; ADCS FOSC/ADCLK; ADCONT disabled; 
    ADCON0 = 0x84;
    
    FVRCON = 0x00; // Disable fixed voltage reference
}

void WDT_Init(void){
    // Config WatchDog Timer

	WDTCON0 = 0x20; // 64 second period (set to 0x1C for 16 s)
	WDTCON1 = 0x07; // LFINTOSC, window 100%
    WDTCON0bits.SEN = 1; // enable WDT
}

void generateIntPower(void){
	READY_SetLow();
	__delay_ms(1);
	READY_SetHigh();
}

void measure(void){
	// Enable Fixed voltage reference with voltage of 2.048 V
    FVRCON = 0x82;
	MeasurementRunning = true;
	
	SOL_MEAS_EN_SetHigh();                              // Enable loadswitch to measure voltage
    
    __delay_ms(10);                                     // Delay for settling voltages

    ADCC_GetSingleConversion(SOL_VOLT);                 // first measurement afte rreset seems to be fixed and need to be rejected
    voltageLDRMeasured = ADCC_GetSingleConversion(SOL_VOLT);
   
    tempValue = ADCC_GetSingleConversion(SOL_VOLT);
    if(tempValue < voltageLDRMeasured){                         // To make sure it is the lowest/ stable voltage that is captured
        voltageLDRMeasured = tempValue;
    }
    floatVoltageLDRMeasured = ((float)voltageLDRMeasured /4096) * 2.048 * ((10+10)/10);   // Convert ADC value to voltage (Resistor divider)
    
    SOL_MEAS_EN_SetLow();                               // Disable loadswitch to measure voltage
    BAT_MEAS_EN_SetHigh();                              // Enable loadswitch to measure voltage
    
    __delay_ms(10);                                     // Delay for settling voltages
    
    ADCC_GetSingleConversion(BAT_VOLT); 
    voltageBatMeasured = ADCC_GetSingleConversion(BAT_VOLT);
    
    floatVoltageBatMeasured = ((float)voltageBatMeasured /4096) * 2.048 * ((10+4.5)/4.5);   // Convert ADC value to voltage (Resistor divider)

    BAT_MEAS_EN_SetLow();                               // Disable loadswitch to measure voltage

	
	if(floatVoltageBatMeasured < floatBatThresholdLevel){
		alertThreshold = true;
	}

    // prepare data for I2C transmission: multiply by 600
    uint16_t databatvoltage = (uint16_t)(round(floatVoltageBatMeasured * 600));
    uint16_t datasolvoltage = (uint16_t)(round(floatVoltageLDRMeasured * 600));
      
    measurementData[0] = (uint8_t)(databatvoltage>>8);
    measurementData[1] = (uint8_t)(databatvoltage);

    measurementData[2] = (uint8_t)(datasolvoltage>>8);
    measurementData[3] = (uint8_t)(datasolvoltage);
   
	MeasurementRunning = false;
	FVRCON = 0x00; // Disable fixed voltage reference
}

void ledBlink(void){
	// startup animation
    LED0_SetHigh();
    __delay_ms(100);
    LED0_SetLow();
    __delay_ms(100);
    LED0_SetHigh();
    __delay_ms(100);
    LED0_SetLow();
    __delay_ms(100);
    LED0_SetHigh();
    __delay_ms(100);
    LED0_SetLow();
    __delay_ms(500);
    
    LED1_SetHigh();
    __delay_ms(100);
    LED1_SetLow();
    __delay_ms(100);
    LED1_SetHigh();
    __delay_ms(100);
    LED1_SetLow();
    __delay_ms(100);
    LED1_SetHigh();
    __delay_ms(100);
    LED1_SetLow();
}

void enterSleep(void){
	CPUDOZEbits.IDLEN = 0; // make sure PIC is not in doze mode before going to sleep   
    NOP();
    SLEEP(); 				// enter sleep
    NOP();
    NOP();
}

/* == API FUNCTIONS == */

void Power_Init(void){
	
	// Enable gpio clock
	PMD0bits.IOCMD = 0; 		// TO DO : Check if it is necessary
    
    // Enable FVR module
    PMD0bits.FVRMD = 0;         
	
	// Config ADC
	ADC_Init();
	
	// Config Interrupt (PIC -> MotherBoard)
	READY_SetDigitalMode();
	READY_SetDigitalOutput();
    READY_SetHigh();
	
	// Config LEDs
	LED0_SetDigitalMode();
	LED1_SetDigitalMode();
	LED0_SetDigitalOutput();
    LED1_SetDigitalOutput();
	LED0_SetLow();
    LED1_SetLow();
	
	// Config Measures (Solar Panel and Battery) 
	// Enabling
	SOL_MEAS_EN_SetDigitalMode();
    BAT_MEAS_EN_SetDigitalMode();
	SOL_MEAS_EN_SetDigitalOutput();
    BAT_MEAS_EN_SetDigitalOutput();
	SOL_MEAS_EN_SetLow();
    BAT_MEAS_EN_SetLow();
	// Measures
	SOL_VOLT_SetDigitalInput();
	BAT_VOLT_SetDigitalInput();
    SOL_VOLT_SetAnalogMode();
	BAT_VOLT_SetAnalogMode();
	
	// Confirm Init
	ledBlink();
	
#ifdef DEBUG
	PollingMeasurement = true;
#endif
}

void Power_Measure(void){
	PollingMeasurement = true;
}

void Power_Loop(void){ 
	// Polling
	if(PollingMeasurement && !MeasurementRunning){
		PollingMeasurement = false;
		// WDT is turned OFF -> Threshold disabled
		if(WDTCON0bits.SEN == 0){
            LED0_SetHigh();
			measure();
			generateIntPower();
            
            measurementData[4] = 0x00;
            measurementData[5] = 0x02;
            
            LED0_SetLow();
		}  
		else if(WDTCON0bits.SEN == 1){  // WDT is turned ON  -> Threshold enabled
			WDTCON0bits.SEN = 0; // disable WDT
            LED0_SetHigh();
			LED1_SetHigh();
			
            measure();
			generateIntPower();
            
            measurementData[4] = 0x00;
            measurementData[5] = 0x04;
            
            LED0_SetLow();
			LED1_SetLow();
            
			
			CLRWDT();
			WDTCON0bits.SEN = 1; // enable WDT
		}
	}
	else if(STATUSbits.nTO == 0){     // WatchDog Time-Out
		WDTCON0bits.SEN = 0; // disable WDT
		
        LED1_SetHigh();
        
        if(batThresholdEnabled && alertThreshold){
			alertThreshold = false;
            measure();
			generateIntPower();
		}
        
        measurementData[4] = 0x00;
        measurementData[5] = 0x06;
        
        LED1_SetLow();
			
		CLRWDT();
		WDTCON0bits.SEN = 1; // enable WDT
	}
	else{
		enterSleep();
	} 
}

void Power_GetData(uint8_t * data, uint8_t * length){
	*length = 6; 	// this is fixed (M_NR = 2)
    data[0] = measurementData[0];
    data[1] = measurementData[1];
	
	data[2] = measurementData[2];
	data[3] = measurementData[3];
    
    data[4] = measurementData[4];
	data[5] = measurementData[5];
}

void Power_SetThreshold(uint8_t metric, uint8_t * thresholdData){
	if(metric == 0){
		batThresholdEnabled = thresholdData[0];
        batThresholdLevel = (uint16_t)((thresholdData[3]<<8) | thresholdData[4]);
        floatBatThresholdLevel = (float) batThresholdLevel/600;
	}
    
    if(batThresholdEnabled && WDTCON0bits.SEN == 0){        //WDT initialy OFF -> INIT WDT      
        WDT_Init();
    }
    else if(batThresholdEnabled && WDTCON0bits.SEN == 1){   //WDT initialy ON  -> RESET and TURN ON
        WDTCON0bits.SEN = 0;
        CLRWDT();
        WDTCON0bits.SEN = 1;
    }
    else{                                                   //WDT initialy OFF or ON -> DISABLE 
        WDTCON0bits.SEN = 0;
    }
}

#endif
#endif