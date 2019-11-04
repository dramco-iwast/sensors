/* 
 * File:   buttons.h
 * Author: Sarah
 *
 * Created on 11 september 2019, 13:26
 */

#ifndef DUMMY_H
#define	DUMMY_H

#include <xc.h>
#include <stdint.h>
#include <stdbool.h>

#define TYPE_BYTE   0x21
#define M_NR        0x01

#define SLAVE_ADDRESS 0x65

#define SENSOR_API { \
    ISRHandler, \
    doMeasurement, \
    setThreshold \
}


void ISRHandler(void);
void doMeasurement(uint8_t metric, uint8_t * data, uint8_t  * length);
void generateInt(void);
void LSW1_Toggle(void);
void LSW2_Toggle(void);
void LSW3_Toggle(void);
void LSW4_Toggle(void);
void setThreshold(uint8_t metric, uint8_t * thresholds);


#endif	/* DUMMY_H */
