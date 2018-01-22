#ifndef _JSON_PARSER_OBJECT_H_
#define _JSON_PARSER_OBJECT_H_

#include <stdio.h>
#include <stdbool.h>
#include <json/json.h>
#include <json/json_parser.h>
#include <json/json_list.h>

json_object_ptr  json_parser_object(char* json, json_object_ptr head);
json_tuple_flag_t parser_object(char c, json_tuple_flag_t flags);


void printf_key_value(json_object_ptr head);

#endif  // _JSON_PARSER_OBJECT_H_
