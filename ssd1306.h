#ifndef SSD1306_H
#define SSD1306_H

#include <msp430.h>

void ssd1306_init(void);
void ssd1306_turn_all_pixels_on(void);
void ssd1306_clear_display(void);
void ssd1306_command(unsigned char command);

#endif /* SSD1306_H */
