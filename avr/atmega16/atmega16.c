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

    while(true)
    {
     
        system_run();
//         _delay_ms(4500);

    }
    return 0;
}
