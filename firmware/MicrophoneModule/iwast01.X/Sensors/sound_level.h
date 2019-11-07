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

/* general sensor API providing methods for
 *  - initializing sensor operation
 *  - starting a new measurement
 *  - retrieving measurement data
 *  - setting thresholds
 */
#define SENSOR_API { \
    init, \
    measure, \
    loop, \
    getData, \
    setThreshold \
}  

void init(void);
void measure(void);
void loop(void);
void getData(uint8_t * data, uint8_t  * length);
void setThreshold(uint8_t metric, uint8_t * thresholdData);

#endif	/* __SOUND_LEVEL_H__ */

