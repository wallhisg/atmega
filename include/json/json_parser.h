#ifndef _JSON_PARSER_H_
#define _JSON_PARSER_H_

#include <ctype.h>
#include <json/json.h>

/********************************************************************
 * FunctionName : json_get_type
 * Description  : get json type:    TYPE_UNDEFINED  TYPE_STRING
 *                                  TYPE_OBJECT     TYPE_ARRAY
 * Parameter    : char*
 * Return       : json_get_type
********************************************************************/
json_schema_ptr json_parser(char* json);

/********************************************************************
 * FunctionName : consume
 * Description  :
 * Parameter    : json_tuple_flag_t
 * Return       : json_tuple_flag_t
********************************************************************/
json_tuple_flag_t consume_char(char c, json_tuple_flag_t flags);

/********************************************************************
 * FunctionName : is_tok_letter
 * Description  : Return true if letter is JTK
 * Parameter    : char
 * Return       : bool
********************************************************************/
bool is_tok_letter(const char c);

#endif  // _JSON_PARSER_H_
