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
 *         File: main.c
 *      Created: 2019-09-11
 *       Author: Matthias Alleman
 *      Version: 0.1
 *
 *  Description: Sound level sensor
 *
 */


#ifndef __SOUND_LEVEL_H__
#define	__SOUND_LEVEL_H__

#include <xc.h>
#include <stdint.h>
#include <stdbool.h>

#define TYPE_BYTE   0x21
#define M_NR        0x01

#define SLAVE_ADDRESS 0x65


#define SENSOR_API { \
    dummy, \
    doMeasurement, \
    setThreshold \
}  

void dummy(void);

void doMeasurement(uint8_t * data, uint8_t  * length);
void prepTransmission(uint16_t);
void getValue(void);
void initializeADC(void);
void stopADC(void);
void generateInt(void);
void setThreshold(uint8_t metric, uint8_t * thresholdData);
void translateData(uint8_t enable,uint8_t MSBLT,uint8_t LSBLT,uint8_t MSBUP,uint8_t LSBUT);
void enableMic(void);
void disableMic(void);


#endif	/* __SOUND_LEVEL_H__ */

