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
 *         File: veml7700.h
 *      Created: 2021-06-24
 *       Author: Jona Cappelle
 *      Version: 1.0
 *
 *  Description: Interface 
 *      with VEML7700 light sensor
 *
 */

#ifndef __VEML7700_H__
#define __VEML7700_H__

/* Header includes */
#include <xc.h>
#include <stdint.h>
#include <stdbool.h>
#include "../global.h"
#include "../system/i2c2.h"


typedef enum{
    VEML7700_POWER_DISABLE,
    VEML7700_POWER_ENABLE,
}VEML7700_POWER;

typedef enum{
    VEML7700_PS_DISABLE,
    VEML7700_PS_ENABLE,
}VEML7700_POWER_SAVE_EN;

typedef enum{
    VEML7700_PS_MODE1,
    VEML7700_PS_MODE2,
    VEML7700_PS_MODE3,
    VEML7700_PS_MODE4,
}VEML7700_POWER_SAVE;

typedef enum
{
    VEML7700_GAIN_X1,
    VEML7700_GAIN_X2,
    VEML7700_GAIN_1X8,
    VEML7700_GAIN_1X4,
} VEML7700_GAIN;

typedef enum
{
    VEML7700_INTEGRATION_TIME_100MS,
    VEML7700_INTEGRATION_TIME_200MS,
    VEML7700_INTEGRATION_TIME_400MS,
    VEML7700_INTEGRATION_TIME_800MS,
    VEML7700_INTEGRATION_TIME_50MS,
    VEML7700_INTEGRATION_TIME_25MS,
} VEML7700_IT;

typedef enum{
    VEML7700_PERSISTENCE_1,
    VEML7700_PERSISTENCE_2,
    VEML7700_PERSISTENCE_4,
    VEML7700_PERSISTENCE_8,
}VEML7700_PERS;

typedef enum{
    VEML7700_INTERRUPT_DISABLE,
    VEML7700_INTERRUPT_ENABLE,
}VEML7700_INT;

typedef enum{
    VEML7700_POWER_ON,
    VEML7700_SHUTDOWN,
}VEML7700_SD;


typedef struct{
    uint16_t ALS;
    float lux;
}veml7700_data;

typedef struct{
    uint16_t threshold_high;
    uint16_t threshold_low;
    VEML7700_GAIN gain;
    VEML7700_IT integration_time;
    VEML7700_PERS persistence;
    VEML7700_INT interrupts;
    VEML7700_POWER_SAVE_EN powersave_en;
    VEML7700_POWER_SAVE powersave;
    VEML7700_SD shutdown;
}veml7700_settings;

////////////////////////
// FUNCTION DECLARATION
////////////////////////

// Control power to veml7700
void veml7700_power(VEML7700_POWER enable);
// Initialization + de-initialization
void veml7700_init(veml7700_settings const * p_config, veml7700_data * p_data);
void veml7700_deinit();
// Reset by clearing config register
void veml7700_soft_reset();

// Global function to configure the sensor
void veml7700_configure(veml7700_settings const * p_config);
// Sub functions for configuration
uint16_t veml7700_getALSConf();                         // Read out config register
void veml7700_setALSConf(uint16_t conf);                // Lower level function to set whole config register at once
void veml7700_setConf_ALS_GAIN(VEML7700_GAIN gain);     // Set gain
void veml7700_setConf_ALS_IT(VEML7700_IT time);         // Set integration time
void veml7700_setConf_ALS_PERS(VEML7700_PERS pers);     // Set persistence
void veml7700_setConf_ALS_INT_EN(VEML7700_INT i);       // Set interrupts enable
void veml7700_setConf_ALS_SD(VEML7700_SD shutdown);     // Set shutdown mode

// Set thresholds
void veml7700_setALS_WH(uint16_t wh);
void veml7700_setALS_WL(uint16_t wl);
// Set power saving
void veml7700_setPowerSaving(bool enable, VEML7700_POWER_SAVE powermode);

// Functions to get the measurement data
float veml7700_gain_to_float(VEML7700_GAIN gain);
void veml7700_raw_to_lux(veml7700_data * p_data, veml7700_settings const * p_config);
void veml7700_getALS(veml7700_data * p_data, veml7700_settings const * p_config);
uint16_t veml7700_getWHITE(void);
uint16_t veml7700_getALS_INT(void);
void veml7700_getIntStatus(bool th_low_exceeded, bool th_high_exceeded);

// Low level read / write functions to interface veml7700 over i2c
void veml7700_read(uint8_t dataAddress, uint8_t *pData, uint16_t nCount);
void veml7700_write(uint8_t addr, uint8_t* data, uint8_t len);


