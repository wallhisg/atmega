#include <driver/timer/timer.h>

void timer_init()
{
    register_write_byte(TCCR0_ADDR, T0_PRESCALE_1_DIV_1024);
    register_write_byte(TCNT0_ADDR, T0_DELAY_1MS_VALUE);
    // enable interrupt timer 0 - Set T0IE0
    register_set_bit(TIMSK_ADDR, BIT_0);
    
    timer_queue_init();
    // Blinky led
    gpio_port_ptr port1 = gpio_port_create(PORT_B, BIT_6);
    timer_task_ptr task1 = timer_task_create(10, gpio_blinky, port1);
    timer_add_task(task1);
    
    gpio_port_ptr port2 = gpio_port_create(PORT_B, BIT_7);
    timer_task_ptr task2 = timer_task_create(10, gpio_blinky, port2);
    timer_add_task(task2);
}


void timer0_isr(void)
{
    register_write_byte(TCNT0_ADDR, T0_DELAY_10MS_VALUE);
    gpio_toggle_pin(PORT_B, BIT_2);
    
    timer_task_ptr task = timer_get_task();
    if (task != NULL)
    {
        task->counter++;
        if (task->counter > task->pv)
        {
            task->counter = 0;
            
            if (task->callback != NULL)
            {
                gpio_toggle_pin(PORT_B, BIT_3);
                task->callback(task->arg);
                timer_remove_task(task);
                printf("get_timer_queue_length %d\r\n", get_timer_queue_length());                
            }
        }
    }


}

