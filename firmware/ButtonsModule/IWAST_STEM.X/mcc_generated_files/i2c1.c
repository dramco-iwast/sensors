/**
  MSSP1 Generated Driver File

  @Company
    Microchip Technology Inc.

  @File Name
    i2c1.c

  @Summary
    This is the generated header file for the MSSP1 driver using 
    PIC10 / PIC12 / PIC16 / PIC18 MCUs

  @Description
    This header file provides APIs for driver for I2C1.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.77
        Device            :  PIC16F18446
        Driver Version    :  2.01
    The generated drivers are tested against the following:
        Compiler          :  XC8 2.05 and above
        MPLAB 	          :  MPLAB X 5.20	
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

#include "i2c1.h"

#define I2C1_SLAVE_ADDRESS 0x08 
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
void I2C1_Initialize(uint8_t slave_address) //MODIFIED (was void)
{
    // initialize the hardware
    // SMP High Speed; CKE disabled; 
    SSP1STAT = 0x00;
    // SSPEN enabled; CKP disabled; SSPM 7 Bit Polling; 
    SSP1CON1 = 0x26;
    // ACKEN disabled; GCEN disabled; PEN disabled; ACKDT acknowledge; RSEN disabled; RCEN disabled; SEN enabled; 
    SSP1CON2 = 0x01;
    // SBCDE disabled; BOEN disabled; SCIE disabled; PCIE disabled; DHEN disabled; SDAHT 100ns; AHEN disabled; 
    SSP1CON3 = 0x00;
    // SSPMSK 127; 
    SSP1MSK = (I2C1_SLAVE_MASK << 1);  // adjust UI mask for R/nW bit            
    // SSPADD 8; 
    //SSP1ADD = (I2C1_SLAVE_ADDRESS << 1);  // adjust UI address for R/nW bit
	SSP1ADD = (slave_address << 1);  // adjust UI address for R/nW bit //MODIFIED
    
    // clear the slave interrupt flag
    PIR3bits.SSP1IF = 0;
    // enable the master interrupt
    PIE3bits.SSP1IE = 1;
    
    rxLen = 0;                  // MODIFIED
    cmdReceived = false;        // MODIFIED

}

void I2C1_ISR ( void )
{
    uint8_t     i2c_data                = 0x55;


    // NOTE: The slave driver will always acknowledge
    //       any address match.

    PIR3bits.SSP1IF = 0;        // clear the slave interrupt flag
    i2c_data        = SSP1BUF;  // read SSPBUF to clear BF
    if(1 == SSP1STATbits.R_nW)
    {
        if((1 == SSP1STATbits.D_nA) && (1 == SSP1CON2bits.ACKSTAT))
        {
            // callback routine can perform any post-read processing
            I2C1_StatusCallback(I2C1_SLAVE_READ_COMPLETED);
        }
        else
        {
            // callback routine should write data into SSPBUF
            I2C1_StatusCallback(I2C1_SLAVE_READ_REQUEST);
        }
    }
    else if(0 == SSP1STATbits.D_nA)
    {
        // this is an I2C address

        // callback routine should prepare to receive data from the master
        I2C1_StatusCallback(I2C1_SLAVE_WRITE_REQUEST);
    }
    else
    {
        I2C1_slaveWriteData   = i2c_data;

        // callback routine should process I2C1_slaveWriteData from the master
        I2C1_StatusCallback(I2C1_SLAVE_WRITE_COMPLETED);
    }

    SSP1CON1bits.CKP    = 1;    // release SCL

} // end I2C1_ISR()

bool I2C1_CommandReceived(void){
    return cmdReceived;
}

void I2C1_GetCommand(uint8_t * cmd, uint8_t * data, uint8_t * len){
    *cmd = cmdByte;
    data = i2c1_rx_buffer;
    *len = rxLen;
    cmdReceived = false;
}

void I2C1_SetTransmitData(uint8_t * data, uint8_t len){
    txCnt = 0;
    while((txCnt < len) && (txCnt < I2C1_TX_BUF_SIZE)){
        i2c1_tx_buffer[txCnt] = data[txCnt]; //MODIFIED
        txCnt++;
    }
    txLen = txCnt;
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
            break;

        case I2C1_SLAVE_READ_COMPLETED:
        default:;

    } // end switch(i2c_bus_state)
}


