#ifndef _EVENT_MANAGER_H_
#define _EVENT_MANAGER_H_

//  The interface control io of peripheral
//  
#include <stdlib.h>
#include <stdint.h>
#include <driver/gpio/gpio.h>


void event_gpio_dispatch(void *args);


#endif  //  _EVENT_MANAGER_H_
