#include <driver/uart/uart.h>

//set stream pointer
#define     INTTERRUPT_GLOBAL_ENABLE   sei()
FILE usart0 = FDEV_SETUP_STREAM(uart_tx_one_byte, uart_rx_one_byte, _FDEV_SETUP_RW);

#define UART_CONFIG_RX_BUFFER_LENGTH     64
#define UART_CONFIG_TX_BUFFER_LENGTH     64
static uint8_t UART_RX_BUFF[UART_CONFIG_RX_BUFFER_LENGTH];

buffer_ptr tx_buf;
buffer_ptr rx_buf;

static uart_signal_t rx_signal;

void uart_init()
{
    uart_config(BIT_RATE_9600);
    
    rx_buf = ringbuf_create();
    rx_buf->buffer = UART_RX_BUFF;
    rx_buf->head = rx_buf->tail = rx_buf->buffer;
    rx_buf->size = UART_CONFIG_RX_BUFFER_LENGTH;
    ringbuf_reset(rx_buf);
    
    rx_signal.counter = 0;
    rx_signal.ctrl = false;
}

void uart_config(UartBautRate baud)
{
    //Set baud rate
    uint32_t BAUDRATE;
    BAUDRATE = ((F_CPU)/(baud*16UL)-1);
    UBRRH=(BAUDRATE>>8);
    UBRRL=BAUDRATE;                             //set baud rate
    UCSRB|=(1<<TXEN)|(1<<RXEN);                 //enable receiver and transmitter
    UCSRC|=(1<<URSEL)|(1<<UCSZ0)|(1<<UCSZ1);    // 8bit data format
    
    //Enable Transmitter and Receiver and Interrupt on receive complete
    UCSRB=(1<<RXEN)|(1<<TXEN)|(1<<RXCIE);
    INTTERRUPT_GLOBAL_ENABLE;
    
    //assign our stream to standart I/O streams
    stdin=stdout=&usart0;
}

int uart_tx_one_byte(char tx_char, FILE *stream)
{
    while (!(UCSRA & (1 << UDRE)));
    UDR = tx_char;
    return 0;
}

int uart_rx_one_byte(FILE *stream)
{
    uint8_t byte = 0;
    
    return byte;
}
void uart_tx_isr()
{
    
}

void uart_rx_isr()
{
    uint8_t byte;
    byte = UDR;
    // two cntrl
    if (rx_signal.ctrl && iscntrl(byte))
        return;
    
    if ((byte == LF) || (byte == CR))
    {
        // buff is empty & cntrl
        if (rx_buf->status == RING_STATUS_EMPTY)
        {
            uart_signal_reset();
            return;
            
        }
        
        if (rx_buf->status == RING_STATUS_FULL)
        {
            ringbuf_reset(rx_buf);
            debug(MSG_UART_RQ_RESEND);
            return;        
        }
        
        rx_signal.ctrl = true;
        rx_signal.counter++;
        uart_regist_event();
    }
    else
    {
        rx_signal.ctrl = false;
    }
    ringbuf_write_one_byte(rx_buf, byte);
}

void uart_regist_event()
{
//     if (uart_signal_counter() > 0)
    {
        event_t event;
        event.id = EVENT_ID_UART_RX;
        event.priority = EVENT_PRIORITY_LOW;
        event.callback = uart_read_frame;
        event_enqueue(event);
    }
}

const uint8_t uart_read_byte()
{
    uint8_t byte = ringbuf_read_one_byte(rx_buf);
    return byte;
}

void* uart_read_frame()
{
    if (rx_signal.counter == 0)
        return 0;
    
    uint8_t end = ringbuf_bytes_used(rx_buf);
    uint8_t* frame = (uint8_t*)calloc(end, sizeof(uint8_t));
    uint8_t idx = 0;
    uint8_t i = 0;
    uint8_t byte;
    for (i = 0; i < end; i++)
    {
        byte = ringbuf_read_one_byte(rx_buf);
        frame[idx++] = byte;
        if ((byte == LF) || (byte == CR))
            break;
        
        if (rx_buf->status == RING_STATUS_EMPTY)
        {
            rx_signal.counter = 0;
            rx_signal.ctrl = false;
            break;
        }
    }
    rx_signal.counter--;
    uint8_t* result = (uint8_t*)malloc((idx + 1) * sizeof(uint8_t));
    // copy bytes not using memcpy
    for (i = 0; i < idx; i++)
    {
        result[i] = frame[i];
    }
    // last letter is NULL, just using in internal message
    result[idx] = '\0';
    free(frame);
    return result;
}

const uint8_t uart_get_byte_used()
{
    uint8_t num_bytes_used = ringbuf_bytes_used(rx_buf);
    return num_bytes_used;
}

void uart_signal_reset()
{
    rx_signal.counter = 0;
    rx_signal.ctrl = false;
}

const uint8_t uart_signal_counter()
{
    return rx_signal.counter;
}
