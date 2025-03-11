#include <msp430.h>
#include <stdint.h>
#include <string.h>
#include "i2c.h"

unsigned char buffer[17];                                                     // buffer for data transmission to screen

/* ====================================================================
 * Horizontal Centering Number Array
 * ==================================================================== */
#define HCENTERUL_OFF   0
#define HCENTERUL_ON    1

/* ====================================================================
 * SSD1306 OLED Settings and Command Definitions
 * ==================================================================== */

#define SSD1306_I2C_ADDRESS             0x3C

#define SSD1306_LCDWIDTH                128
#define SSD1306_LCDHEIGHT               64
#define SSD1306_128_64

#define SSD1306_SETCONTRAST             0x81
#define SSD1306_DISPLAYALLON_RESUME     0xA4
#define SSD1306_DISPLAYALLON            0xA5
#define SSD1306_NORMALDISPLAY           0xA6
#define SSD1306_INVERTDISPLAY           0xA7
#define SSD1306_DISPLAYOFF              0xAE
#define SSD1306_DISPLAYON               0xAF

#define SSD1306_SETDISPLAYOFFSET        0xD3
#define SSD1306_SETCOMPINS              0xDA

#define SSD1306_SETVCOMDETECT           0xDB

#define SSD1306_SETDISPLAYCLOCKDIV      0xD5
#define SSD1306_SETPRECHARGE            0xD9

#define SSD1306_SETMULTIPLEX            0xA8

#define SSD1306_SETLOWCOLUMN            0x00
#define SSD1306_SETHIGHCOLUMN           0x10

#define SSD1306_SETSTARTLINE            0x40

#define SSD1306_MEMORYMODE              0x20
#define SSD1306_COLUMNADDR              0x21
#define SSD1306_PAGEADDR                0x22

#define SSD1306_COMSCANINC              0xC0
#define SSD1306_COMSCANDEC              0xC8

#define SSD1306_SEGREMAP                0xA0

#define SSD1306_CHARGEPUMP              0x8D

#define SSD1306_EXTERNALVCC             0x1
#define SSD1306_SWITCHCAPVCC            0x2

#define SSD1306_ACTIVATE_SCROLL                         0x2F
#define SSD1306_DEACTIVATE_SCROLL                       0x2E
#define SSD1306_SET_VERTICAL_SCROLL_AREA                0xA3
#define SSD1306_RIGHT_HORIZONTAL_SCROLL                 0x26
#define SSD1306_LEFT_HORIZONTAL_SCROLL                  0x27
#define SSD1306_VERTICAL_AND_RIGHT_HORIZONTAL_SCROLL    0x29
#define SSD1306_VERTICAL_AND_LEFT_HORIZONTAL_SCROLL     0x2A

void ssd1306_init(void) {
    // SSD1306 init sequence
    ssd1306_command(SSD1306_DISPLAYOFF);                                // 0xAE
    ssd1306_command(SSD1306_SETDISPLAYCLOCKDIV);                        // 0xD5
    ssd1306_command(0x80);                                              // the suggested ratio 0x80

    ssd1306_command(SSD1306_SETMULTIPLEX);                              // 0xA8
    ssd1306_command(SSD1306_LCDHEIGHT - 1);

    ssd1306_command(SSD1306_SETDISPLAYOFFSET);                          // 0xD3
    ssd1306_command(0x0);                                               // no offset
    ssd1306_command(SSD1306_SETSTARTLINE | 0x0);                        // line #0
    ssd1306_command(SSD1306_CHARGEPUMP);                                // 0x8D
    ssd1306_command(0x14);                                              // generate high voltage from 3.3v line internally
    ssd1306_command(SSD1306_MEMORYMODE);                                // 0x20
    ssd1306_command(0x00);                                              // 0x0 act like ks0108
    ssd1306_command(SSD1306_SEGREMAP | 0x1);
    ssd1306_command(SSD1306_COMSCANDEC);

    ssd1306_command(SSD1306_SETCOMPINS);                                // 0xDA
    ssd1306_command(0x12);
    ssd1306_command(SSD1306_SETCONTRAST);                               // 0x81
    ssd1306_command(0xCF);

    ssd1306_command(SSD1306_SETPRECHARGE);                              // 0xd9
    ssd1306_command(0xF1);
    ssd1306_command(SSD1306_SETVCOMDETECT);                             // 0xDB
    ssd1306_command(0x40);
    ssd1306_command(SSD1306_DISPLAYALLON_RESUME);                       // 0xA4
    ssd1306_command(SSD1306_NORMALDISPLAY);                             // 0xA6

    ssd1306_command(SSD1306_DEACTIVATE_SCROLL);

    ssd1306_command(SSD1306_DISPLAYON);                                 //--turn on oled panel
}

void ssd1306_turn_all_pixels_on(void) {
    ssd1306_command(SSD1306_DISPLAYALLON);
}

void ssd1306_clear_display(void) {
    uint8_t i, j, k;

    // Set memory addressing mode
    ssd1306_command(SSD1306_MEMORYMODE);
    ssd1306_command(0x00);  // Horizontal addressing mode

    // Set column address range
    ssd1306_command(SSD1306_COLUMNADDR);
    ssd1306_command(0);     // Start at column 0
    ssd1306_command(SSD1306_LCDWIDTH - 1); // End at column 127

    // Set page address range
    ssd1306_command(SSD1306_PAGEADDR);
    ssd1306_command(0);     // Start at page 0
    ssd1306_command(7);     // End at page 7 (for 64-pixel height display)

    // Prepare buffer for data transmission (all zeros)
    buffer[0] = 0x40;       // Co = 0, D/C = 1 (data)

    // Each page is 128 columns wide
    // We'll send 16 bytes at a time (limited by our buffer size)
    for (i = 0; i < 8; i++) {           // 8 pages for 64-pixel height
        for (j = 0; j < SSD1306_LCDWIDTH/16; j++) {  // 128 pixels width / 16 bytes
            // Fill buffer with zeros (starting from index 1)
            for (k = 1; k <= 16; k++) {
                buffer[k] = 0x00;
            }
            // Send 16 bytes of zeros
            i2c_write(SSD1306_I2C_ADDRESS, buffer, 17);
        }
    }
}

void ssd1306_command(unsigned char command) {
    buffer[0] = 0x80;
    buffer[1] = command;

    i2c_write(SSD1306_I2C_ADDRESS, buffer, 2);
}
