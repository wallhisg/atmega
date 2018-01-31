#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>                
#include <avr/iom16.h>
#include <system/system.h>
#include <stdbool.h>


int main()
{
    system_init();
    printf("Atmega16\r\n");

    while(true)
    {
        if (gpio_read_pin_state(PORT_D, BIT_6))
        {
            printf("pin activer \r\n");
            gpio_lock_pin(PORT_D, BIT_6);
            gpio_port_ptr port = gpio_port_create(PORT_D, BIT_6);
            timer_task_ptr task1 = timer_task_create(1000, gpio_unlock_pin, port);
            timer_add_task(task1);
        }
        system_run();
       
//         printf("mem free %d\r\n", get_free_memory());
//         _delay_ms(500);
    }
    return 0;
}
