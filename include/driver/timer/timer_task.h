#ifndef _TIMER_TASK_H_
#define _TIMER_TASK_H_

#include <stdio.h>		
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <system/event.h>

#define TIMER_TASK_SIZE     3

typedef enum {
    RUNNING,
    READY,
    WAITING
} task_status_e;

typedef struct {
    uint16_t counter;
    uint16_t pv;
    task_status_e state;
    event_callback callback;
    void* arg;
} timer_task_t;

typedef timer_task_t* timer_task_ptr;

typedef struct {
    timer_task_t ** task;
    uint8_t size;
    uint8_t length;
} timer_queue_t;

typedef timer_queue_t* timer_queue_ptr;

timer_task_ptr timer_task_create(uint16_t pv, event_callback callback, void* arg);
void timer_task_destroy(timer_task_ptr timer_task);

void timer_queue_init();
timer_queue_ptr timer_queue_create(uint8_t size);
bool timer_add_task(timer_task_ptr tm_task);
timer_task_ptr timer_get_task();
void timer_remove_task(timer_task_ptr task);
uint16_t timer_get_counter();
uint8_t get_timer_queue_length();
void task_print();

#endif  //  _TIMER_TASK_H_
