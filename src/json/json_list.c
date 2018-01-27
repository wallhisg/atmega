#include <json/json_list.h>

json_object_ptr json_create_object(char* key, char* value, 
                                     json_object_ptr next)
{
    json_object_ptr new_object = (json_object_ptr)malloc(sizeof(json_object_t));
    if (new_object == NULL)
    {
        printf("Error creating a new object.\n");
        exit(0);
    }
    
    uint8_t len = strlen(key) + 1;
    new_object->key = (char*)malloc(len * sizeof(char));
    memcpy(new_object->key, key, len);
    
    len = strlen(value) + 1;
    new_object->value = (char*)malloc(len * sizeof(char));
    memcpy(new_object->value, value, len);
    new_object->next = next;
    
    return new_object;
}

json_object_ptr json_object_init(char* key, char* value, 
                                   json_object_ptr head)
{
    json_object_ptr new_object = json_create_object(key, value, head);
    head = new_object;
    return head;
}
/*
    insert a new node after the prev node
*/
json_object_ptr json_object_insert(char* key, char* value, json_object_ptr head)
{
    if (head == NULL )
    {
        head = json_object_init(key, value, head);
        return head;
    }
    else
    {
        json_object_ptr cursor = head;
        while(cursor->next != NULL)
            cursor = cursor->next;
        
        cursor->next = json_create_object(key, value, NULL);
        return head;
    }
}

json_object_ptr json_object_search(char* key, json_object_ptr head)
{
    json_object_ptr cursor = head;
    while(cursor != NULL)
    {
        if (!strcmp(cursor->key, key))
        {
            return cursor;
        }
        cursor = cursor->next;
    }
    return NULL;
}

json_object_ptr json_object_update(char* key, char* value, json_object_ptr head)
{
    json_object_ptr tmp = NULL;
    tmp = json_object_search(key, head);
    if (tmp != NULL)
    {
        free(tmp->value);
        int len = strlen(value) + 1;
        tmp->value = (char*)malloc(len * sizeof(char));
        memcpy(tmp->value, value, len-1);
        return tmp;
    }
    return NULL;
}

void delete_json_list(json_object_ptr head)
{
    json_object_ptr cursor, tmp;
    if (head != NULL)
    {
        cursor = head->next;
        head->next = NULL;
        while(cursor != NULL)
        {
            tmp = cursor->next;
            free(cursor->key);
            free(cursor->value);
            free(cursor);
            cursor = tmp;
        }
        free(head->key);
        free(head->value);
        free(head);
    }
}
