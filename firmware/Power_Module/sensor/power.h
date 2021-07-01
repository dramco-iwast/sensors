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
    veml7700_data data;
}iwast_power_light_t;

typedef struct{
    iwast_power_batt_t batt;
    iwast_power_light_t light;
}iwast_power_meas_t;

typedef struct{
    bool startMeasurement;
    bool measurementRunning;
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


#endif /* POWER_H_ */
/** @}*/
