#include <json/json_parser.h>

/********************************************************************
 * FunctionName : json_get_type
 * Description  : get json type:    TYPE_UNDEFINED  TYPE_STRING
 *                                  TYPE_OBJECT     TYPE_ARRAY
 * Parameter    : char*
 * Return       : json_get_type
 * NOTE repair case {"a" -> fixed by tok_counter
********************************************************************/
json_schema_ptr json_parser(char* json)
{
    json_tuple_flag_t flags;
    flags.tok = JEX_LETTER_START;
    flags.tribool = TRIBOOL_INDETERMINATE;
    flags.type = TYPE_UNDEFINED;
    flags.pos = 0;
    
    uint8_t begin = 0;
    uint8_t end = strlen(json);
    uint8_t index = 0;
    char* json_ = (char*)malloc((end +1) * sizeof(char));
    
    // token counter, if counter is even return true
    uint8_t tok_counter = 0;
    
    // verify schema
    for (begin = 0; begin <= end; begin++ )
    {
        flags = consume_char(json[begin], flags);
        
        if (is_tok_letter(json[begin]))
            tok_counter++;

        if (flags.tribool == TRIBOOL_FALSE)
        {
            flags.type = TYPE_UNDEFINED;
            flags.pos = begin;

//             printf("Error pos %u\n", begin);

            break;
        }
        else if (flags.tribool == TRIBOOL_TRUE )
            json_[index++] = json[begin];

    }
    
    tok_counter = tok_counter % 2;
    if (tok_counter)
        flags.tribool = TRIBOOL_INDETERMINATE;
    
    json_schema_ptr schema = json_schema_create();
    if (flags.tribool == TRIBOOL_FALSE || flags.tribool == TRIBOOL_INDETERMINATE)
    {
        schema->pos = begin;
        schema->type = TYPE_UNDEFINED;
        free(schema);
        return NULL;
    }
    else
    {
        schema->str = (char*)malloc(index * sizeof(char));
        memcpy(schema->str, json_, index-1);
        schema->type = flags.type;
        
        free(json_);
        return schema;        
    }
}

/********************************************************************
 * FunctionName : consume
 * Description  :
 * Parameter    : char, json_tuple_flag_t
 * Return       : json_tuple_flag_t
********************************************************************/
json_tuple_flag_t consume_char(char c, json_tuple_flag_t flags)
{
    json_tuple_flag_t flags_ = flags;
    
    switch(flags_.tok)
    {
        case JEX_LETTER_START:
            if ( c == '\"')
            {
                flags_.tok = JEX_DQ_MARK;
                flags_.tribool = TRIBOOL_INDETERMINATE;
                flags_.type = TYPE_STRING;
                return flags_;
            }
            else if (c == '{')
            {
                flags_.tok = JTK_L_CURLY;
                flags_.tribool = TRIBOOL_INDETERMINATE;
                flags_.type = TYPE_OBJECT;
                return flags_;                
            }
            else if ((c != LF) || (c != CR) || (c != '\0'))
            {
                flags_.tribool = TRIBOOL_FALSE;
                flags_.type = TYPE_UNDEFINED;
                flags_.pos = 1;
                return flags_;                   
            }
            else 
            {
                flags_.tok = JEX_LETTER_START;
                flags_.tribool = TRIBOOL_INDETERMINATE;
                flags_.type = TYPE_UNDEFINED;
                return flags_;   
            }
            break;
        // case "
        case JEX_DQ_MARK:
            if (isalpha(c) || isdigit(c))
            {
                flags_.tok = JEX_LETTER;
                flags_.tribool = TRIBOOL_TRUE;
                return flags_;
            }
            else if (c == ':')
            {
                flags_.tok = JTK_COLON;
                flags_.tribool = TRIBOOL_TRUE;
                return flags_;
            }
            else if (c == ',')
            {
                flags_.tok = JTK_COMMA;
                flags_.tribool = TRIBOOL_TRUE;
                return flags_;
            }
            else if (c == '}')
            {
                flags_.tok = JTK_R_CURLY;
                flags_.tribool = TRIBOOL_TRUE;
                return flags_;
            }
            else if ((c == '\0') || (c == '\r') || (c == '\n'))
            {
                flags_.tribool = TRIBOOL_TRUE;
                return flags_;
            }
            else 
            {
                flags_.tribool = TRIBOOL_INDETERMINATE;
                return flags_;
            }
            break;            
        // case {
        case JTK_L_CURLY:
            if (c == '\"')
            {
                flags_.tok = JEX_DQ_MARK;
                flags_.tribool = TRIBOOL_TRUE;
                return flags_;
            }
            else if (isspace(c))
            {
                flags_.tribool = TRIBOOL_INDETERMINATE;
                return flags_;                
            }
            else 
            {
//                 flags_.tribool = TRIBOOL_INDETERMINATE;
                flags_.tribool = TRIBOOL_FALSE;
                return flags_;
            }
            break;
        // case  }
        case JTK_R_CURLY:
            if ((c == '\0') || (c == '\r') || (c == '\n'))
            {
                flags_.tribool = TRIBOOL_TRUE;
                return flags_;
            }
            else 
            {
                    flags_.tribool = TRIBOOL_INDETERMINATE;
                    return flags_;
            }
            break;
        // case :
        case JTK_COLON:
            if (c == '\"')
            {
                flags_.tok = JEX_LETTER;
                flags_.tribool = TRIBOOL_TRUE;
                return flags_;
            }
            else
            {
                flags_.tribool = TRIBOOL_INDETERMINATE;
                return flags_;
            }            
            break;
        // ,
        case JTK_COMMA:
            if (c == '\"')
            {
                flags_.tok = JEX_DQ_MARK;
                flags_.tribool = TRIBOOL_TRUE;
                return flags_;
            }
            else
            {
                flags_.tribool = TRIBOOL_INDETERMINATE;
                return flags_;
            }
            break;
        case JEX_LETTER:
            if (isalpha(c) || isdigit(c))
            {
                flags_.tok = JEX_LETTER;
                flags_.tribool = TRIBOOL_TRUE;
                return flags_;
            }
            else if ((c == '\"') && (flags_.type == TYPE_STRING))
            {
                flags_.tok = JEX_DQ_MARK;
                flags_.tribool = TRIBOOL_INDETERMINATE;
                return flags_;
            }
            else if ((c == '\"') && (flags_.type == TYPE_OBJECT))
            {
                flags_.tok = JEX_DQ_MARK;
                flags_.tribool = TRIBOOL_TRUE;
                return flags_;
            }
            else if ((c == ':') || (c == ','))
            {
                flags_.tribool = TRIBOOL_FALSE;
                return flags_;
            }
            else {
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
    return  flags_;
}

bool is_tok_letter(const char c)
{
    bool flag;
    switch (c)
    {
        
        case '{': case '}': case '\"': case '[': case ']':         
            flag = true;
            break;
        default:
            flag = false;
    }
    
    return flag;
}
