#ifndef _EVENT_H_
#define _EVENT_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <c_def.h>

#define event_init              (event_t){0,EVENT_PRIORITY_LOW, NULL}, NULL

typedef void* (*event_callback)(void*);

typedef enum {
    EVENT_PRIORITY_LOW,
    EVENT_PRIORITY_MEDIUM,
    EVENT_PRIORITY_HIGH
} event_priority_e;

typedef struct event_t {
    uint16_t id;
    event_priority_e priority;
    event_callback callback;
    struct event_t* next;
} event_t;

typedef event_t* event_ptr;

typedef struct event_queue_t {
    uint8_t length;
    event_ptr event;
} event_queue_t;

typedef event_queue_t* event_queue_ptr;

event_ptr event_create(event_t event, event_ptr next);
void event_destroy(event_ptr event);

void event_queue_init();
event_queue_ptr event_queue_create();
void event_queue_destroy();

void event_enqueue(event_t event);
event_t event_dequeue();
uint8_t event_queue_length();

void event_dispatch(event_t event);

#endif  //  _EVENT_H_
