#include <driver/gpio/gpio.h>


void gpio_init()
{
    DDRB = 0xFF;

    PORTD = 0b11111110;       //  enable pull up resistor
    
    GICR = 1 << INT0 | 1 << INT1;
    MCUCR = (1 << ISC01 | 0 << ISC00) | (1 << ISC11 | 0 << ISC10);
}

uint8_t* gpio_blinky()
{
    PORTB ^= 1;
    return NULL;
}

void int0_isr()
{
    event_t event;
    event.id = EVENT_ID_INT0;
    event.priority = EVENT_PRIORITY_HIGH;
    event.callback = gpio_blinky;
    event_enqueue(event);
}

void int1_isr()
{
    event_t event;
    event.id = EVENT_ID_INT1;
    event.priority = EVENT_PRIORITY_HIGH;
    event.callback = gpio_blinky;
    event_enqueue(event);

}
