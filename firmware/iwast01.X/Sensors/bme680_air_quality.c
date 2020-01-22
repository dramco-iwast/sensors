/*
 * File:   bme680_air_quality.c
 * Author: sarah
 *
 * Created on November 10, 2019, 3:48 PM
 */

#include "bme680_air_quality.h"
#include "bme680.h"
#include "bme680_defs.h"
#include "../mcc_generated_files/spi2.h"

#ifdef SENSOR_TYPE
#if (SENSOR_TYPE == BME680)
#warning "Compiling for BME680"

#define D_LEN (M_NR * 2)
uint8_t measurementData[D_LEN] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

#define METRIC_TEMPERATURE  0
#define METRIC_PRESSURE     1
#define METRIC_IAQ          2
#define METRIC_HUMIDITY     3
// threshold settings for each metric
// temperature
 uint8_t tempTreshEnabled = 0;
 uint16_t tempTLH = 0;
 uint16_t tempTLL = 0;
 bool tempTLHExceeded = false;
 bool tempTLLExceeded = false;
// atm. pressure
 uint8_t presTreshEnabled = 0;
 uint16_t presTLH = 0;
 uint16_t presTLL = 0;
 bool presTLHExceeded = false;
 bool presTLLExceeded = false;
// air quality index
 uint8_t iaqTreshEnabled = 0;
 uint16_t iaqTLH = 0;
 uint16_t iaqTLL = 0;
 bool iaqTLHExceeded = false;
 bool iaqTLLExceeded = false;
// humidity
 uint8_t humiTreshEnabled = 0;
 uint16_t humiTLH = 0;
 uint16_t humiTLL = 0;
 bool humiTLHExceeded = false;
 bool humiTLLExceeded = false;
 
uint8_t rslt;
BME680_t gas_sensor;

bool init = true;
bool polledMeasurement = false;
bool measurementRunning = false;

void generateInt(void);
void measure(void);

void delay_wrapper(uint32_t ms){
    uint32_t c = 0;
    while(c<ms){
        __delay_ms(1);
        c++;
    }
}

int8_t spi_read(uint8_t dev_id, uint8_t reg_addr, uint8_t *reg_data, uint16_t len){
    int8_t rslt = 0; /* Return 0 for Success, non-zero for failure */
    uint8_t readDummy;
    
    CS1_SetLow();
    
    readDummy = SPI2_Exchange8bit(reg_addr);
    
    while(len--){
        *reg_data = SPI2_Exchange8bit(SPI2_DUMMY_DATA);
        reg_data++;
    }
    
   
    CS1_SetHigh();
    
    return rslt;
}

int8_t spi_write(uint8_t dev_id, uint8_t reg_addr, uint8_t *reg_data, uint16_t len){
    int8_t rslt = 0; /* Return 0 for Success, non-zero for failure */
    uint8_t readDummy;
    
    CS1_SetLow();
    
    readDummy = SPI2_Exchange8bit(reg_addr);
    
    while(len--){
        readDummy = SPI2_Exchange8bit(*reg_data);
        reg_data++;
    }

    CS1_SetHigh();
    
    return rslt;
}

