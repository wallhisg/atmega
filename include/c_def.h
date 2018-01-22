#ifndef _C_TYPE_H_
#define _C_TYPE_H_

#include <stdio.h>
// system debug
#define SYS_DEBUG           1

#if (SYS_DEBUG)
    #define debug(msg)          printf("err: %02x\r\n", msg);
#else
    #define debug(msg)
#endif

// memory debug
#define MEM_DEBUG           1

#if (MEM_DEBUG)
    #define m_debug()   printf("free mem %u\r\n", get_free_memory());
#else
    #define m_debug()
#endif

// define message code

// OBJECT
#define MSG_OBJ_RINGBUFF_IS_NULL        0x10
#define MSG_OBJ_EVENT_QUEUE_IS_NULL     0x11
#define MSG_OBJ_EVENT_IS_NULL           0x12
#define MSG_OBJ_MESSAGE_QUEUE_IS_NULL   0x13
// UART
#define MSG_UART_RING_EMPTY             0x20
#define MSG_UART_RING_FULL              0x21
#define MSG_UART_RQ_RESEND              0x22

// INTERNAL MESSAGE
// function: lower layer get message and regist event
// using to control peripheral 
// or internal process

// EXTERNAL MESSAGE
// 

// EVENT ID
#define EVENT_ID_PERIPHERAL_NULL   0x00
#define EVENT_ID_UART_TX           0x01
#define EVENT_ID_UART_RX           0x02
#define EVENT_ID_INT0              0x08
#define EVENT_ID_INT1              0x09

#endif  //  _C_TYPE_H_
