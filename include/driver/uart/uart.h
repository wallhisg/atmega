#ifndef _UART_H_
#define _UART_H_

#include <stdio.h>
#include <ctype.h>
#include <avr/io.h>
#include <avr/iom16.h>
#include <avr/interrupt.h>
#include <avr/signal.h>
#include <string.h>
#include <driver/uart/ring_buffer.h>
#include <system/event.h>


typedef uint8_t uint8_t;

typedef enum {
    BIT_RATE_300 = 300,
    BIT_RATE_600 = 600,
    BIT_RATE_1200 = 1200,
    BIT_RATE_2400 = 2400,
    BIT_RATE_4800 = 4800,
    BIT_RATE_9600   = 9600,
    BIT_RATE_19200  = 19200,
    BIT_RATE_38400  = 38400,
    BIT_RATE_57600  = 57600,
    BIT_RATE_74880  = 74880,
    BIT_RATE_115200 = 115200,
    BIT_RATE_230400 = 230400,
    BIT_RATE_460800 = 460800,
    BIT_RATE_921600 = 921600,
    BIT_RATE_1843200 = 1843200,
    BIT_RATE_3686400 = 3686400,
} UartBautRate;



typedef struct {
    bool    ctrl;
    uint8_t counter;
} uart_signal_t;


void uart_config(UartBautRate baud);
void uart_init();
int uart_tx_one_byte(char tx_char, FILE *stream);
int uart_rx_one_byte(FILE *stream);

// Interrupt usart
void uart_tx_isr(void) asm("__vector_13") __attribute__ ((signal, __INTR_ATTRS));
void uart_rx_isr(void) asm("__vector_11") __attribute__ ((signal, __INTR_ATTRS));

void uart_regist_event();

const uint8_t uart_read_byte();
void* uart_read_frame();
const uint8_t uart_get_byte_used();
void uart_signal_reset();
const uint8_t uart_signal_counter();



#endif

