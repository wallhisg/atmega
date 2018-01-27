#include <driver/timer/timer.h>

void timer_init()
{
    register_write_byte(TCCR0_ADDR, T0_PRESCALE_1_DIV_1024);
    register_write_byte(TCNT0_ADDR, T0_DELAY_1MS_VALUE);
    // enable interrupt timer 0 - Set T0IE0
    register_set_bit(TIMSK_ADDR, BIT0);
}

void timer0_isr(void)
{
    register_write_byte(TCNT0_ADDR, T0_DELAY_10MS_VALUE);
    gpio_toggle_pin(PORT_B, BIT3);
}
