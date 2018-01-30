#ifndef _REGISTER_H_
#define _REGISTER_H_

#include <stdio.h>
#include <stdbool.h>
#include <avr/io.h>
#include <avr/iom16.h>
#include <avr/interrupt.h>
#include <avr/sfr_defs.h>
#include <util/delay.h>


typedef uint8_t register_size;

#define PIN_OFFSET      0
#define DDR_OFFSET      1
#define PORT_OFFSET     2

#define PIN_A_ADDR     
#define PIN_B_ADDR       0x36
#define PIN_C_ADDR       0x33
#define PIN_D_ADDR       0x30

typedef enum {
    PORT_A = 0,
    PORT_B = 1,
    PORT_C = 2,
    PORT_D = 3
} PORT_X; 

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

typedef struct {
    register_size addr;
    uint8_t mask;
    bool lock_byte;
    bool lock_bit;
} port_t;

void register_init();

void register_write_byte(int addr, uint8_t value);
void register_set_bit(int addr, BIT_X bit);
void register_clear_bit(int addr, BIT_X bit);

void register_port_write_byte(PORT_X port, uint8_t value);
void register_ddr_write_byte(PORT_X port, uint8_t value);

void register_port_set_bit(PORT_X port, BIT_X bit);
void register_port_clear_bit(PORT_X port, BIT_X bit);
void register_port_toggle_bit(PORT_X port, BIT_X bit);

void register_ddr_set_bit(PORT_X port, BIT_X bit);
void register_ddr_clear_bit(PORT_X port, BIT_X bit);

bool register_pin_read_bit(PORT_X port, BIT_X bit);
void register_pin_lock(PORT_X port, BIT_X bit);
void register_pin_unlock(PORT_X port, BIT_X bit);

#endif  //  _REGISTER_H_
