#ifndef _JSON_H_
#define _JSON_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

typedef unsigned char uint8_t;

#define LF      0x0A    //  '\n'
#define CR      0x0D    //  '\r'

#define KEY_SIZE    8
#define VAL_SIZE    8
#define OBJ_SIZE    (KEY_SIZE + VAL_SIZE)

typedef enum {
    VALUE_STRING    = 0,
    VALUE_NUMBER    = 1,
    VALUE_BOOLEAN   = 2,
    VALUE_NULL      = 3
} json_value_type_e;

typedef enum {
    TYPE_UNDEFINED  = 0,
    TYPE_STRING     = 1,
    TYPE_OBJECT     = 2,
    TYPE_ARRAY      = 3,
    // extra to recognize key - value
    TYPE_KEY        = 4,
    TYPE_VALUE      = 5
} json_type_e;

typedef enum {
    ERROR_NONE      = 0,
    ERROR_SYNTAX    = 1,
    ERROR_UNDEFINED = 2
} json_error_e;

typedef enum {
    TRIBOOL_FALSE = 0,
    TRIBOOL_TRUE = 1,
    TRIBOOL_INDETERMINATE = 2
} tribool_e;
// six struct tokens
typedef enum {
    JTK_L_CURLY,        //  {
    JTK_R_CURLY,        //  }
    JTK_COLON,          //  :
    JTK_COMMA,          //  ,
    // extra token
    JEX_LETTER_START,   //
    JEX_DQ_MARK,        //  "
    JEX_LETTER,         //  letter
    JEX_SPACE           //  space    
} json_token_e;

typedef struct {
    json_token_e tok;
    tribool_e tribool;
    json_type_e type;
    uint8_t pos;
} json_tuple_flag_t;

typedef struct {
    uint8_t pos;
    json_type_e type;
    char* str;
} json_schema_t;

typedef json_schema_t * json_schema_ptr;

json_schema_ptr json_schema_create();

typedef char * json_string;

typedef struct {
    char* key;
    char* value;
} key_value_t;
typedef key_value_t* key_value_ptr;


key_value_ptr key_value_create();

char* uint8_to_char(uint8_t* str);
#endif // _JSON_H_
