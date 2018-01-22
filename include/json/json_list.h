#ifndef _LIST_H_
#define _LIST_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef unsigned char uint8_t;

typedef struct json_object_t{
    char *key;
    char *value;
    struct json_object_t* next;
} json_object_t;
typedef json_object_t *json_object_ptr;


typedef void (*json_object_push)(json_object_ptr object);

json_object_ptr json_create_object(char* key, char* value, 
                                     json_object_ptr next);

json_object_ptr json_object_init(char* key, char* value, 
                                   json_object_ptr head);

json_object_ptr json_object_insert(char* key, char* value, json_object_ptr head);

json_object_ptr json_object_search(char* key, json_object_ptr head);
void delete_json_list(json_object_ptr head);void delete_json_list(json_object_ptr head);
json_object_ptr json_object_update(char* key, char* value, json_object_ptr head);


#endif  // _LIST_H_
