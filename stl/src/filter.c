/**
 * @file filter.c
 * @author wang.xuhui
 * @brief filter API.
 * @version 0.1
 * @date 2025-01-07
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "filter.h"

/**
 * @brief initialize the filter.
 * 
 * @param f the pointer of the filter to be initialized
 * @param len the length of the data buffer
 * @param buf the pointer of the data buffer
 */
void filter_init(Filter *f, uint8_t len, uint32_t *buf)
{
    f->len = len;
    f->cnt = 0;
    f->idx = 0;
    f->buf = buf;
}

/**
 * @brief update the filter with new data.
 * 
 * @param f the pointer of the filter to be updated
 * @param data the new data
 */
void filter_update(Filter *f, uint32_t data)
{
    uint32_t *const buf = f->buf;
    const uint8_t len = f->len;
    uint8_t idx = f->idx;

    if (f->cnt < len)
    {
        // if the buffer is not full, increase the count
        ++f->cnt;
    }

    // add the new data to the buffer
    buf[idx] = data;
    f->idx = (idx + 1) % len;
}

/**
 * @brief update the average filter with new data.
 * 
 * @param avg the pointer of the average filter to be updated
 * @param data the new data
 */
void avg_filter_update(AvgFilter *avg, uint32_t data)
{
    uint32_t *const buf = avg->base.buf;
    const uint8_t len = avg->base.len;
    uint8_t idx = avg->base.idx;

    if (avg->base.cnt < len)
    {
        // if the buffer is not full, increase the count
        ++avg->base.cnt;
    }
    else
    {
        // if the buffer is full, remove the oldest data
        avg->sum -= buf[idx];
    }

    // add the new data to the buffer
    buf[idx] = data;
    idx = (idx + 1) % len;
    avg->base.idx = idx;
    // update the sum
    avg->sum += data;
}

/**
 * @brief get the average value of the average filter.
 * 
 * @param avg the pointer of the average filter
 * @return double, the average value
 */
double avg_filter_get(AvgFilter *avg)
{
    return (double)avg->sum / avg->base.cnt;
}

/**
 * @brief initialize the average filter.
 * 
 * @param avg the pointer of the average filter to be initialized
 * @param len the length of the data buffer
 * @param buf the pointer of the data buffer
 */
void avg_filter_init(AvgFilter *avg, uint8_t len, uint32_t *buf)
{
    filter_init((Filter *)avg, len, buf);
    avg->sum = 0;
}

/**
 * @brief update the middle filter with new data.
 * 
 * @param mid the pointer of the middle filter to be updated
 * @param data the new data
 */
void mid_filter_update(MidFilter *mid, uint32_t data)
{
    filter_update((Filter *)mid, data);
}

/**
 * @brief get the middle value of the filter.
 * 
 * @param mid the pointer of the filter
 * @return uint32_t the middle value
 */
uint32_t mid_filter_get(MidFilter *mid)
{
    uint32_t *const sort = mid->sort_tmp;
    uint32_t *const buf = mid->base.buf;
    uint8_t cnt = mid->base.cnt;

    // copy the buffer to sort
    for (int i = 0; i < cnt; ++i)
    {
        sort[i] = buf[i];
    }

    // bubble sort
    for (int i = 0; i < cnt - 1; ++i)
    {
        for (int j = i + 1; j < cnt; ++j)
        {
            if (sort[i] > sort[j])
            {
                uint32_t tmp = sort[i];
                sort[i] = sort[j];
                sort[j] = tmp;
            }
        }
    }

    // return the middle value
    uint32_t res = sort[cnt / 2];
    return res;
}

/**
 * @brief initialize the middle filter.
 * 
 * @param mid the pointer of the filter to be initialized
 * @param len the length of the data buffer
 * @param buf the pointer of the data buffer
 */
void mid_filter_init(MidFilter *mid, uint8_t len, uint32_t *buf)
{
    filter_init((Filter *)mid, len, buf);
}

