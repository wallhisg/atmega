#include <system/event_manager.h>

void blinky(PORT_ADDR port, BIT_X bit)
{
//     volatile register_size* DDR = (register_size *)(port + 1);
//     volatile register_size* PORT = (register_size *)(port + 2);
//     *DDR |= bit;
//     *PORT ^= _BV(bit);
    gpio_output_set(PORTD_ADDR, bit);
}
