#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>                
#include <avr/iom16.h>
#include <system/system.h>
#include <stdbool.h>

typedef void (*void_callback)(void);
typedef uint8_t (*uint8_callback)(void);

int main()
{
    system_init();
    printf("Atmega16\r\n");
//     gpio_output_set(PORTD_ADDR, BIT4);
    register_ddr_write_byte(PORT_B, 0xFF);
    register_pin_lock(PORT_D, BIT7);
    while(true)
    {
        if (gpio_read_pin_state(PORT_D, BIT7) | gpio_read_pin_state(PORT_D, BIT6)) 
        {
            printf("active\r\n");
            register_pin_unlock(PORT_D, PIN7);
            
        }
        
//         system_run();
//         blinky(PORTD_ADDR, BIT4);
//         register_port_write_byte(PORT_B, 0xFE);
//         register_port_set_bit(PORT_B, BIT7);
        gpio_toggle_pin(PORT_B, BIT4);
        gpio_set_pin_high(PORT_B, BIT7);
        _delay_ms(250);
//         gpio_set_low(PORTD_ADDR, BIT4);
//         register_port_write_byte(PORT_B, 0xFF);
//         register_port_clear_bit(PORT_B, BIT7);
        gpio_set_pin_low(PORT_B, BIT7);
        _delay_ms(250);
//         register_port_lock(PORT_B);
    }
    return 0;
}
