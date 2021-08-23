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
 *         File: power.h
 *      Created: 2020-11-27
 *       Author: Jona Cappelle
 *      Version: 0.2
 *
 *  Description: Power Module Implementation
 *
 */


#ifndef __POWER_H__
#define __POWER_H__

/* Header includes */
#include <xc.h>
#include <stdint.h>
#include <stdbool.h>
#include "../global.h"
#include "veml7700.h"
#include "util.h"

#define POWERV2

typedef struct{
    bool enabled;
    float thresholdLevelHigh;
    float thresholdLevelLow;
    bool overThreshold;
    bool underThreshold;
}iwast_power_thresholds_t;

typedef struct{
    float voltage;
}iwast_power_batt_t;

typedef struct{
    veml7700_data_t data;
}iwast_power_light_t;

typedef struct{
    iwast_power_batt_t batt;
    iwast_power_light_t light;
}iwast_power_meas_t;

typedef struct{
    bool startMeasurement;
    bool measurementRunning;
    uint8_t WDT_count;
}iwast_power_ctrl_t;

typedef struct{
    iwast_power_meas_t meas;
    iwast_power_ctrl_t ctrl;
    iwast_power_thresholds_t batt_threshold;
    iwast_power_thresholds_t light_threshold;
}iwast_power_t;

void POWER_init_params();

#define TYPE_BYTE   POWER
#define M_NR        0x02

#define SLAVE_ADDRESS I2C_ADDRESS


#define METRIC_BATT     0
#define METRIC_LIGHT    1

#define ENABLE  1
#define DISABLE 0

#define INPUT   1
#define OUTPUT  0

#define HIGH    1
#define LOW     0

#define ANALOG      1
#define DIGITAL     0

#define PULL_UP_ENABLED      1
#define PULL_UP_DISABLED     0


#define POWER_API { \
    Power_Init, \
    Power_Measure, \
    Power_Loop, \
    Power_GetData, \
    Power_SetThreshold \
}  

/* Sensor API prototypes ******************************************************/

void Power_Init(void);
void Power_Measure(void);
void Power_Loop(void);
void Power_GetData(uint8_t * data, uint8_t  * length);
void Power_SetThreshold(uint8_t metric, uint8_t * thresholdData);

#define LDR_VOLT   0x13

#define LDR_VOLT_TRIS                       TRISCbits.TRISC3
#define LDR_VOLT_LAT                        LATCbits.LATC3
#define LDR_VOLT_PORT                       PORTCbits.RC3
#define LDR_VOLT_WPU                        WPUCbits.WPUC3
#define LDR_VOLT_OD                         ODCONCbits.ODCC3
#define LDR_VOLT_ANS                        ANSELCbits.ANSC3
#define LDR_VOLT_SetHigh()                  do { LATCbits.LATC3 = 1; } while(0)
#define LDR_VOLT_SetLow()                   do { LATCbits.LATC3 = 0; } while(0)
#define LDR_VOLT_Toggle()                   do { LATCbits.LATC3 = ~LATCbits.LATC3; } while(0)
#define LDR_VOLT_GetValue()                 PORTCbits.RC3
#define LDR_VOLT_SetDigitalInput()          do { TRISCbits.TRISC3 = 1; } while(0)
#define LDR_VOLT_SetDigitalOutput()         do { TRISCbits.TRISC3 = 0; } while(0)
#define LDR_VOLT_SetPullup()                do { WPUCbits.WPUC3 = 1; } while(0)
#define LDR_VOLT_ResetPullup()              do { WPUCbits.WPUC3 = 0; } while(0)
#define LDR_VOLT_SetPushPull()              do { ODCONCbits.ODCC3 = 0; } while(0)
#define LDR_VOLT_SetOpenDrain()             do { ODCONCbits.ODCC3 = 1; } while(0)
#define LDR_VOLT_SetAnalogMode()            do { ANSELCbits.ANSC3 = 1; } while(0)
#define LDR_VOLT_SetDigitalMode()           do { ANSELCbits.ANSC3 = 0; } while(0)

#define LDR_MEAS_EN_TRIS                    TRISCbits.TRISC0
#define LDR_MEAS_EN_LAT                     LATCbits.LATC0
#define LDR_MEAS_EN_PORT                    PORTCbits.RC0
#define LDR_MEAS_EN_WPU                     WPUCbits.WPUC0
#define LDR_MEAS_EN_OD                      ODCONCbits.ODCC0
#define LDR_MEAS_EN_ANS                     ANSELCbits.ANSC0
#define LDR_MEAS_EN_SetHigh()               do { LATCbits.LATC0 = 1; } while(0)
#define LDR_MEAS_EN_SetLow()                do { LATCbits.LATC0 = 0; } while(0)
#define LDR_MEAS_EN_Toggle()                do { LATCbits.LATC0 = ~LATCbits.LATC0; } while(0)
#define LDR_MEAS_EN_GetValue()              PORTCbits.RC0
#define LDR_MEAS_EN_SetDigitalInput()       do { TRISCbits.TRISC0 = 1; } while(0)
#define LDR_MEAS_EN_SetDigitalOutput()      do { TRISCbits.TRISC0 = 0; } while(0)
#define LDR_MEAS_EN_SetPullup()             do { WPUCbits.WPUC0 = 1; } while(0)
#define LDR_MEAS_EN_ResetPullup()           do { WPUCbits.WPUC0 = 0; } while(0)
#define LDR_MEAS_EN_SetPushPull()           do { ODCONCbits.ODCC0 = 0; } while(0)
#define LDR_MEAS_EN_SetOpenDrain()          do { ODCONCbits.ODCC0 = 1; } while(0)
#define LDR_MEAS_EN_SetAnalogMode()         do { ANSELCbits.ANSC0 = 1; } while(0)
#define LDR_MEAS_EN_SetDigitalMode()        do { ANSELCbits.ANSC0 = 0; } while(0)

#define NCHG_TRIS                 TRISCbits.TRISC5
#define NCHG_LAT                  LATCbits.LATC5
#define NCHG_PORT                 PORTCbits.RC5
#define NCHG_WPU                  WPUCbits.WPUC5
#define NCHG_OD                   ODCONCbits.ODCC5
#define NCHG_ANS                  ANSELCbits.ANSC5
#define NCHG_SetHigh()            do { LATCbits.LATC5 = 1; } while(0)
#define NCHG_SetLow()             do { LATCbits.LATC5 = 0; } while(0)
#define NCHG_Toggle()             do { LATCbits.LATC5 = ~LATCbits.LATC5; } while(0)
#define NCHG_GetValue()           PORTCbits.RC5
#define NCHG_SetDigitalInput()    do { TRISCbits.TRISC5 = 1; } while(0)
#define NCHG_SetDigitalOutput()   do { TRISCbits.TRISC5 = 0; } while(0)
#define NCHG_SetPullup()          do { WPUCbits.WPUC5 = 1; } while(0)
#define NCHG_ResetPullup()        do { WPUCbits.WPUC5 = 0; } while(0)
#define NCHG_SetPushPull()        do { ODCONCbits.ODCC5 = 0; } while(0)
#define NCHG_SetOpenDrain()       do { ODCONCbits.ODCC5 = 1; } while(0)
#define NCHG_SetAnalogMode()      do { ANSELCbits.ANSC5 = 1; } while(0)
#define NCHG_SetDigitalMode()     do { ANSELCbits.ANSC5 = 0; } while(0)

#endif /* POWER_H_ */
/** @}*/
