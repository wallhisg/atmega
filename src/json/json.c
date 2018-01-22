#include <json/json.h>


json_schema_ptr json_schema_create()
{
    json_schema_ptr new_schema = (json_schema_ptr)malloc(sizeof(json_schema_t));
    
    if (new_schema == NULL)
    {
        free(new_schema);
//         exit(0);
        return NULL;
    }
    new_schema->pos = 0;
    new_schema->str = NULL;
    new_schema->type = TYPE_UNDEFINED;
    return new_schema;
}

key_value_ptr key_value_create()
{
    key_value_ptr key_value = (key_value_ptr)malloc(sizeof(key_value_t));
    
    if (key_value == NULL)
    {
        free(key_value);
        exit(0);
    }
    key_value->key = NULL;
    key_value->value = NULL;
    
    return key_value;
}

char * uint8_to_char(uint8_t* str)
{
    uint8_t counter = 0;
    uint8_t idx = 0;
    
    while (str[idx++] != '\0')
        counter++;
    
    counter++;
    
    char* out_str = (char*)malloc(counter * sizeof(char));
    
    for (idx = 0; idx < counter; idx++)
        out_str[idx] = (char)str[idx];
    
    free(str);
    
    return out_str;
}
