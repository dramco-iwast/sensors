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
 *         File: i2c1.c
 *      Created: 2020-08-26
 *       Author: Geoffrey Ottoy
 *      Version: 1.0
 *
 *  Description: Modified version of the Microchip MSSP1 Driver (see License)
 *
 */

/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
*/

#include <string.h>
#include "i2c1.h"
#include "../global.h"

#define I2C1_SLAVE_MASK    0x7F

#define I2C1_RX_BUF_SIZE   32  // MODIFIED
#define I2C1_TX_BUF_SIZE   32  // MODIFIED

typedef enum {                 // MODIFIED
    SLAVE_COMMAND_DATA,        // MODIFIED
    SLAVE_COMMAND,             // MODIFIED
} SLAVE_WRITE_DATA_TYPE;       // MODIFIED

/**
 Section: Global Variables
*/

volatile uint8_t    I2C1_slaveWriteData      = 0x55;


// Local variables
static uint8_t i2c1_rx_buffer[I2C1_RX_BUF_SIZE]; // MODIFIED
static uint8_t i2c1_tx_buffer[I2C1_TX_BUF_SIZE]; // MODIFIED

static uint8_t cmdByte;                          // MODIFIED
static bool cmdReceived;                         // MODIFIED
static uint8_t rxLen;                            // MODIFIED
static uint8_t txLen;                            // MODIFIED
static uint8_t txCnt;                            // MODIFIED

/**
 Section: Local Functions
*/
void I2C1_StatusCallback(I2C1_SLAVE_DRIVER_STATUS i2c_bus_state);


/**
  Prototype:        void I2C1_Initialize(void)
  Input:            none
  Output:           none
  Description:      I2C1_Initialize is an
                    initialization routine that takes inputs from the GUI.
  Comment:          
  Usage:            I2C1_Initialize();

*/
void I2C1_Initialize(uint8_t slave_address){ //MODIFIED
    // initialize the hardware
    PMD6bits.MSSP1MD = 0; // enable MSSP1
    //ANSELB = 0x50;
    ANSELBbits.ANSB5 = 0; // RB5 is digital pin
    ANSELBbits.ANSB7 = 0; // RB7 is digital pin
    //TRISB = 0xF0;
    TRISBbits.TRISB5 = 1; // RB5 is input
    TRISBbits.TRISB7 = 1; // RB7 is input
    
    SSP1CLKPPS = 0x0F;   //RB7->MSSP1:SCL1;    
    RB7PPS = 0x13;       //RB7->MSSP1:SCL1;    
    RB5PPS = 0x14;       //RB5->MSSP1:SDA1;    
    SSP1DATPPS = 0x0D;   //RB5->MSSP1:SDA1;   
    
    // SMP High Speed; CKE disabled; 
    SSP1STAT = 0x00;
    // SSPEN enabled; CKP disabled; SSPM 7 Bit Polling; 
    SSP1CON1 = 0x26;
    // ACKEN disabled; GCEN disabled; PEN disabled; ACKDT acknowledge; RSEN disabled; RCEN disabled; SEN enabled; 
    SSP1CON2 = 0x01;
    // SBCDE disabled; BOEN disabled; SCIE disabled; PCIE disabled; DHEN disabled; SDAHT 100ns; AHEN disabled; 
    SSP1CON3 = 0x00;
    //SSP1CON3bits.AHEN = 1;
    SSP1CON3bits.DHEN = 1;
    // SSPMSK 127; 
    SSP1MSK = (I2C1_SLAVE_MASK << 1);  // adjust UI mask for R/nW bit            
    // SSPADD; 
	SSP1ADD = (slave_address << 1);  // adjust UI address for R/nW bit //MODIFIED
	
    
    // clear the slave interrupt flag
    PIR3bits.SSP1IF = 0;
    // enable the master interrupt
    PIE3bits.SSP1IE = 1;
    
    txCnt = 0;
    rxLen = 0;                  // MODIFIED
    cmdReceived = false;        // MODIFIED
}