void BME680_Init(void){
     /**
    LATx registers
    */
    LATA = 0x14;
    LATB = 0x00;
    LATC = 0x80;
    /**
    TRISx registers
    */
    TRISA = 0x2B;
    TRISB = 0xF0;
    TRISC = 0x1F;
    /**
    ANSELx registers
    */
    ANSELC = 0x2F;
    ANSELB = 0x50;
    ANSELA = 0x37;
    /**
    WPUx registers
    */
    WPUB = 0x00;
    WPUA = 0x00;
    WPUC = 0x00;
    /**
    ODx registers
    */
    ODCONA = 0x00;
    ODCONB = 0x00;
    ODCONC = 0x00;
    /**
    SLRCONx registers
    */
    SLRCONA = 0x37;
    SLRCONB = 0xF0;
    SLRCONC = 0xFF;
    /**
    INLVLx registers
    */
    INLVLA = 0x3F;
    INLVLB = 0xF0;
    INLVLC = 0xFF;

    // Enable IOCI interrupt 
    PIE0bits.IOCIE = 1; 
	
    //SSP1CLKPPS = 0x0F;   //RB7->MSSP1:SCL1;    
    SSP2DATPPS = 0x14;   //RC4->MSSP2:SDI2;    
    //RB7PPS = 0x13;   //RB7->MSSP1:SCL1;    
    //RB5PPS = 0x14;   //RB5->MSSP1:SDA1;    
    RC5PPS = 0x16;   //RC5->MSSP2:SDO2;    
    RC6PPS = 0x15;   //RC6->MSSP2:SCK2;    
    //SSP1DATPPS = 0x0D;   //RB5->MSSP1:SDA1;    
    SSP2CLKPPS = 0x16;   //RC6->MSSP2:SCK2;    
    
    // initialize timer for periodic measurements
    // setup watchdog (WWDT))
    WDTCON0 = 0x1A; // 1 second period
    WDTCON1 = 0x07; // LFINTOSC, window 100%
    
    USER_LED_SetDigitalOutput();
    //USER_LED_SetLow();
    
    // sensor interface init
    SPI2_Initialize();
    
     //--------------- SPI example ------------------------
    
    //struct bme680_dev gas_sensor;
    
    /* You may assign a chip select identifier to be handled later */
    gas_sensor.dev_id = 0;
    gas_sensor.intf = BME680_SPI_INTF;
    gas_sensor.read = &spi_read; //pointer int8_t
    gas_sensor.write = &spi_write;
    gas_sensor.delay_ms = &delay_wrapper;
    /* amb_temp can be set to 25 prior to configuring the gas sensor 
     * or by performing a few temperature readings without operating the gas sensor.
     */
    gas_sensor.amb_temp = 25;

    //int8_t rslt = BME680_OK;
    rslt = BME680_OK;
    rslt = bme680_init(&gas_sensor);
    
    if (rslt != BME680_OK){
        init = false;
    }
    
    //----------------- example configuring sensor in forced mode -------------------
    uint8_t set_required_settings;

    /* Set the temperature, pressure and humidity settings */
    gas_sensor.tph_sett.os_temp = BME680_OS_8X;
    gas_sensor.tph_sett.os_hum = BME680_OS_2X;
    gas_sensor.tph_sett.os_pres = BME680_OS_4X;
    
    gas_sensor.tph_sett.filter = BME680_FILTER_SIZE_3;

    /* Set the remaining gas sensor settings and link the heating profile */
    gas_sensor.gas_sett.run_gas = BME680_ENABLE_GAS_MEAS;
    /* Create a ramp heat waveform in 3 steps */
    gas_sensor.gas_sett.heatr_temp = 320; /* degree Celsius */
    gas_sensor.gas_sett.heatr_dur = 150; /* milliseconds */

    /* Select the power mode */
    /* Must be set before writing the sensor configuration */
    gas_sensor.power_mode = BME680_FORCED_MODE; 

    /* Set the required sensor settings needed */
    set_required_settings = BME680_OST_SEL | BME680_OSP_SEL | BME680_OSH_SEL | BME680_FILTER_SEL 
        | BME680_GAS_SENSOR_SEL;

    /* Set the desired sensor configuration */
    rslt = bme680_set_sensor_settings(set_required_settings,&gas_sensor);

    if (rslt != BME680_OK){
      init = false;
    }
    
    /* Set the power mode */
    rslt = bme680_set_sensor_mode(&gas_sensor);

    if (rslt != BME680_OK){
      init = false;
    }
    
    //--------------------- reading sensor data example -------------------------
    /* Get the total measurement duration so as to sleep or wait till the
     * measurement is complete */
    uint16_t meas_period;
    bme680_get_profile_dur(&meas_period, &gas_sensor);

    if ( meas_period == 0){
      init = false;
    } else {
      delay_wrapper(meas_period); // delay till the measurement is ready
    }

    // periodically measure -> based on watchdog timer
    WDTCON0bits.SWDTEN = 1;
    //USER_LED_SetHigh();
}

void BME680_Measure(void){
    polledMeasurement = true;
}

//---------------------- Generate Interrupt to inform the motherboard that data is ready for transmission -----------------------------

// Toggle the interrupt line
void generateInt(void){
    READY_SetLow();
    __delay_ms(1);                          
    READY_SetHigh();
}

