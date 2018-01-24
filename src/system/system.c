#include <system/system.h>
#include <driver/gpio/gpio.h>
#include <driver/uart/uart.h>

extern event_queue_ptr event_queue;
message_vector_ptr msg_queue;

void system_init()
{

    uart_init(BIT_RATE_9600);
    gpio_init();
    event_queue_init();
    msg_queue = message_vector_create();
}

void system_run()
{
    schedule();
//     event_non_savable_run();
}

void schedule()
{
    event_schedule();
    message_schedule();
//     _delay_ms(500);
}

void event_schedule()
{
    event_t event;
    message_ptr msg = NULL;

    while (event_queue_length() > 0)
    {
        event = event_dequeue();

        if (event.priority == EVENT_PRIORITY_HIGH)
        {
            dispatch(event);
        }
        else if (event.priority == EVENT_PRIORITY_LOW)
        {
            msg->type = event.id;
            msg->pData = event.callback();
            
            message_add(msg_queue, msg);
        }
        m_debug();
    }    
}

void message_schedule()
{
    if (msg_queue->size > 0)
    {
        message_ptr   msg;
        msg = message_get(msg_queue);
        printf("msg_out %s\r\n", msg->pData); 
        json_process(msg->pData);
    }
}

void dispatch(event_t event)
{
    if (event.callback != NULL)
    {
        event.callback();
    }
}

void json_process(uint8_t* str)
{
    json_schema_ptr schema = json_schema_create();
    if (schema != NULL)
    {
        schema->str = uint8_to_char(str);
        json_schema_ptr new_schema  = json_parser(schema->str);

        if (new_schema->type == TYPE_STRING)
        {
            printf("json output string: %s\r\n", new_schema->str);
        }
        else if (new_schema->type == TYPE_OBJECT)
        {
            json_object_ptr head = NULL;
            head = json_parser_object(new_schema->str, head);
            if (strcmp(head->key, KEY_WRITE_GPIO) == 0)
            {
                printf("Writing GPIO. \r\n");
                gpio_blinky();
            }
            printf_key_value(head);
            delete_json_list(head);
        }
        free(schema->str);
        free(schema);
        free(new_schema->str);
        free(new_schema);    
    }
}

int get_free_memory()
{
    extern char __bss_end;
    extern char *__brkval;

    int free_memory;

    if((int)__brkval == 0)
        free_memory = ((int)&free_memory) - ((int)&__bss_end);
    else
        free_memory = ((int)&free_memory) - ((int)__brkval);

    return free_memory;
}
