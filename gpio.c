#include "gpio.h"
#include <msp430.h>
#include <stdint.h>

setup_gpio_input_port_1(uint8_t pin_num)
{
    if (pin_num > 7) {
        return;
    }

    P1DIR |= ~(1 << pin_num);       // Set as input
    P1REN |=  (1 << pin_num);       // Enable pull/up down resistor
    P1OUT |=  (1 << pin_num);       // Set resistor to pull-up
    P1IES |=  (1 << pin_num);       // Set from H > L
    P1IFG |= ~(1 << pin_num);       // Clear IRQ Flag
    P1IE  |=  (1 << pin_num);       // Enable IRQ
}

setup_gpio_input_port_4(uint8_t pin_num)
{
    if (pin_num > 7) {
        return;
    }

    P4DIR |= ~(1 << pin_num);       // Set as input
    P4REN |=  (1 << pin_num);       // Enable pull/up down resistor
    P4OUT |=  (1 << pin_num);       // Set resistor to pull-up
    P4IES |=  (1 << pin_num);       // Set from H > L
    P4IFG |= ~(1 << pin_num);       // Clear IRQ Flag
    P4IE  |=  (1 << pin_num);       // Enable IRQ
}

setup_gpio_output_port_1(uint8_t pin_num)
{
    if (pin_num > 7) {
        return;
    }

    P1DIR |= (1 << pin_num);    // Set as output
    P1OUT |= ~(1 << pin_num);   // Clear the pin
}

gpio_toggle_port_1(uint8_t pin_num)
{
    if (pin_num > 7) {
        return;
    }

    P1OUT ^= (1 << pin_num);
}


gpio_turn_on_port_1(uint8_t pin_num)
{
    if (pin_num > 7) {
        return;
    }

    P1OUT &= ~(1 << pin_num);
}

gpio_turn_off_port_1(uint8_t pin_num)
{
    if (pin_num > 7) {
        return;
    }

    P1OUT |= (1 << pin_num);
}

