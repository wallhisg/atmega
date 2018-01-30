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
        system_run();
       
//         printf("mem free %d\r\n", get_free_memory());
        _delay_ms(500);
    }
    return 0;
}