#define CHECK_BIT(var,pos) ((var) & (1<<(pos)))

// Bitmasks for config register
#define VEML7700_ALS_GAIN_MASK      0b0001100000000000
#define VEML7700_ALS_INT_MASK       0b0000001111000000
#define VEML7700_ALS_PERS_MASK      0b0000000000110000
#define VEML7700_ALS_INT_EN_MASK    0b0000000000000010
#define VEML7700_ALS_SD_MASK        0b0000000000000001
#define VEML7700_PSM_MASK           0b00000110
#define VEML7700_PSM_EN_MASK        0b00000001

#define VEML7700_RETRY_MAX  100

#define VEML7700_I2CADDR_DEFAULT 0x10 ///< I2C address

#define VEML7700_ALS_CONFIG 0x00        ///< Light configuration register
#define VEML7700_ALS_THREHOLD_HIGH 0x01 ///< Light high threshold for irq
#define VEML7700_ALS_THREHOLD_LOW 0x02  ///< Light low threshold for irq
#define VEML7700_ALS_POWER_SAVE 0x03    ///< Power save regiester
#define VEML7700_ALS_DATA 0x04          ///< The light data output
#define VEML7700_WHITE_DATA 0x05        ///< The white light data output
#define VEML7700_INTERRUPTSTATUS 0x06   ///< What IRQ (if any)

#define VEML7700_INTERRUPT_HIGH 0x4000 ///< Interrupt status for high threshold
#define VEML7700_INTERRUPT_LOW 0x8000  ///< Interrupt status for low threshold

#define VEML7700_GAIN_1 0x00   ///< ALS gain 1x
#define VEML7700_GAIN_2 0x01   ///< ALS gain 2x
#define VEML7700_GAIN_1_8 0x02 ///< ALS gain 1/8x
#define VEML7700_GAIN_1_4 0x03 ///< ALS gain 1/4x

#define VEML7700_IT_100MS 0x00 ///< ALS intetgration time 100ms
#define VEML7700_IT_200MS 0x01 ///< ALS intetgration time 200ms
#define VEML7700_IT_400MS 0x02 ///< ALS intetgration time 400ms
#define VEML7700_IT_800MS 0x03 ///< ALS intetgration time 800ms
#define VEML7700_IT_50MS 0x08  ///< ALS intetgration time 50ms
#define VEML7700_IT_25MS 0x0C  ///< ALS intetgration time 25ms

#define VEML7700_PERS_1 0x00 ///< ALS irq persisance 1 sample
#define VEML7700_PERS_2 0x01 ///< ALS irq persisance 2 samples
#define VEML7700_PERS_4 0x02 ///< ALS irq persisance 4 samples
#define VEML7700_PERS_8 0x03 ///< ALS irq persisance 8 samples

#define VEML7700_ALS_INT_DISABLE    0x00
#define VEML7700_ALS_INT_ENABLE     0x01

#define VEML7700_ALS_SD_POWER_ON    0x00
#define VEML7700_ALS_SD_SHUTDOWN    0x01

#define VEML7700_POWERSAVE_ON    0x01
#define VEML7700_POWERSAVE_OFF   0x00
#define VEML7700_POWERSAVE_MODE1 0x00 ///< Power saving mode 1
#define VEML7700_POWERSAVE_MODE2 0x01 ///< Power saving mode 2
#define VEML7700_POWERSAVE_MODE3 0x02 ///< Power saving mode 3
#define VEML7700_POWERSAVE_MODE4 0x03 ///< Power saving mode 4

////////////
// PIN DEFS
////////////

// Power pin - VEML7700 is powered trough pin on microcontroller
#define VEML7700_PWR_TRIS                 TRISAbits.TRISA5
#define VEML7700_PWR_LAT                  LATAbits.LATA5
#define VEML7700_PWR_PORT                 PORTAbits.RA5
#define VEML7700_PWR_WPU                  WPUAbits.WPUA5
#define VEML7700_PWR_OD                   ODCONAbits.ODCA5
#define VEML7700_PWR_ANS                  ANSELAbits.ANSA5
#define VEML7700_PWR_SetHigh()            do { LATAbits.LATA5 = 1; } while(0)
#define VEML7700_PWR_SetLow()             do { LATAbits.LATA5 = 0; } while(0)
#define VEML7700_PWR_Toggle()             do { LATAbits.LATA5 = ~LATAbits.LATA5; } while(0)
#define VEML7700_PWR_GetValue()           PORTAbits.RA5
#define VEML7700_PWR_SetDigitalInput()    do { TRISAbits.TRISA5 = 1; } while(0)
#define VEML7700_PWR_SetDigitalOutput()   do { TRISAbits.TRISA5 = 0; } while(0)
#define VEML7700_PWR_SetPullup()          do { WPUAbits.WPUA5 = 1; } while(0)
#define VEML7700_PWR_ResetPullup()        do { WPUAbits.WPUA5 = 0; } while(0)
#define VEML7700_PWR_SetPushPull()        do { ODCONAbits.ODCA5 = 0; } while(0)
#define VEML7700_PWR_SetOpenDrain()       do { ODCONAbits.ODCA5 = 1; } while(0)
#define VEML7700_PWR_SetAnalogMode()      do { ANSELAbits.ANSA5 = 1; } while(0)
#define VEML7700_PWR_SetDigitalMode()     do { ANSELAbits.ANSA5 = 0; } while(0)

