#include <driver/gpio/gpio.h>


void gpio_init()
{
    gpio_output_set(PORTD_ADDR, BIT1);
	gpio_input_set(PORTD_ADDR, BIT0);

    GICR = 1 << INT0 | 1 << INT1;
    MCUCR = (1 << ISC01 | 0 << ISC00) | (1 << ISC11 | 0 << ISC10);
}

uint8_t* gpio_blinky()
{
    PORTB ^= 1;
    return NULL;
}

// active low
bool gpio_read_pin_state(PORT_ADDR port, BIT_X bit)
{
    gpio_input_set(port, bit);
    volatile register_size* PINs = (void *)(port);
    if (*PINs & _BV(bit))
    {
        
        return false;
    }
    else    // active
    {
        gpio_output_set(port, bit);
        gpio_set_low(port, bit);
        _delay_ms(200);
        return true;
        
    }
}

void gpio_input_set(PORT_ADDR port, BIT_X bit)
{
    volatile register_size* DDR = (void *)(port + 1);
    *DDR &= ~_BV(bit);
    volatile register_size* PORT = (void *)(port + 2);
    *PORT |= _BV(bit);    // enable internal pull-up 
}

void gpio_output_set(PORT_ADDR port, BIT_X bit)
{
    volatile register_size* DDR = (void *)(port + 1);
    *DDR |= _BV(bit); 
}

void gpio_set_high(PORT_ADDR port, BIT_X bit)
{
    gpio_output_set(port, bit);
    volatile register_size* PORT = (void *)(port + 2);
    *PORT |= _BV(bit);
}

void gpio_set_low(PORT_ADDR port, BIT_X bit)
{
    gpio_output_set(port, bit);
    volatile register_size* PORT = (void *)(port + 2);
    *PORT &= ~_BV(bit);
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
