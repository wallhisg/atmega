#include <system/event.h>

event_queue_ptr event_queue;

void event_queue_init()
{
    event_queue = event_queue_create();
}

event_queue_ptr event_queue_create()
{
    event_queue_ptr new_events = (event_queue_ptr)malloc(sizeof(event_queue_t));
    if (new_events == NULL)
    {
        debug(MSG_OBJ_EVENT_QUEUE_IS_NULL);
        free(new_events);
        return NULL;
    }
    new_events->length = 0;
    new_events->event = NULL; // first event is always NULL;
    return new_events;
}

void event_enqueue(event_t event)
{
    event_ptr events = event_queue->event;
    event_ptr new_event = event_create(event, NULL);
    if (events == NULL)
    {
        event_queue->event = new_event;
        event_queue->length++;
        return;
    }
    
    // DISABLE_INTERRUPT - pending;
    while (events->next != NULL)
        events = events->next;
    
    events->next = new_event;
    event_queue->length++;
    // ENABLE INTERRUPT - pending;
}

event_t event_dequeue()
{
    if (event_queue->length > 0)
    {
        event_ptr next = event_queue->event->next;
        
        // copy event
        event_t event;
        event.id = event_queue->event->id;
        event.priority = event_queue->event->priority;
        event.callback = event_queue->event->callback;
        
        event_destroy(event_queue->event);

        event_queue->event = next;
        event_queue->length--;
        return event;
    }
    
    return (event_t){0, EVENT_PRIORITY_LOW, NULL};
}
    
void event_queue_destroy()
{
    // destroy events
    event_ptr event, next;
    if (event_queue->event != NULL)
    {
        event = event_queue->event;
        
        while(event != NULL)
        {
            next = event->next;
            free(event);
            event = next;
        }
    }
    
    // destroy event_queue
    free(event_queue);
    
}
uint8_t event_queue_length()
{
    return event_queue->length;
}
event_ptr event_create(event_t event, event_ptr next)
{
    event_ptr new_event = (event_ptr)malloc(sizeof(event_t));
    if (new_event == NULL)
    {
        debug(MSG_OBJ_EVENT_IS_NULL);
        free(new_event);
    }
    new_event->id = event.id;
    new_event->priority = event.priority;
    new_event->callback = event.callback;
    new_event->next = next;

    return new_event;
}

void event_destroy(event_ptr event)
{
//     free(event->callback);
    free(event);
}

void event_dispatch(event_t event)
{
    if (event.callback != NULL)
    {
        event.callback();
    }
}
