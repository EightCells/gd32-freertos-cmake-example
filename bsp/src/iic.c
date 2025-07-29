/**
 * @file iic.c
 * @author wang.xuhui
 * @brief iic master driver
 * @version 0.1
 * @date 2024-12-03
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "bsp.h"

#define IIC_DEF(name)   BSP_DEF(IIC, name, IIC_N)

IIC_DEF(SCL_PORT);
IIC_DEF(SDA_PORT);
IIC_DEF(SCL_RCU);
IIC_DEF(SDA_RCU);
IIC_DEF(SCL_PIN);
IIC_DEF(SDA_PIN);


static void iic_x_config(IICxEnum x)
{
    rcu_periph_clock_enable(IIC_SCL_RCU[x]);
    rcu_periph_clock_enable(IIC_SDA_RCU[x]);

    gpio_mode_set(IIC_SCL_PORT[x], GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, IIC_SCL_PIN[x]);
    gpio_output_options_set(IIC_SCL_PORT[x], GPIO_OTYPE_OD, GPIO_OSPEED_50MHZ, IIC_SCL_PIN[x]);

    gpio_mode_set(IIC_SDA_PORT[x], GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, IIC_SDA_PIN[x]);
    gpio_output_options_set(IIC_SDA_PORT[x], GPIO_OTYPE_OD, GPIO_OSPEED_50MHZ, IIC_SDA_PIN[x]);

    gpio_bit_set(IIC_SCL_PORT[x], IIC_SCL_PIN[x]);
    gpio_bit_set(IIC_SDA_PORT[x], IIC_SDA_PIN[x]);
}

void iic_config(void)
{
    for (int i = 0; i < IIC_N; ++i)
    {
        iic_x_config((IICxEnum)i);
    }
}

#define IIC_SCL_pd(x)   gpio_bit_reset(IIC_SCL_PORT[x], IIC_SCL_PIN[x])
#define IIC_SCL_pu(x)   gpio_bit_set(IIC_SCL_PORT[x], IIC_SCL_PIN[x])
#define IIC_delay()     delay_us(2)

#define IIC_SDA_IN(x)   gpio_mode_set(IIC_SDA_PORT[x], GPIO_MODE_INPUT, GPIO_PUPD_PULLDOWN, IIC_SDA_PIN[x])
#define IIC_SDA_OUT(x)  gpio_mode_set(IIC_SDA_PORT[x], GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, IIC_SDA_PIN[x])

static void IIC_SDA_write(IICxEnum x, uint8_t b)
{
    b ? \
    gpio_bit_set(IIC_SDA_PORT[x], IIC_SDA_PIN[x]) : \
    gpio_bit_reset(IIC_SDA_PORT[x], IIC_SDA_PIN[x]);
}

static uint8_t IIC_SDA_read(IICxEnum x)
{
    return (uint8_t)gpio_input_bit_get(IIC_SDA_PORT[x], IIC_SDA_PIN[x]);
}

/**
 * @brief generate IIC start signal
 * 
 * @param x IICxEnum 1,2,3,4,MCU
 */
static void IIC_start(IICxEnum x)
{
    /* stop all device */
    // IIC_SDA_write(x, 1);
    // IIC_SCL_pu(x);
    // IIC_delay();

    /* at first, SCL = SDA = 1 */
    /* send start signal, pull down SDA when SCL is high */
    IIC_SDA_write(x, 0);
    IIC_delay();
    /* pull down SCL, ready to send data */
    IIC_SCL_pd(x);
    // IIC_delay();
    /* at last, SCL = 0, SDA = 0 */
}

/**
 * @brief generate IIC stop signal
 * 
 * @param x IICxEnum 1,2,3,4,MCU
 */
static void IIC_stop(IICxEnum x)
{
    /* send stop signal, pull up SDA when SCL = 1 */
    /* at first, SCL = 0 */
    IIC_SDA_write(x, 0);
    IIC_delay();
    IIC_SCL_pu(x);
    IIC_delay();
    IIC_SDA_write(x, 1);
    IIC_delay();
    /* at last, SCL = SDA = 1 */
}

