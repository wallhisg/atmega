#ifndef _TIMER_TASK_H_
#define _TIMER_TASK_H_

#include <stdio.h>		
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <system/event.h>

#define TIMER_TASK_SIZE     3

typedef void (*vCallBack)(void);

typedef enum {
    RUNNING,
    READY,
    WAITING
} task_status_e;

typedef struct {
    uint16_t counter;
    task_status_e state;
    event_callback vCallback;
} timer_task_t;

typedef timer_task_t* timer_task_ptr;

typedef struct {
    timer_task_t ** task;
    uint8_t size;
    uint8_t length;
} timer_queue_t;

typedef timer_queue_t* timer_queue_ptr;

timer_task_ptr create_timer_task(uint16_t counter, event_callback callback);
void destroy_timer_task(timer_task_ptr timer_task);

void timer_queue_init();
timer_queue_ptr create_timer_queue(uint8_t size);
bool timer_add_task(timer_task_ptr tm_task);
timer_task_ptr timer_get_task();
void timer_remove_task(timer_task_ptr task);
uint16_t timer_get_counter();

void task_print();

#endif  //  _TIMER_TASK_H_
