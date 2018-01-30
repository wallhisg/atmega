#include <driver/timer/timer_task.h>

timer_queue_ptr timer_queue;

timer_task_ptr create_timer_task(uint16_t counter, event_callback callback)
{
    timer_task_ptr timer_task = (timer_task_ptr)malloc(sizeof(timer_task_t));
    if (timer_task == NULL)
    {
        free(timer_task);
        return NULL;
    }
    timer_task->counter = counter;
    timer_task->state = WAITING;
    timer_task->vCallback = callback;
    return timer_task;
}

void destroy_timer_task(timer_task_ptr timer_task)
{
    free(timer_task);
}

timer_queue_ptr create_timer_queue(uint8_t size)
{
    timer_queue_ptr timer_queue = (timer_queue_ptr)malloc(sizeof(timer_queue_t));
    if (timer_queue == NULL)
    {
        free(timer_queue);
        return NULL;
    }
    timer_queue->size = size;
    timer_queue->length = 0;
    return timer_queue;
}

void timer_queue_init()
{
    timer_queue = create_timer_queue(TIMER_TASK_SIZE);
    if (timer_queue != NULL)
        timer_queue->task = (timer_task_t**)realloc(timer_queue->task, sizeof(timer_task_t*) * timer_queue->size);
    
}

bool timer_add_task(timer_task_ptr tm_task)
{
    uint8_t at = 0;
    
    for (at = 0; at < timer_queue->size; at++)
    {
        if (timer_queue->task[at] == NULL)
        {
            timer_queue->task[at] = tm_task;
            timer_queue->length++;
            return true;
        }
    }
    free(tm_task);
    return false;
}

timer_task_ptr timer_get_task()
{
    uint8_t at = 0;
    
    for (at = 0; at < timer_queue->size; at++)
    {
        if (timer_queue->task[at] != NULL)
        {
            if (timer_queue->task[at]->state == RUNNING)
                return timer_queue->task[at];
            else if (timer_queue->task[at]->state == READY)
            {
                timer_queue->task[at]->state = RUNNING;
                return timer_queue->task[at];
            }
            else
            {
                timer_queue->task[at]->state = READY;
                timer_queue->length--;
                break;
            }
        }
    }
    return NULL;    
}

void timer_remove_task(timer_task_ptr task)
{
    uint8_t at = 0;
    
    for (at = 0; at < timer_queue->size; at++)
    {
        if (timer_queue->task[at] == task)
        {
            destroy_timer_task(task);
//             if (at == (timer_queue->size - 1))
            timer_queue->task[at] = NULL;
                
        }
    }
}

uint16_t timer_get_counter()
{
    if (timer_queue->task[0] != NULL)
        return timer_queue->task[0]->counter;
    
    return 0;
}

void task_print()
{
    printf("task print. \r\n");
}
