#ifndef _GPIO_H_
#define _GPIO_H_

#include <stdio.h>
#include <avr/io.h>
#include <avr/iom16.h>
#include <avr/interrupt.h>
#include <system/event.h>
#include <c_def.h>

#define BLINK_PIN   PINB0

void gpio_init();
uint8_t* gpio_blinky();
void gpio_regist_event();
void int0_isr(void) asm("__vector_1") __attribute__ ((signal, __INTR_ATTRS));
void int1_isr(void) asm("__vector_2") __attribute__ ((signal, __INTR_ATTRS));

#endif  // _GPIO_H_