void BME680_SetThreshold(uint8_t metric, uint8_t * thresholdData){
    switch(metric){
        case METRIC_TEMPERATURE:{
            tempTreshEnabled = thresholdData[0];
            tempTLL = (uint16_t)((thresholdData[1]<<8) | thresholdData[2]);
            tempTLH = (uint16_t)((thresholdData[3]<<8) | thresholdData[4]);
        } break;
        case METRIC_PRESSURE:{
            presTreshEnabled = thresholdData[0];
            presTLL = (uint16_t)((thresholdData[1]<<8) | thresholdData[2]);
            presTLH = (uint16_t)((thresholdData[3]<<8) | thresholdData[4]);
        } break;
        case METRIC_IAQ:{
            iaqTreshEnabled = thresholdData[0];
            iaqTLL = (uint16_t)((thresholdData[1]<<8) | thresholdData[2]);
            iaqTLH = (uint16_t)((thresholdData[3]<<8) | thresholdData[4]);
        } break;
        case METRIC_HUMIDITY:{
            humiTreshEnabled = thresholdData[0];
            humiTLL = (uint16_t)((thresholdData[1]<<8) | thresholdData[2]);
            humiTLH = (uint16_t)((thresholdData[3]<<8) | thresholdData[4]);
        } break;
        default: break;
    }
}

void BME680_GetData(uint8_t * data, uint8_t  * length){
    uint8_t i;
    for(i=0; i<D_LEN; i++) data[i] = measurementData[i];
    *length = D_LEN;
}

void BME680_Loop(void){
    bool startMeasurement = false;
    // watchdog timer overflow has occurred while sleeping
    if(STATUSbits.nTO == 0){
        WDTCON0bits.SWDTEN = 1; //start watchdog -> results in reset after 1 s
        if(!measurementRunning) startMeasurement = true;
    }
    
    if(startMeasurement || polledMeasurement){
        measurementRunning = true;
        measure();
        measurementRunning = false;
    }
    else{
        /* go to sleep
         * possible wake-up sources in this case:
         *  - i2c clock line goes active
         *  - watchdog timer overflow
         */
        SLEEP();
        NOP();
    }
}

