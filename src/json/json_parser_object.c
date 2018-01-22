#include <json/json_parser_object.h>


json_object_ptr  json_parser_object(char* json, json_object_ptr head)
{
    printf("json_parser_object:\r\n");
    key_value_ptr key_value = key_value_create();
    key_value->key = (char*)malloc(KEY_SIZE * sizeof(char));
    key_value->value = (char*)malloc(VAL_SIZE * sizeof(char));
    uint8_t key_count = 0;
    uint8_t val_count = 0;
    
    json_tuple_flag_t flags;
    flags.tok = JEX_LETTER_START;
    flags.tribool = TRIBOOL_INDETERMINATE;
    flags.type = TYPE_KEY;
    flags.pos = 0;    
    
    uint8_t begin = 0;
    uint8_t end = strlen(json);
    char c;
    for (begin = 0; begin <= end; begin++)
    {
        c = json[begin];
        if (c == ',')
        {
            key_value->key[key_count] = '\0';
            key_value->value[val_count] = '\0';
            head = json_object_insert(key_value->key, key_value->value, head);
            flags.tok = JEX_LETTER_START;
            flags.tribool = TRIBOOL_INDETERMINATE;
            flags.type = TYPE_KEY;
            flags.pos = 0;

            free(key_value->key);
            free(key_value->value);

            key_value->key = (char*)malloc(KEY_SIZE * sizeof(char));
            key_value->value = (char*)malloc(VAL_SIZE * sizeof(char));
            key_count = 0;
            val_count = 0;
        }
        else if ((c == '\0') || (c == '\r') || (c == '\n'))
        {
            key_value->key[key_count] = '\0';
            key_value->value[val_count] = '\0';
            head = json_object_insert(key_value->key, key_value->value, head);
            
            free(key_value->key);
            free(key_value->value);
            break;
        }
        
        flags = parser_object(c, flags);
        if ((flags.tribool == TRIBOOL_TRUE) && (flags.type == TYPE_KEY))
        {
            key_value->key[key_count++] = c;
        }
        else if ((flags.tribool == TRIBOOL_TRUE) && (flags.type = TYPE_VALUE))
        {
            key_value->value[val_count++] = c;
        }
    }
    free(key_value);
    return head;
}

json_tuple_flag_t parser_object(char c, json_tuple_flag_t flags)
{
    json_tuple_flag_t flags_ = flags;
    switch(flags_.tok)
    {
        case JEX_LETTER_START:
            if (c == '\"')
            {
                flags_.type = TYPE_KEY;
                flags_.tok = JEX_DQ_MARK;
                flags_.tribool = TRIBOOL_INDETERMINATE;
                return flags_;
            }
            else 
            {
                flags_.type = TYPE_KEY;
                flags_.tok = JEX_DQ_MARK;
                flags_.tribool = TRIBOOL_INDETERMINATE;
                return flags_;
            }
            break;
        // CASE "
        case JEX_DQ_MARK:
            if (isalpha(c) || isdigit(c))
            {
                flags_.tok = JEX_LETTER;
                flags_.tribool = TRIBOOL_TRUE;
                return flags_;
            }
            else if (c == ':')
            {
                flags_.type = TYPE_VALUE;
                flags_.tok = JTK_COLON;
                flags_.tribool = TRIBOOL_INDETERMINATE;
                return flags_;
                
            }
            else if (c == ',')
            {
                flags_.type = TYPE_KEY;
                flags_.tok = JTK_COMMA;
                flags_.tribool = TRIBOOL_INDETERMINATE;
                return flags_;
            }
            break;
        // CASE :
        case JTK_COLON:
            if (c == '\"')
            {
                flags_.type = TYPE_VALUE;
                flags_.tok = JEX_DQ_MARK;
                flags_.tribool = TRIBOOL_INDETERMINATE;
                return flags_;
            }
            break;
        // CASE ,
        case JTK_COMMA:
            if (c == '\"')
            {
                flags_.type = TYPE_KEY;
                flags_.tok = JEX_DQ_MARK;
                flags_.tribool = TRIBOOL_INDETERMINATE;
                return flags_;
            }
            break;
        // CASE A -> Z, 0 -> 1
        case JEX_LETTER:
            if (isalpha(c) || isdigit(c))
            {
                flags_.tok = JEX_LETTER;
                flags_.tribool = TRIBOOL_TRUE;
                return flags_;
            }
            else if (c == '\"')
            {
                flags_.tok = JEX_DQ_MARK;
                flags_.tribool = TRIBOOL_INDETERMINATE;
                return flags_;
            }
            break;
        default:
        {
            flags_.tribool = TRIBOOL_INDETERMINATE;
            return flags_;
        }
    }
    return flags_;
}

void printf_key_value(json_object_ptr head)
{
    json_object_ptr cursor = head;
    while (cursor != NULL)
    {
        printf("Key: %s\r\n", cursor->key);
        printf("Value: %s\r\n", cursor->value);
        cursor = cursor->next;
    }
    free(cursor);
}
