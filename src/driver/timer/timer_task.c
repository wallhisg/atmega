#include <driver/timer/timer_task.h>

timer_queue_ptr timer_queue;

timer_task_ptr timer_task_create(uint16_t pv, event_callback callback, void* arg)
{
    timer_task_ptr timer_task = (timer_task_ptr)malloc(sizeof(timer_task_t));
    if (timer_task == NULL)
    {
        free(timer_task);
        return NULL;
    }
    timer_task->counter = 0;
    timer_task->pv = pv;
    timer_task->state = WAITING;
    timer_task->callback = callback;
    timer_task->arg = arg;
    return timer_task;
}

void timer_task_destroy(timer_task_ptr timer_task)
{
    free(timer_task);
}

timer_queue_ptr timer_queue_create(uint8_t size)
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
    timer_queue = timer_queue_create(TIMER_TASK_SIZE);
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
            {
                timer_queue->task[at]->state = WAITING;
                return timer_queue->task[at];
            }
            else if (timer_queue->task[at]->state == READY)
            {
                timer_queue->task[at]->state = RUNNING;
                return timer_queue->task[at];
            }
            else if (timer_queue->task[at]->state == WAITING)
            {
                timer_queue->task[at]->state = READY;
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
            timer_task_destroy(task);
//             if (at == (timer_queue->size - 1))
            timer_queue->task[at] = NULL;
            timer_queue->length--;
                
        }
    }
}

uint16_t timer_get_counter()
{
    if (timer_queue->task[0] != NULL)
        return timer_queue->task[0]->counter;
    
    return 0;
}

uint8_t get_timer_queue_length()
{
    return timer_queue->length;
}

void task_print()
{
    printf("task print. \r\n");
}
