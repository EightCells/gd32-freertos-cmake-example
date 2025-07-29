/**
 * @file adverage_filter.h
 * @author wang.xuhui
 * @brief the header of adverage_filter.c.
 * @version 0.1
 * @date 2025-01-07
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef __FILTER_H__
#define __FILTER_H__

#include <stdint.h>
#include <stdbool.h>

typedef struct st_Filter Filter;
typedef struct st_AvgFilter AvgFilter;
typedef struct st_MidFilter MidFilter;

struct st_Filter
{
    uint32_t    *buf;   // buffer of the data
    uint8_t     len;    // length of the buffer
    uint8_t     cnt;    // count of the data
    uint8_t     idx;    // index of the latest data
};

struct st_AvgFilter
{
    Filter base;                // base
    volatile double sum;        // sum of the data
};

#define MID_FILTER_MAX_LEN  10
struct st_MidFilter
{
    Filter base;
    uint32_t sort_tmp[MID_FILTER_MAX_LEN];
};

void avg_filter_init(AvgFilter *avg, uint8_t len, uint32_t *buf);
void mid_filter_init(MidFilter *mid, uint8_t len, uint32_t *buf);

void avg_filter_update(AvgFilter *avg, uint32_t data);
void mid_filter_update(MidFilter *mid, uint32_t data);

double avg_filter_get(AvgFilter *avg);
uint32_t mid_filter_get(MidFilter *mid);

#endif
