#include <driver/uart/ring_buffer.h>

buffer_ptr ringbuf_create(void)
{
    buffer_ptr buff = (buffer_ptr)malloc(sizeof(ring_buffer_t));
    if (buff == NULL)
    {
        free(buff);
        debug(MSG_OBJ_RINGBUFF_IS_NULL);
        return NULL;
    }
    
    buff->status = RING_STATUS_EMPTY;
    return buff;
}

void ringbuf_write_one_byte(buffer_ptr buff, const uint8_t byte)
{
    if (buff->status == RING_STATUS_FULL)
    {
        debug(MSG_UART_RING_FULL);
        return;
    }
    
    *buff->tail = byte;
    buff->tail++;
    
    if (buff->tail == (buff->buffer + buff->size))
        buff->tail = buff->buffer;
    
    buff->status = RING_STATUS_DATA_PRESENT;
    
    if (buff->tail == buff->head)
        buff->status = RING_STATUS_FULL;

}

uint16_t ringbuf_write_bytes(buffer_ptr buff, uint8_t* bytes)
{
    uint16_t numBytesWritten = 0;
    uint8_t byte;
    while (numBytesWritten < buff->size)
    {
        if (buff->status == RING_STATUS_FULL)
            break;
        
        byte = bytes[numBytesWritten];
        if ((byte != LF) || (byte != CR) || (byte != '\0'))
            ringbuf_write_one_byte(buff, byte);
        else
        {
            ringbuf_write_one_byte(buff, byte);
            break;
        }
    }
    
    return numBytesWritten;
}

const uint8_t ringbuf_read_one_byte(buffer_ptr buff)
{
    uint8_t byte = 0;
    byte = *buff->head;
    *buff->head = ' ';
    buff->head++;
    
    if (buff->head == buff->buffer + buff->size)
        buff->head = buff->buffer;
    
    if (buff->head == buff->tail)
        buff->status = RING_STATUS_EMPTY;
    else
        buff->status = RING_STATUS_DATA_PRESENT;
    
    return byte;
}

uint8_t ringbuf_read_bytes(uint8_t* result,  buffer_ptr buff)
{
    uint16_t numBytesRead = 0;
    
    while (numBytesRead < buff->size)
    {
        if (buff->status == RING_STATUS_EMPTY)
            break;
        else
        {
            result[numBytesRead++] = ringbuf_read_one_byte(buff);
        }
    }
    
    return numBytesRead;
}

const ring_buffer_status_e ringbuf_status(buffer_ptr buff)
{
    return buff->status;
}

const uint8_t ringbuf_bytes_used (const buffer_ptr buff)
{
    if (buff->status == RING_STATUS_EMPTY)
        return 0;
    else if (buff->tail > buff->head)
        return (buff->tail - buff->head);
    else
        return (buff->size - (buff->head - buff->tail));

}

void ringbuf_reset(buffer_ptr buff)
{
    memset(buff->buffer, 0, buff->size);
    buff->head = buff->tail = buff->buffer;
    buff->status = RING_STATUS_EMPTY;
}
