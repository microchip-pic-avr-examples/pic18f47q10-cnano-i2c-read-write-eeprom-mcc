/*
© [2021] Microchip Technology Inc. and its subsidiaries.

    Subject to your compliance with these terms, you may use Microchip 
    software and any derivatives exclusively with Microchip products. 
    You are responsible for complying with 3rd party license terms  
    applicable to your use of 3rd party software (including open source  
    software) that may accompany Microchip software. SOFTWARE IS ?AS IS.? 
    NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS 
    SOFTWARE, INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT,  
    MERCHANTABILITY, OR FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT 
    WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY 
    KIND WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF 
    MICROCHIP HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE 
    FORESEEABLE. TO THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP?S 
    TOTAL LIABILITY ON ALL CLAIMS RELATED TO THE SOFTWARE WILL NOT 
    EXCEED AMOUNT OF FEES, IF ANY, YOU PAID DIRECTLY TO MICROCHIP FOR 
    THIS SOFTWARE.
*/
#include "mcc_generated_files/system/system.h"
#include "mcc_generated_files/i2c_host/i2c_host_types.h"
#include "mcc_generated_files/i2c_host/mssp1.h"


#define MIN(x,y) (((x)<(y)) ? (x) : (y))
#define I2C_EEPROM_ADDR 0x50 /* 7-bit address */
#define PAGESIZE 8
#define TEST_SET_SIZE 20


/* Defining functions */
static uint8_t I2C1_writeNBytesEEPROM(uint8_t address, uint8_t memoryAddress, uint8_t*
data, uint8_t dataLength, uint8_t EEPROMPagesize);

/* Declare variables */
const i2c_host_interface_t *I2C = &i2c1_host_interface;
uint8_t dataWrite[TEST_SET_SIZE];
uint8_t dataRead[TEST_SET_SIZE];
uint8_t EEPROMMemoryRegister = 0x00;

int main(void)
{
    SYSTEM_Initialize();
    
    /* Constructing test data */
    for (uint8_t i = 0; i < TEST_SET_SIZE; i++)
    {
        dataWrite[i] = i;
    }
    
    /* Write N bytes of data to the EEPROM and return pointer to next EEPROM address*/
    EEPROMMemoryRegister = I2C1_writeNBytesEEPROM(I2C_EEPROM_ADDR, EEPROMMemoryRegister,
    dataWrite, TEST_SET_SIZE, PAGESIZE);
    
    if(!dataOperationSuccessful)
    {
        /* Handle error */
    }
    
    while(1)
    {
        /* Telling the EEPROM to read back from the beginning of the memory register */
        dataWrite[0] = 0x00;
        if (I2C->WriteRead(I2C_EEPROM_ADDR, dataWrite, 1, dataRead, 10))
        {
            while(I2C->IsBusy())
            {
                I2C->Tasks();
            }
            if (I2C->ErrorGet() == I2C_ERROR_NONE)
            {
                /* WriteRead operation is successful */
                printf("\r\n-----------------------------------");
                for (uint8_t i = 0; i < 10; i++)
                {
                    printf("\r\nValues read = %i", dataRead[i]);
                }
                printf("\r\n-----------------------------------");
            }
            else
            {
                /* Error handling */
                printf("\r\n Error Occurred");
            }
        }
        __delay_ms(5000);
    }
}

/* This function enables the user to write N bytes to an EEPROM without having to think about
pagesize and pagebuffer.
* However, it does not take care of end of memory space issues. E.g. what happens when we
try to write past the last memory address.
* Returns a value that corresponds to the last memory address written to */
static uint8_t I2C1_writeNBytesEEPROM(uint8_t address, uint8_t memoryAddress, uint8_t*
data, uint8_t dataLength, uint8_t EEPROMPagesize)
{
    uint8_t pageCounter = memoryAddress/EEPROMPagesize;
    uint8_t pageEnd = pageCounter + dataLength / EEPROMPagesize;
    uint8_t dataPerIteration = MIN(EEPROMPagesize - (memoryAddress%EEPROMPagesize),dataLength);
    uint8_t dataBuffer[8 + 1]; /* PAGESIZE + memoryAddress */
    /* Storing the memory pointer */
    dataBuffer[0] = memoryAddress;
    while(pageCounter <= pageEnd)
    {
        /* wait for page write buffer */
        __delay_ms(2);
        /* Loading the desired data onto the buffer */
        for (uint8_t i = 0; i < dataPerIteration; i++)
        {
            dataBuffer[i+1] = *data++;
        }
        
        dataOperationSuccessful = 1;
        /* Writing the memory address and data to EEPROM */
        if(I2C->Write(address, dataBuffer, dataPerIteration + 1))
        {
            while(I2C->IsBusy())
            {
                I2C->Tasks();
            }
            if (I2C->ErrorGet() == I2C_ERROR_NONE)
            {
                /* Write operation is successful */
            }
            else
            {
                /* Error handling */
                dataOperationSuccessful = 0;
            }
            
        }
        /* Updating variables for next iteration */
        dataLength -= dataPerIteration;
        dataBuffer[0] += dataPerIteration;
        dataPerIteration = MIN(EEPROMPagesize,dataLength);
        pageCounter++;
    }
    return dataBuffer[0];
}