/**
 * @brief send IIC ack signal after read a byte
 * 
 * @param x IICxEnum 1,2,3,4,MCU
 */
static void IIC_ack(IICxEnum x)
{
    /* at first, SCL = 0 */
    IIC_SDA_write(x, 0);
    IIC_delay();
    IIC_SCL_pu(x);
    IIC_delay();
    /* pull down SCL, ready to change SDA */
    IIC_SCL_pd(x);
    /* release SDA */
    IIC_SDA_write(x, 1);
    /* at last, SCL = 0, SDA = 1 */
}

/**
 * @brief send IIC nack signal after read a byte
 * 
 * @param x IICxEnum 1,2,3,4,MCU
 */
static void IIC_nack(IICxEnum x)
{
    /* at first, SCL = 0 */
    IIC_SDA_write(x, 1);
    IIC_delay();
    IIC_SCL_pu(x);
    IIC_delay();
    /* pull down SCL, ready to change SDA */
    IIC_SCL_pd(x);
    /* release SDA */
    IIC_SDA_write(x, 1);
    /* at last, SCL = 0, SDA = 1 */
}

/**
 * @brief IIC wait a ACK/NACK, then SCL = 0
 * 
 * @param x IICxEnum 1,2,3,4,MCU
 * @retval 0 - get ack
 * @retval 1 - get nack
 */
static uint8_t IIC_wait_ack(IICxEnum x)
{
    uint8_t rack = 0;

    /* master release SDA */
    // IIC_SDA_write(x, 1);
    IIC_SDA_IN(x);
    IIC_delay();

    /* master pull up SCL and read SDA */
    IIC_SCL_pu(x);
    // IIC_delay();
    timer5_delay = 5;
    while (IIC_SDA_read(x))
    {
        if (timer5_delay == 0)
        {
            /* get nack */
            rack = 1;
            break;
        }
    }
    while (timer5_delay != 0);

    IIC_SCL_pd(x);

    IIC_SDA_OUT(x);

    return rack;
}

/**
 * @brief IIC send a byte to slave device
 * @attention NOT send START signal before send.
 * @attention NOT check ACK/NACK from slave device after send complete.
 * @param x IICxEnum 1,2,3,4,MCU
 * @param b byte to send
 */
static void IIC_send_byte(IICxEnum x, uint8_t b)
{
    /* send data, MSB */
    for (int i = 0; i < 8; ++i)
    {
        IIC_SDA_write(x, (b & 0x80) >> 7);
        IIC_delay();
        IIC_SCL_pu(x);
        IIC_delay();
        IIC_SCL_pd(x);
        b <<= 1;
    }

    /* master release SDA */
    // IIC_SDA_write(x, 1);
    // IIC_SDA_IN(x);
    // IIC_delay();
}

/**
 * @brief IIC read a byte from slave device
 * @attention NOT send ACK/NACK after read complete.
 * @param x IICxEnum 1,2,3,4,MCU
 * @return uint8_t - byte read from slave device
 */
uint8_t IIC_read_byte(IICxEnum x)
{
    uint8_t res = 0;

    IIC_SDA_IN(x);
    for (int i = 0; i < 8; ++i)
    {
        IIC_SCL_pd(x);
        IIC_delay();
        res <<= 1;
        IIC_SCL_pu(x);
        IIC_delay();
        res |= IIC_SDA_read(x);
    }
    IIC_SDA_OUT(x);

    IIC_SCL_pd(x);
    //delay_us(100);
    return res;
}

void IIC_send(IICxEnum x, \
              uint8_t *write_bytes, uint8_t write_count, \
              uint8_t *read_bytes, uint8_t read_count)
{
    /* send start signal */
    IIC_start(x);

    /* send bytes */
    while (write_count--)
    {
        IIC_send_byte(x, *write_bytes);
        if (IIC_wait_ack(x))
        {
            IIC_stop(x);
            return;
        }
        // IIC_ack(x);
        write_bytes++;
    }

    /* read bytes */
    while (read_count--)
    {
        *read_bytes = IIC_read_byte(x);
        read_count ? IIC_ack(x) : IIC_nack(x);
        read_bytes++;
    }

    /* send stop signal */
    IIC_stop(x);
}
