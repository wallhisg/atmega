#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>                
#include <avr/iom16.h>
#include <system/system.h>
#include <stdbool.h>

typedef void (*void_callback)(void);
typedef uint8_t (*uint8_callback)(void);



int main(int argc, char *argv[])
{
    system_init();
    printf("Atmega16\r\n");
    gpio_output_set(PORTD_ADDR, BIT4);

    while(true)
    {
        if (gpio_read_pin_state(PORTD_ADDR, BIT7))
            printf("active\r\n");
        
        system_run();
//         blinky(PORTD_ADDR, BIT4);
        gpio_set_high(PORTD_ADDR, BIT4);
        _delay_ms(250);
        gpio_set_low(PORTD_ADDR, BIT4);
        _delay_ms(250);
    }
    return 0;
}
