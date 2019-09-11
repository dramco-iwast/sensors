/* 
 * File:   dummy.h
 * Author: geoffrey
 *
 * Created on 11 september 2019, 13:26
 */

#ifndef DUMMY_H
#define	DUMMY_H

#include <xc.h>
#include <stdint.h>
#include <stdbool.h>

#define TYPE_BYTE   0x21
#define LENGTH_BYTE 0x04

#define SLAVE_ADDRESS 0x65

void doMeasurement(void);

#endif	/* DUMMY_H */

