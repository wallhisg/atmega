#ifndef _SYSTEM_H_
#define _SYSTEM_H_

#include <stdio.h>
#include <util/delay.h>

#include <system/register.h>
#include <driver/gpio/gpio.h>
#include <driver/uart/uart.h>
#include <system/event.h>
#include <system/message.h>
#include <json/json.h>
#include <json/json_parser.h>
#include <json/json_list.h>
#include <json/json_parser_object.h>
#include <system/event_manager.h>

void system_init();
void system_run();
void schedule();
void event_schedule();
void message_schedule();
void dispatch(event_t event);

void json_process(uint8_t* str);

int get_free_memory();

#endif  //  _SYSTEM_H_
