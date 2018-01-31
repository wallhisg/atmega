#include <driver/gpio/gpio.h>

void gpio_init()
{
    gpio_set_input_bit(PORT_D, BIT_0);
    gpio_set_output_bit(PORT_D, BIT_1);

    GICR = 1 << INT0 | 1 << INT1;
    MCUCR = (1 << ISC01 | 0 << ISC00) | (1 << ISC11 | 0 << ISC10);
}

gpio_port_ptr gpio_port_create(PORT_X port, BIT_X bit)
{
    gpio_port_ptr port_ = (gpio_port_ptr)malloc(sizeof(gpio_port_t));
    if (port_ == NULL)
    {
        free(port_);
        return NULL;
    }
    port_->port = port;
    port_->bit = bit;
    return port_;
    
}
void* gpio_blinky(void *args)
{
    gpio_port_ptr port = args;
    gpio_toggle_pin(port->port, port->bit);
    free(port);
    return NULL;
}

// active low
bool gpio_read_pin_state(PORT_X port, BIT_X bit)
{
    gpio_set_input_bit(port, bit);
    if (register_pin_read_bit(port, bit))
    {
        return false;
    }
    else    // active low
    {
        return true;
    }
}

void gpio_set_input_bit(PORT_X port, BIT_X bit)
{
    // write to DDRX 
    // 0 - input;   1 - output
    register_ddr_clear_bit(port, bit);
    // enable internal pull-up 
    register_port_set_bit(port, bit);
}

void gpio_set_output_bit(PORT_X port, BIT_X bit)
{
    // write to DDRX 
    // 0 - input;   1 - output
    register_ddr_set_bit(port, bit);
}

void gpio_set_pin_high(PORT_X port, BIT_X bit)
{
    gpio_set_output_bit(port, bit);
    register_port_set_bit(port, bit);
}

void gpio_set_pin_low(PORT_X port, BIT_X bit)
{
    gpio_set_output_bit(port, bit);
    register_port_clear_bit(port, bit);
}

void gpio_toggle_pin(PORT_X port, BIT_X bit)
{
    gpio_set_output_bit(port, bit);
    register_port_toggle_bit(port, bit);
}

void gpio_lock_pin(PORT_X port, BIT_X bit)
{
    register_pin_lock(port, bit);
}

void* gpio_unlock_pin(void *args)
{
    gpio_port_ptr port = args;
    register_pin_unlock(port->port, port->bit);
    return NULL;
}

void int0_isr()
{
    event_t event;
    event.id = EVENT_ID_INT0;
    event.priority = EVENT_PRIORITY_HIGH;
    
    gpio_port_ptr port = gpio_port_create(PORT_B, BIT_1);
    event.callback = gpio_blinky(port);
    
    event_enqueue(event);
}

void int1_isr()
{
    event_t event;
    event.id = EVENT_ID_INT1;
    event.priority = EVENT_PRIORITY_HIGH;

    gpio_port_ptr port = gpio_port_create(PORT_B, BIT_2);
    event.callback = gpio_blinky(port);

    event_enqueue(event);

}


