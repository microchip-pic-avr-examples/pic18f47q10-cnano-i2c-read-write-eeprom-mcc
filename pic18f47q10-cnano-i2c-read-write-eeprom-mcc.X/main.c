/*
© [2023] Microchip Technology Inc. and its subsidiaries.

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


#define CEIL(x, y)    ((x) / (y) + (((x) % (y)) != 0))
#define MIN(x, y)     (((x) < (y)) ? (x) : (y))


#define I2C_EEPROM_ADDRES   0x50 // 7-bit address
#define PAGE_SIZE           8

#define TEST_BYTES_SIZE         20
#define EEPROM_START_ADDRESS    0x00


static uint8_t WriteBytesToEeprom(uint8_t const address, uint8_t const memoryAddress, uint8_t const * data, uint8_t dataLength);


static const i2c_host_interface_t * I2C = &I2C1_Host;

static uint8_t dataWrite[TEST_BYTES_SIZE] = { 0 };
static uint8_t dataRead[TEST_BYTES_SIZE] = { 0 };

bool dataOperationSuccessful = false;

void main(void)
{
    SYSTEM_Initialize();

    INTERRUPT_GlobalInterruptHighEnable();

    
    for (uint8_t idx = 0; idx < TEST_BYTES_SIZE; ++idx)
    {
        dataWrite[idx] = idx;
    }

    uint8_t const nextEepromAddress = WriteBytesToEeprom(I2C_EEPROM_ADDRES, EEPROM_START_ADDRESS, dataWrite, TEST_BYTES_SIZE);

    if (!dataOperationSuccessful)
    {
        // Error handling
    }

    while (true)
    {
        dataWrite[0] = EEPROM_START_ADDRESS;

        if (I2C->WriteRead(I2C_EEPROM_ADDRES, dataWrite, 1, dataRead, TEST_BYTES_SIZE))
        {
            while (I2C->IsBusy())
            {
                I2C->Tasks();
            }

            if (I2C->ErrorGet() == I2C_ERROR_NONE)
            {
                printf("\r\n-----------------------------------");
                for (uint8_t idx = 0; idx < TEST_BYTES_SIZE; ++idx)
                {
                    printf("\r\nAddress 0x%02X -> %i", EEPROM_START_ADDRESS + idx, dataRead[idx]);
                }
                printf("\r\n-----------------------------------");
            }
            else
            {
                // Error handling
                printf("\r\n Error occurred!");
            }
        }
        __delay_ms(5000);
    }
}

/**
 * @brief This function enables the user to write N bytes to an EEPROM without 
 * having to think about page size and page buffer. However, it does not take 
 * care of end of memory space issues (e.g. what happens when trying to write 
 * past the last memory address).
 *
 * @return Returns a value that corresponds to the next EEPROM address.
 **/
static uint8_t WriteBytesToEeprom(uint8_t const address, uint8_t const memoryAddress, uint8_t const * data, uint8_t dataLength)
{
    uint8_t lastPage = CEIL(dataLength, PAGE_SIZE);
    uint8_t bytesForCurrentWrite = MIN(PAGE_SIZE - (memoryAddress % PAGE_SIZE), dataLength);

    uint8_t dataBuffer[PAGE_SIZE + 1] = { 0 };
    dataBuffer[0] = memoryAddress;

    for (uint8_t currentPage = 1; currentPage <= lastPage; ++currentPage)
    {
        for (uint8_t idx = 0; idx < bytesForCurrentWrite; idx++)
        {
            dataBuffer[idx + 1] = *data++;
        }

        dataOperationSuccessful = true;

        if (I2C->Write(address, dataBuffer, bytesForCurrentWrite + 1))
        {
            while (I2C->IsBusy())
            {
                I2C->Tasks();
            }
            
            if (I2C->ErrorGet() == I2C_ERROR_NONE)
            {
                // Write operation is successful
            }
            else
            {
                // Error handling
                dataOperationSuccessful = false;
            }

        }

        dataLength -= bytesForCurrentWrite;
        dataBuffer[0] += bytesForCurrentWrite;
        bytesForCurrentWrite = MIN(PAGE_SIZE, dataLength);

        // Wait for the page write buffer to be flushed
        __delay_ms(5);
    }

    return dataBuffer[0];
}
