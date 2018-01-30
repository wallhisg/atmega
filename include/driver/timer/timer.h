#ifndef _TIMER_H_
#define _TIMER_H_

#include <stdlib.h>
#include <avr/io.h>
#include <avr/iom16.h>
#include <avr/interrupt.h>

#include <system/register.h>
#include <driver/gpio/gpio.h>
#include <driver/timer/timer_task.h>

#define F_OSC                           16
#define T0_DELAY_1MS_VALUE              (256-F_OSC)
#define T0_DELAY_10MS_VALUE             256-10*F_OSC

// TIMER0 - 8 bit
#define TCNT0_ADDR                      0x52
#define TCCR0_ADDR                      0x53
#define TIMSK_ADDR                      0x59

#define T0_NO_CLOCK_SOURCE              0x00
#define T0_PRESCALE_1_DIV_1             0x01
#define T0_PRESCALE_1_DIV_8             0x02
#define T0_PRESCALE_1_DIV_64            0x03
#define T0_PRESCALE_1_DIV_256           0x04
#define T0_PRESCALE_1_DIV_1024          0x05
#define T0_EXT_CLOCK_ON_FALLING_T0_PIN  0x06
#define T0_EXT_CLOCK_ON_RASING_T0_PIN   0x07


void timer_init();

void timer0_isr(void) asm("__vector_9") __attribute__ ((signal, __INTR_ATTRS));

#endif  //  _TIMER_H_
