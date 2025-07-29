/**
 * @file queue.c
 * @author wang.xuhui
 * @brief round queue API
 * @version 0.1
 * @date 2024-10-25
 */

#include <stdio.h>
#include "rqueue.h"

/**
 * @addtogroup Queue Interface 
 * @{
 */

/**
 * @brief queue initial
 * @param q queue struct pointer
 * @param p_buff queue buffer pointer
 * @param buff_size queue buffer size
 * @param data_len unit data length (byte)
 */
void queue_init(RoundQueue_t q, void *p_buff, uint32_t buff_size, uint8_t data_len)
{
    q->p_buff = (uint32_t)p_buff;
    q->head = 0;
    q->tail = 0;
    q->buff_size = buff_size;
    q->data_len = data_len;
}

/**
 * @brief return whether queue is empty
 * @param q queue struct pointer
 * @return true
 * @return false
 */
bool queue_empty(RoundQueue_t q)
{
    return q->head == q->tail;
}

/**
 * @brief return whether queue is full
 * @param q queue struct pointer
 * @return true
 * @return false
 */
bool queue_full(RoundQueue_t q)
{
    return (q->tail + 1) % q->buff_size == q->head;
}

/**
 * @brief enqueue a data, data length must fit q->data_len 
 * @param q queue struct pointer
 * @param data data start address
 * @retval -1 - fail, queue is full
 * @retval 0 - success
 */
int8_t enqueue(RoundQueue_t q, uint8_t *data)
{
    if (queue_full(q)) return -1;

    uint8_t *p = (uint8_t *)(q->p_buff + q->tail * q->data_len);
    for (int i = 0; i < q->data_len; ++i)
    {
        *(p + i) = *(data + i);
    }

    q->tail = (q->tail + 1) % q->buff_size;

    return 0;
}

/**
 * @brief dequeue a data 
 * @param q queue struct pointer
 * @retval NULL - fail, queue is empty
 * @return data start pointer
 */
void *dequeue(RoundQueue_t q)
{
    if (queue_empty(q)) return NULL;

    void *res = (void *)(q->p_buff + q->head * q->data_len);
    q->head = (q->head + 1) % q->buff_size;

    return res;
}

/**
 * @}
 */
