#ifndef _MESSAGE_H_
#define _MESSAGE_H_

#include <stdlib.h>
#include <stdint.h>
#include <c_def.h>

// define Instruction register size 


typedef struct {
    uint16_t type;
    uint8_t* pData;
} message_t;

typedef message_t* message_ptr;

typedef struct {
    message_t **message;
    uint8_t size;
    uint8_t length;
} message_vector_t;

typedef message_vector_t* message_vector_ptr;

void message_process();


void message_add(message_vector_ptr vector, message_ptr msg);
message_ptr message_get(message_vector_ptr vector);
void message_remove(message_vector_ptr vector, message_ptr msg);

message_vector_ptr message_vector_create();
void message_vector_destroy(message_vector_ptr vector);

#endif  //  _MESSAGE_H_
