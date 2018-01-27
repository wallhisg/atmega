#ifndef _GPIO_H_
#define _GPIO_H_

#include <stdio.h>
#include <stdbool.h>
#include <avr/io.h>
#include <avr/iom16.h>
#include <avr/interrupt.h>
#include <avr/sfr_defs.h>
#include <util/delay.h>

#include <c_def.h>
#include <system/event.h>
#include <system/register.h>

// PINx is based address
// DDRx = PORTx_ADDR + 1
// PORTx = PORTx_ADDR + 2
typedef enum {
    PORTB_ADDR = 0x36,
    PORTC_ADDR = 0x33,
    PORTD_ADDR = 0x30
} PORT_ADDR;


void gpio_init();
uint8_t* gpio_blinky();

void gpio_set_input_bit(PORT_X port, BIT_X bit);
void gpio_set_output_bit(PORT_X port, BIT_X bit);

void gpio_set_pin_high(PORT_X port, BIT_X bit);
void gpio_set_pin_low(PORT_X port, BIT_X bit);
void gpio_toggle_pin(PORT_X port, BIT_X bit);

bool gpio_read_pin_state(PORT_X port, BIT_X bit);

void int0_isr(void) asm("__vector_1") __attribute__ ((signal, __INTR_ATTRS));
void int1_isr(void) asm("__vector_2") __attribute__ ((signal, __INTR_ATTRS));

#endif  // _GPIO_H_
