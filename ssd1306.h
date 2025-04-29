#ifndef SSD1306_H
#define SSD1306_H

#include <msp430.h>

void ssd1306_init(void);
void ssd1306_turn_all_pixels_on(void);
void ssd1306_clear_display(void);
void ssd1306_command(unsigned char command);
void ssd1306_set_position(uint8_t column, uint8_t page);
void ssd1306_print_text(uint8_t x, uint8_t y, char *ptString);
void test_display_pattern(void);

#endif /* SSD1306_H */