void I2C1_ISR(void){
    uint8_t     i2c_data                = 0x00;

    // NOTE: The slave driver will always acknowledge
    //       any address match.

    PIE3bits.SSP1IE = 0;
    PIR3bits.SSP1IF = 0;        // clear the slave interrupt flag
    i2c_data        = SSP1BUF;  // read SSPBUF to clear BF
    if(1 == SSP1STATbits.R_nW){
        if((1 == SSP1STATbits.D_nA) && (1 == SSP1CON2bits.ACKSTAT)){
            // callback routine can perform any post-read processing
            I2C1_StatusCallback(I2C1_SLAVE_READ_COMPLETED);
        }
        else{
            // callback routine should write data into SSPBUF
            I2C1_StatusCallback(I2C1_SLAVE_READ_REQUEST);
            SSP1CON1bits.CKP = 1;       // release SCL
            //while(!PIR3bits.SSP1IF);    // TODO: make non-blocking
        }
    }
    else if(0 == SSP1STATbits.D_nA){
        // this is an I2C address

        // callback routine should prepare to receive data from the master
        I2C1_StatusCallback(I2C1_SLAVE_WRITE_REQUEST);
    }
    else{
        I2C1_slaveWriteData   = i2c_data;

        // callback routine should process I2C1_slaveWriteData from the master
        I2C1_StatusCallback(I2C1_SLAVE_WRITE_COMPLETED);
        SSP1CON1bits.CKP = 1;       // release SCL
        uint8_t ctr=0xff;
        while(!PIR3bits.SSP1IF && ctr--){
            __delay_us(1);
        }    // TODO: make non-blocking
    }

    // clear the slave interrupt flag
    PIR3bits.SSP1IF = 0;
    SSP1CON1bits.CKP    = 1;    // release SCL

    PIE3bits.SSP1IE = 1;
} // end I2C1_ISR()

bool I2C1_CommandReceived(void){
    return cmdReceived;
}

bool I2C1_TxBufferEmpty(void){
    return (txCnt != 0);
}

void I2C1_GetCommand(uint8_t * cmd){
    *cmd = cmdByte;
    cmdReceived = false;
}

void I2C1_GetCommandData(uint8_t * data, uint8_t * len){
    memcpy(data, i2c1_rx_buffer, rxLen);
    *len = rxLen;
}

void I2C1_SetTransmitData(uint8_t * data, uint8_t len){
    //txCnt = 0;
    while((txCnt < len) && (txCnt < I2C1_TX_BUF_SIZE)){
        i2c1_tx_buffer[txCnt] = data[txCnt]; //MODIFIED
        txCnt++;
    }
    txLen = txCnt;
    txCnt = 0;
}

void I2C1_ClearTxBuffer(void){
    txCnt = 0;
}

/* Implementation of the callback
 */
void I2C1_StatusCallback(I2C1_SLAVE_DRIVER_STATUS i2c_bus_state){

    static uint8_t slaveWriteType   = SLAVE_COMMAND_DATA;

    // actions based on current state
    switch (i2c_bus_state){
        
        case I2C1_SLAVE_WRITE_REQUEST:
            // the master will be sending the eeprom address next
            slaveWriteType  = SLAVE_COMMAND;
            break;

        case I2C1_SLAVE_WRITE_COMPLETED:

            switch(slaveWriteType)
            {
                case SLAVE_COMMAND:
                    cmdByte   = I2C1_slaveWriteData;
                    rxLen = 0;
                    cmdReceived = true;
                    break;

                case SLAVE_COMMAND_DATA:
                default:
                    // the master has written data to store in the eeprom
                    if(rxLen <= I2C1_RX_BUF_SIZE)
                    {
                        i2c1_rx_buffer[rxLen++]    = I2C1_slaveWriteData;
                    }
                    break;

            } // end switch(slaveWriteType)

            slaveWriteType  = SLAVE_COMMAND_DATA;
            break;

        case I2C1_SLAVE_READ_REQUEST:
            if(txCnt<txLen){
                SSP1BUF = i2c1_tx_buffer[txCnt++];
            }
            else{
                SSP1BUF = 0x00;
            }
//            SSP1CON1bits.CKP = 1;
            break;

        case I2C1_SLAVE_READ_COMPLETED:
        default:;

    } // end switch(i2c_bus_state)
}

