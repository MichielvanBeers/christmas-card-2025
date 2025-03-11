#include "i2c.h"

#include <msp430.h>
#include <stdint.h>

void i2c_init(void) {
    // Put eUSCI_B0 in software reset
    UCB0CTLW0 |= UCSWRST;

    // Configure eUSCI_B0 for I2C communication
    UCB0CTLW0 |= UCSSEL_3;      // Select SMLCK = 1MHz
    UCB0BRW = 10;               // Divide by 10 = 100kHz
    UCB0CTLW0 |= UCMODE_3;      // Put into I2C mode
    UCB0CTLW0 |= UCMST;         // Put into master mode
    UCB0CTLW1 |= UCASTP_2;      // Auto stop when UCB0TBCNT is reached

    // Configure ports
    P1SEL0 |= SDA | SCL;
    P1SEL1 &= ~(SDA | SCL);

    // Disable low power mode
    PM5CTL0 &= ~LOCKLPM5;

    // Take eUSCI_B0 out of software reset
    UCB0CTLW0 &= ~UCSWRST;

    // Enable interrupts
    UCB0IE |= UCTXIE0;          // Enable I2C Tx0 IRQ
    __enable_interrupt();
}

void i2c_write(unsigned char slave_address, unsigned char *DataBuffer, unsigned char ByteCounter) {
    UCB0I2CSA = slave_address;
    UCB0TBCNT = ByteCounter;

    PTxData = DataBuffer;
    TxByteCounter = ByteCounter;

    while (UCB0STATW & UCBBUSY);
    UCB0CTLW0 |= UCTR;                      // Put in Tx mode
    UCB0CTLW0 |= UCTXSTT;                   // Generate start condition

    while ((UCB0IFG & UCSTPIFG) == 0);      // Wait for stop flag
    UCB0IFG &= ~UCSTPIFG;                   // Clear stop flag
}
