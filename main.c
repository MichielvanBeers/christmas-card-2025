#include <msp430.h>
#include <stdint.h>
#include "i2c.h"
#include "ssd1306.h"

const char textBlock[55] = "Lieve Carmen, ik hoop dat je een hele fijne kerst hebt!";

int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer

    // Initialize i2c
    i2c_init();

    // Initialize ssd1306
    ssd1306_init();

    // Clear display
    ssd1306_clear_display();

    // Turn all pixels on
    ssd1306_print_text_block(0, 0, textBlock);

    while(1){}

    return 0;
}

/* =============================================================================
 * The EUSCI_B0_VECTOR is structured such that it can be used to transmit any
 * number of bytes by pre-loading TXByteCtr with the byte count. Also, TXData
 * points to the next byte to transmit.
 * ============================================================================= */
#pragma vector = EUSCI_B0_VECTOR
__interrupt void b0_vector_isr(void) {
    if (TxByteCounter) {                                                    // Check TX byte counter
        UCB0TXBUF = *PTxData++;                                             // Load TX buffer
        TxByteCounter--;                                                    // Decrement TX byte counter
    }
}
