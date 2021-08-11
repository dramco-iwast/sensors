/*  ____  ____      _    __  __  ____ ___
 * |  _ \|  _ \    / \  |  \/  |/ ___/ _ \
 * | | | | |_) |  / _ \ | |\/| | |  | | | |
 * | |_| |  _ <  / ___ \| |  | | |__| |_| |
 * |____/|_| \_\/_/   \_\_|  |_|\____\___/
 *                           research group
 *                             dramco.be/
 *
 *  KU Leuven - Technology Campus Gent,
 *  Gebroeders De Smetstraat 1,
 *  B-9000 Gent, Belgium
 *
 *         File: battery.c
 *      Created: 2020-11-27
 *       Author: Jona Cappelle
 *      Version: 0.2
 *
 *  Description: Read battery voltage
 *
 */

#include <xc.h>
#include "../global.h"
#include "../system/system.h"
#include "battery.h"
#include "../system/adcc.h"
#include "util.h"
#include "stdint.h"
#include "string.h"
#include "stdbool.h"


void ADC_Init()
{
    // Enable ADC peripheral
    PMD3bits.ADCMD = 0; 
    
    // Enable FVR module
    PMD0bits.FVRMD = 0;
    
    // Enable Fixed voltage reference with voltage of 2.048 V
    FVRCON = 0x82;
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
    // ADCS FOSC/2; 
    ADCLK = 0x00;
    //  ADCLK = 0x07;
    //  Doesnt matter, since we're just doing a single conversion
    //  I've changed it back to the default value
    //  TODO
    
    // ADGO stop; ADFM right; ADON enabled; ADCS FOSC/ADCLK; ADCONT disabled; 
    ADCON0 = 0x84;
    
    FVRCON = 0x00; // Disable fixed voltage reference
}

void ADC_Fixed_Voltage_Ref(battery_fvr_t mode){
    switch(mode)
    {
        case BATTERY_FVR_ENABLE:
            FVRCON = 0x82; // Enable Fixed voltage reference
            break;

        case BATTERY_FVR_DISABLE:
            FVRCON = 0x00; // Disable the Fixed voltage reference
            break;
            
        default:
            FVRCON = 0x00; // Disable the Fixed voltage reference
    }
}

void battery_init()
{
    // Init ADC
    ADC_Init();

    // Set pins
    BAT_MEAS_EN_SetDigitalMode();
    BAT_MEAS_EN_SetDigitalOutput();
    BAT_MEAS_EN_SetLow();
    
    BAT_VOLT_SetDigitalInput(); 
    BAT_VOLT_SetAnalogMode();
    
}

float battery_measure(void)
{
    ADC_Fixed_Voltage_Ref(BATTERY_FVR_ENABLE);
    
    BAT_MEAS_EN_SetHigh(); // Enable loadswitch to measure voltage
    __delay_ms(20);  // Delay for settling voltages, 10ms is not long enough

    //  Reference voltage to FVR module (2.048 V)
//    ADREFbits.PREF0 = 1;
//    ADREFbits.PREF1 = 1;
    
    // Get ADC value
    ADCC_GetSingleConversion(BAT_VOLT_ADC_CHN); 
    uint16_t voltage = ADCC_GetSingleConversion(BAT_VOLT_ADC_CHN);
    // Convert ADC value to voltage (Resistor divider)
    float batt_voltage = ((float)voltage /4096) * 2.048 * ((10+8.2)/8.2);

    BAT_MEAS_EN_SetLow(); // Disable loadswitch to measure voltage
    
    //  Reference voltage to VDD (3V3)
//    ADREFbits.PREF0 = 0;   
//    ADREFbits.PREF1 = 0;
    
    ADC_Fixed_Voltage_Ref(BATTERY_FVR_DISABLE);
    
    return batt_voltage;
}
