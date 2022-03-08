/*
 * bme680_air_quality.h
 *
 *  Created on: 30 Nov 2020
 *      Author: sarah
 */

#ifndef BME680_AIR_QUALITY_H_
#define BME680_AIR_QUALITY_H_

#include <stdint.h>
#include <stdbool.h>
#include "global.h"

#define TYPE_BYTE       BME680
#define M_NR            0x04

#define SLAVE_ADDRESS   I2C_ADDRESS

#define SENSOR_API { \
    BME680_Init, \
    BME680_Measure, \
    BME680_Loop, \
    BME680_GetData, \
    BME680_SetThreshold \
}

#define D_LEN (M_NR * 2)
#define METRIC_TEMPERATURE  0
#define METRIC_PRESSURE     1
#define METRIC_IAQ          2
#define METRIC_HUMIDITY     3

/* Sensor API prototypes ******************************************************/

void BME680_Init(void);
void BME680_Measure(void);
void BME680_Loop(void);
void BME680_GetData(uint8_t * data, uint8_t  * length);
void BME680_SetThreshold(uint8_t metric, uint8_t * thresholdData);

#endif /* BME680_AIR_QUALITY_H_ */
