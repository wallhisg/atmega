#include <system/message.h>


void message_add(message_vector_ptr vector, message_ptr msg)
{
    if (vector->size + 1 >= vector->length)
    {
        vector->length++;
        vector->message = (message_ptr*)realloc(vector->message, 
                                               sizeof(message_ptr) * vector->length);
    }
    vector->message[vector->size] = msg;
    vector->size++;
}

message_ptr message_get(message_vector_ptr vector)
{
    message_ptr msg = NULL;
    msg->pData = vector->message[0]->pData;
    msg->type = vector->message[0]->type;
    message_remove(vector, msg);
    return msg;
}

void message_remove(message_vector_ptr vector, message_ptr msg)
{
    int8_t at = -1;
    int8_t i = 0;
    for (i = 0; i < vector->size; i++)
    {
        if (vector->message[i] == msg)
        {
            at = i;
            break;
        }
    }
    // deleted msg will be the last
    if (at != -1)
    {
        if (at != vector->size - 1)
            vector->message[at] = vector->message[vector->size - 1];
        
        vector->message[vector->size - 1] = NULL;
        vector->size--;
    }
    
}

message_vector_ptr message_vector_create()
{
    message_vector_ptr vector = (message_vector_ptr)malloc(sizeof(message_vector_t));
    if (vector == NULL)
    {
//         debug(MSG_OBJ_MESSAGE_QUEUE_IS_NULL);
        free(vector);
    }
    
    vector->length = 0;
    vector->size = 0;
    vector->message = NULL;
    
    return vector;
}

void message_vector_destroy(message_vector_ptr vector)
{
    if (vector->length)
        free(vector->message);
    
    free(vector);
}


