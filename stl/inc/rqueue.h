/**
 * @file rqueue.h
 * @author wang.xuhui
 * @brief the header of queue.c
 * @version 0.1
 * @date 2024-10-25 
 */
#ifndef __RQUEUE_H__
#define __RQUEUE_H__

#include <stdint.h>
#include <stdbool.h>

/**
 * @addtogroup Queue Interface 
 * @{
 */
typedef struct st_Queue
{
    uint32_t    head;
    uint32_t    tail;
    uint32_t    p_buff;
    uint32_t    buff_size;
    uint8_t     data_len;
} RoundQueue, *RoundQueue_t;

/**
 * @}
 */

void queue_init(RoundQueue_t q, void *p_buff, uint32_t buff_size, uint8_t data_len);
bool queue_empty(RoundQueue_t q);
bool queue_full(RoundQueue_t q);
int8_t enqueue(RoundQueue_t q, uint8_t *data);
void *dequeue(RoundQueue_t q);

#endif



