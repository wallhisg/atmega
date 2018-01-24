#ifndef _GPIO_H_
#define _GPIO_H_

#include <stdio.h>
#include <stdbool.h>
#include <avr/io.h>
#include <avr/iom16.h>
#include <avr/interrupt.h>
#include <avr/sfr_defs.h>
#include <util/delay.h>

#include <system/event.h>
#include <system/register.h>
#include <c_def.h>

typedef uint8_t register_size;

// PINx is based address
// DDRx = PORTx_ADDR + 1
// PORTx = PORTx_ADDR + 2
typedef enum {
    PORTB_ADDR = 0x36,
    PORTC_ADDR = 0x33,
    PORTD_ADDR = 0x30
} PORT_ADDR;

typedef enum {
    BIT0 = 0x00,
    BIT1 = 0x01,
    BIT2 = 0x02,
    BIT3 = 0x03,
    BIT4 = 0x04,
    BIT5 = 0x05,
    BIT6 = 0x06,
    BIT7 = 0x07
} BIT_X;

void gpio_init();
uint8_t* gpio_blinky();

bool gpio_read_pin_state(PORT_ADDR port, BIT_X bit);
void gpio_input_set(PORT_ADDR port, BIT_X bit);
void gpio_output_set(PORT_ADDR port, BIT_X bit);

void gpio_set_high(PORT_ADDR port, BIT_X bit);
void gpio_set_low(PORT_ADDR port, BIT_X bit);

void int0_isr(void) asm("__vector_1") __attribute__ ((signal, __INTR_ATTRS));
void int1_isr(void) asm("__vector_2") __attribute__ ((signal, __INTR_ATTRS));

#endif  // _GPIO_H_
