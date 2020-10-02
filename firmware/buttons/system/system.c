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
 *         File: system.c
 *      Created: 2020-10-02
 *       Author: Geoffrey Ottoy
 *      Version: 2.0
 *
 *  Description: Basic system initialization for the oscillator and 
 *               I2C slave interface.
 * 
 */

#include "system.h"
#include "i2c1.h"
#include "interrupt.h"

void OSCILLATOR_Initialize(void);
void PMD_Initialize(void);
void PIN_MANAGER_Initialize(void);

void SYSTEM_Initialize(uint8_t slave_address){ //MODIFIED (was void))
    PMD_Initialize();
    OSCILLATOR_Initialize();
       
    I2C1_Initialize(slave_address);

    GlobalInterruptEnable();
    PeripheralInterruptEnable();
}

// The SensorInterruptHandler allows the sensor-specific code to operate
// interrupt-base.
void SYSTEM_SetSensorISR(void (* SensorInterruptHandler)(void)){
    SetSensorInterruptHandler(SensorInterruptHandler);
}

// Clock setup
void OSCILLATOR_Initialize(void){
    // NOSC HFINTOSC; NDIV 1; 
    OSCCON1 = 0x60;
    // HFFRQ 32_MHz; 
    OSCFRQ = 0x06;
}

// Enable/disable peripheral modules
void PMD_Initialize(void){
    // CLKRMD CLKR enabled;
    // SYSCMD SYSCLK enabled;
    // FVRMD FVR enabled;
    // IOCMD IOC enabled;
    // NVMMD NVM enabled; 
    PMD0 = 0x00; // reset value
    // disable the rest by default -> should be enabled by sensor
    PMD1 = 0xFF;
    PMD2 = 0xFF;
    PMD3 = 0xFF;
    PMD4 = 0xFF;
    PMD5 = 0xFF;
    PMD6 = 0xFF;
    PMD7 = 0xFF;
}
