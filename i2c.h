#ifndef I2C_H
#define I2C_H

#include <msp430.h>

#define SDA BIT2                    // i2c SDA pin
#define SCL BIT3                    // i2c SCL pin

unsigned char *PTxData;             // Pointer to TX data
unsigned char TxByteCounter;        // number of bytes to TX// buffer for data transmission to screen

void i2c_write(unsigned char slave_address, unsigned char *DataBuffer, unsigned char ByteCtr);
void i2c_init(void);

#endif /* I2C_H */
