#include <system/register.h>

static port_t PORT[4];

void register_init()
{
    PORT[1].addr = PIN_B_ADDR;
    PORT[2].addr = PIN_C_ADDR;
    PORT[3].addr = PIN_D_ADDR;
    
    PORT[1].mask = 0xFF;
    PORT[2].mask = 0xFF;
    PORT[3].mask = 0xFF;
    
    PORT[1].lock_byte = false;
    PORT[2].lock_byte = false;
    PORT[3].lock_byte = false;
    
    PORT[1].lock_bit = false;
    PORT[2].lock_bit = false;
    PORT[3].lock_bit = false;    
}

void register_port_write_byte(PORT_X port, uint8_t value)
{
    if (!PORT[port].lock_byte)
    {
        const int addr = PORT[port].addr + PORT_OFFSET;
        volatile register_size* ADDR = (void *)(addr);
        *ADDR = value;
    }
}

void register_ddr_write_byte(PORT_X port, uint8_t value)
{
    if (!PORT[port].lock_byte)
    {
        const int addr = PORT[port].addr + DDR_OFFSET;
        volatile register_size* ADDR = (void *)(addr);
        *ADDR = value;
    }
}

void register_port_set_bit(PORT_X port, BIT_X bit)
{
    const int addr = PORT[port].addr + PORT_OFFSET;
    volatile register_size* ADDR = (void *)(addr);
    *ADDR |= _BV(bit);    
}

void register_port_clear_bit(PORT_X port, BIT_X bit)
{
    const int addr = PORT[port].addr + PORT_OFFSET;
    volatile register_size* ADDR = (void *)(addr);
    *ADDR &= ~_BV(bit);    
}

void register_port_toggle_bit(PORT_X port, BIT_X bit)
{
    const int addr = PORT[port].addr + PORT_OFFSET;
    volatile register_size* ADDR = (void *)(addr);
    *ADDR ^= _BV(bit);
}


void register_ddr_set_bit(PORT_X port, BIT_X bit)
{
    const int addr = PORT[port].addr + DDR_OFFSET;
    volatile register_size* ADDR = (void *)(addr);
    *ADDR |= _BV(bit);    
}

void register_ddr_clear_bit(PORT_X port, BIT_X bit)
{
    const int addr = PORT[port].addr + DDR_OFFSET;
    volatile register_size* ADDR = (void *)(addr);
    *ADDR &= ~_BV(bit);    
}

bool register_pin_read_bit(PORT_X port, BIT_X bit)
{
    if (PORT[port].mask & _BV(bit))
    {
        const int addr = PORT[port].addr + PIN_OFFSET;
        volatile register_size* ADDR = (void *)(addr);
        return ((*ADDR & _BV(bit)) ? 1 : 0 );
    }
    return 1;   // inactive
}

void register_pin_lock(PORT_X port, BIT_X bit)
{
    PORT[port].mask &= ~_BV(bit);
}

void register_pin_unlock(PORT_X port, BIT_X bit)
{
    PORT[port].mask |= _BV(bit);
}


void register_write_byte(uint16_t addr, uint8_t value)
{
    volatile register_size* ADDR = (void *)(addr);
    *ADDR = value;
}

void register_set_bit(uint16_t addr, BIT_X bit)
{
    volatile register_size* ADDR = (void *)(addr);
    *ADDR |= _BV(bit);
}

void register_clear_bit(uint16_t addr, BIT_X bit)
{
    volatile register_size* ADDR = (void *)(addr);
    *ADDR &= ~_BV(bit);      
}