// VEML7700 SDA pin
#define VEML7700_SDA_TRIS                 TRISBbits.TRISB4
#define VEML7700_SDA_LAT                  LATBbits.LATB4
#define VEML7700_SDA_PORT                 PORTBbits.RB4
#define VEML7700_SDA_WPU                  WPUBbits.WPUB4
#define VEML7700_SDA_OD                   ODCONBbits.ODCB4
#define VEML7700_SDA_ANS                  ANSELBbits.ANSB4
#define VEML7700_SDA_SetHigh()            do { LATBbits.LATB4 = 1; } while(0)
#define VEML7700_SDA_SetLow()             do { LATBbits.LATB4 = 0; } while(0)
#define VEML7700_SDA_Toggle()             do { LATBbits.LATB4 = ~LATBbits.LATB4; } while(0)
#define VEML7700_SDA_GetValue()           PORTBbits.RB4
#define VEML7700_SDA_SetDigitalInput()    do { TRISBbits.TRISB4 = 1; } while(0)
#define VEML7700_SDA_SetDigitalOutput()   do { TRISBbits.TRISB4 = 0; } while(0)
#define VEML7700_SDA_SetPullup()          do { WPUBbits.WPUB4 = 1; } while(0)
#define VEML7700_SDA_ResetPullup()        do { WPUBbits.WPUB4 = 0; } while(0)
#define VEML7700_SDA_SetPushPull()        do { ODCONBbits.ODCB4 = 0; } while(0)
#define VEML7700_SDA_SetOpenDrain()       do { ODCONBbits.ODCB4 = 1; } while(0)
#define VEML7700_SDA_SetAnalogMode()      do { ANSELBbits.ANSB4 = 1; } while(0)
#define VEML7700_SDA_SetDigitalMode()     do { ANSELBbits.ANSB4 = 0; } while(0)

// VEML7700 SCL pin
#define VEML7700_SCL_TRIS                 TRISBbits.TRISB6
#define VEML7700_SCL_LAT                  LATBbits.LATB6
#define VEML7700_SCL_PORT                 PORTBbits.RB6
#define VEML7700_SCL_WPU                  WPUBbits.WPUB6
#define VEML7700_SCL_OD                   ODCONBbits.ODCB6
#define VEML7700_SCL_ANS                  ANSELBbits.ANSB6
#define VEML7700_SCL_SetHigh()            do { LATBbits.LATB6 = 1; } while(0)
#define VEML7700_SCL_SetLow()             do { LATBbits.LATB6 = 0; } while(0)
#define VEML7700_SCL_Toggle()             do { LATBbits.LATB6 = ~LATBbits.LATB6; } while(0)
#define VEML7700_SCL_GetValue()           PORTBbits.RB6
#define VEML7700_SCL_SetDigitalInput()    do { TRISBbits.TRISB6 = 1; } while(0)
#define VEML7700_SCL_SetDigitalOutput()   do { TRISBbits.TRISB6 = 0; } while(0)
#define VEML7700_SCL_SetPullup()          do { WPUBbits.WPUB6 = 1; } while(0)
#define VEML7700_SCL_ResetPullup()        do { WPUBbits.WPUB6 = 0; } while(0)
#define VEML7700_SCL_SetPushPull()        do { ODCONBbits.ODCB6 = 0; } while(0)
#define VEML7700_SCL_SetOpenDrain()       do { ODCONBbits.ODCB6 = 1; } while(0)
#define VEML7700_SCL_SetAnalogMode()      do { ANSELBbits.ANSB6 = 1; } while(0)
#define VEML7700_SCL_SetDigitalMode()     do { ANSELBbits.ANSB6 = 0; } while(0)

#endif /* VEML7700_H_ */
/** @}*/