void measure(void){
    USER_LED_SetLow();
    uint8_t set_required_settings;
    bool status = true;
    
    CLRWDT();
    
    /* Select the power mode */
    /* Must be set before writing the sensor configuration */
    gas_sensor.power_mode = BME680_FORCED_MODE; 

    /* Set the required sensor settings needed */
    set_required_settings = BME680_OST_SEL | BME680_OSP_SEL | BME680_OSH_SEL | BME680_FILTER_SEL 
        | BME680_GAS_SENSOR_SEL;

    /* Set the desired sensor configuration */
    rslt = bme680_set_sensor_settings(set_required_settings,&gas_sensor);

    CLRWDT();
    
    if (rslt != BME680_OK){
      status = false;
    }

    /* Set the power mode */
    rslt = bme680_set_sensor_mode(&gas_sensor);

    if (rslt != BME680_OK){
      status = false;
    }

    //--------------------- reading sensor data example -------------------------
    /* Get the total measurement duration so as to sleep or wait till the
     * measurement is complete */
    uint16_t meas_period;
    bme680_get_profile_dur(&meas_period, &gas_sensor);

    CLRWDT();
    
    if ( meas_period == 0){
      status = false;
    } else {
      delay_wrapper(meas_period); // delay till the measurement is ready
    }

    struct bme680_field_data dataBME;

    rslt = bme680_get_sensor_data(&dataBME, &gas_sensor);

    CLRWDT();
    
    if (rslt != BME680_OK){
      status = false;
    }

    if(!status){
        //USER_LED_SetHigh();
        return;
    }
    
    while(!(dataBME.status & BME680_NEW_DATA_MSK)){
      //doe niets!
        //CLRWDT();
        //USER_LED_SetHigh();
        return;
    }
    //--------------------- reading sensor data --------------------------------
    int16_t dataTemperature = 0x0000;
    uint32_t dataPressure = 0x00000000;
    uint32_t dataHumidity = 0x00000000;
    uint32_t IAQ = 0x00000000;
    uint32_t dataGasResistance = 0x00000000;
    uint32_t IAQ_temp = 0x00000000;
    uint32_t IAQ_hum = 0x00000000;
    uint32_t IAQ_gas = 0x00000000;

    //if (init & (dataBME.status & BME680_NEW_DATA_MSK)){
    if (dataBME.status & BME680_NEW_DATA_MSK){
      dataTemperature = dataBME.temperature;
      dataPressure = dataBME.pressure;
      dataHumidity = dataBME.humidity;
      dataGasResistance = dataBME.gas_resistance;
    } else {
      dataTemperature = 0xFFFE;
      dataPressure = 0xFFFFFFFE;
      dataHumidity = 0xFFFFFFFE;
      dataGasResistance = 0xFFFFFFFE;
    }

    if ((dataTemperature) >= 2100){
        IAQ_temp = ((50*(dataTemperature - 2100)/29)+50)/100;
    } else {
        IAQ_temp = ((50*(2100 - dataTemperature)/41)+50)/100;
    }

    if ((dataHumidity) >= 40000){
        IAQ_hum = ((5*(dataHumidity - 40000)/6)+500)/1000;
    } else {
        IAQ_hum = ((5*(40000 - dataHumidity)/4)+500)/1000;
    }

    if (dataGasResistance < 150000){
        IAQ_gas = 2*(150000 - dataGasResistance)/725;
    } else {
        IAQ_gas = 0;
    }

    IAQ = IAQ_temp + IAQ_hum + IAQ_gas;
    
    CLRWDT();
    
    // convert readings to 16-bit value
    uint16_t temp16 = (uint16_t)(dataTemperature+5000);
    uint16_t pres16 = (uint16_t)((dataPressure+50)/100);
    uint16_t humi16 = (uint16_t)((dataHumidity+5)/10);
    uint16_t iaq16 = (uint16_t)(IAQ & 0x0000FFFF);
    
    // copy readings to byte buffer
    measurementData[METRIC_TEMPERATURE*2] = (temp16 >> 8);
    measurementData[1+METRIC_TEMPERATURE*2] = (temp16 & 0xFF);
    measurementData[METRIC_PRESSURE*2] = (pres16 >> 8);
    measurementData[1+METRIC_PRESSURE*2] = (pres16 & 0xFF);
    measurementData[METRIC_IAQ*2] = (iaq16 >> 8);
    measurementData[1+METRIC_IAQ*2] = (iaq16 & 0xFF);
    measurementData[METRIC_HUMIDITY*2] = (humi16 >> 8);
    measurementData[1+METRIC_HUMIDITY*2] = (humi16 & 0xFF);
    
    if(polledMeasurement){ // motherboard has requested a measurement
        polledMeasurement = false;
        // notify the motherboard that the requested measurement has completed
        generateInt();
    }
    else{ // automatic measurement -> check thresholds
        bool thresholdExceeded = false;
        // check temperature thresholds
        if(tempTreshEnabled){
            if(temp16 < tempTLL){
                if(!tempTLLExceeded){
                    thresholdExceeded = true;
                    tempTLLExceeded = true;
                }
            }
            else{
                tempTLLExceeded = false;
            }
            if(temp16 > tempTLH){
                if(!tempTLHExceeded){
                    thresholdExceeded = true;
                    tempTLHExceeded = true;
                }
            }
            else{
                tempTLHExceeded = false;
            }
        }
        
        // check pressure thresholds
        if(presTreshEnabled){
            if(pres16 < presTLL){
                if(!presTLLExceeded){
                    thresholdExceeded = true;
                    presTLLExceeded = true;
                }
            }
            else{
                presTLLExceeded = false;
            }
            if(pres16 > presTLH){
                if(!presTLHExceeded){
                    thresholdExceeded = true;
                    presTLHExceeded = true;
                }
            }
            else{
                presTLHExceeded = false;
            }
        }
        
        // check iaq thresholds
        if(iaqTreshEnabled){
            if(iaq16 < iaqTLL){
                if(!iaqTLLExceeded){
                    thresholdExceeded = true;
                    iaqTLLExceeded = true;
                }
            }
            else{
                iaqTLLExceeded = false;
            }
            if(iaq16 > iaqTLH){
                if(!iaqTLHExceeded){
                    thresholdExceeded = true;
                    iaqTLHExceeded = true;
                }
            }
            else{
                iaqTLHExceeded = false;
            }
        }
        
        // check humidity thresholds
        if(humiTreshEnabled){
            if(humi16 < humiTLL){
                if(!humiTLLExceeded){
                    thresholdExceeded = true;
                    humiTLLExceeded = true;
                }
            }
            else{
                humiTLLExceeded = false;
            }
            if(humi16 > humiTLH){
                if(!humiTLHExceeded){
                    thresholdExceeded = true;
                    humiTLHExceeded = true;
                }
            }
            else{
                humiTLHExceeded = false;
            }
        }
        
        if(thresholdExceeded){
            generateInt();
        }
    }
    USER_LED_SetHigh();
}

#else
#endif
#endif
