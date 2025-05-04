#ifndef GPIO_H
#define GPIO_H

#include <msp430.h>
#include <stdint.h>

#define MAX_PORT_NUM 1
#define MAX_PIN_NUM  7

setup_gpio_input_port_1(uint8_t pin_num);
setup_gpio_input_port_4(uint8_t pin_num);
setup_gpio_output_port_1(uint8_t pin_num);
gpio_toggle_port_1(uint8_t pin_num);
gpio_turn_on_port_1(uint8_t pin_num);
gpio_turn_off_port_1(uint8_t pin_num);

#endif /* GPIO_H */
