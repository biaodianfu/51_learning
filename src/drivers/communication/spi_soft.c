#include "config.h"
#if USE_SPI
#include "spi_soft.h"
static SPI_CONFIG current_config;

/* SPI初始化 */
void spi_init(SPI_CONFIG config)
{
    current_config = config;

    // 初始化引脚状态
    SPI_CS = 1;     // 默认高电平（不选中）
    SPI_MOSI = 1;   // 空闲高电平

    // 根据模式设置初始时钟
    switch(config.mode) {
        case SPI_MODE0:
        case SPI_MODE1:
            SPI_CLK = 0;  // 模式0/1 空闲低电平
            break;
        case SPI_MODE2:
        case SPI_MODE3:
            SPI_CLK = 1;  // 模式2/3 空闲高电平
            break;
    }
}

/* 设置SPI模式 */
void spi_set_mode(SPI_MODE new_mode)
{
    current_config.mode = new_mode;

    // 更新时钟状态
    switch(new_mode) {
        case SPI_MODE0:
        case SPI_MODE1:
            SPI_CLK = 0;  // 空闲低电平
            break;
        case SPI_MODE2:
        case SPI_MODE3:
            SPI_CLK = 1;  // 空闲高电平
            break;
    }
}

/* 发送单个字节 */
void spi_write_byte(unsigned char data)
{
    unsigned char i;

    for(i = 0; i < 8; i++) {
        // 准备数据位
        switch(current_config.mode) {
            case SPI_MODE0:
            case SPI_MODE2:
                // 在第一个边沿写数据
                SPI_MOSI = (data & 0x80) ? 1 : 0;
                data <<= 1;
                break;
            default:
                break;
        }

        // 时钟翻转
        SPI_CLK = !SPI_CLK;
        ASM_NOP();
        ASM_NOP();

        switch(current_config.mode) {
            case SPI_MODE1:
            case SPI_MODE3:
                // 在第二个边沿写数据
                SPI_MOSI = (data & 0x80) ? 1 : 0;
                data <<= 1;
                break;
            default:
                break;
        }

        // 恢复时钟
        SPI_CLK = !SPI_CLK;
        ASM_NOP();
        ASM_NOP();
    }
}

/* 接收单个字节 */
unsigned char spi_read_byte(void)
{
    unsigned char i, data = 0;

    for(i = 0; i < 8; i++) {
        // 根据模式采样
        switch(current_config.mode) {
            case SPI_MODE0:
                // 上升沿采样
                SPI_CLK = 1;
                ASM_NOP();
                data <<= 1;
                if(SPI_MISO) data |= 0x01;
                SPI_CLK = 0;
                break;

            case SPI_MODE1:
                // 下降沿采样
                SPI_CLK = 0;
                ASM_NOP();
                data <<= 1;
                if(SPI_MISO) data |= 0x01;
                SPI_CLK = 1;
                break;

            case SPI_MODE2:
                // 下降沿采样
                SPI_CLK = 0;
                ASM_NOP();
                data <<= 1;
                if(SPI_MISO) data |= 0x01;
                SPI_CLK = 1;
                break;

            case SPI_MODE3:
                // 上升沿采样
                SPI_CLK = 1;
                ASM_NOP();
                data <<= 1;
                if(SPI_MISO) data |= 0x01;
                SPI_CLK = 0;
                break;
        }

        ASM_NOP();
    }

    return data;
}

/* 发送数据块 */
void spi_write_data(unsigned char *data, unsigned int len)
{
    while(len--) {
        spi_write_byte(*data++);
    }
}

/* 接收数据块 */
void spi_read_data(unsigned char *buf, unsigned int len)
{
    while(len--) {
        *buf++ = spi_read_byte();
    }
}


// 当前活动的设备ID
static unsigned char current_device = INVALID_DEVICE_ID;

// 设备ID列表
#define MAX_SPI_DEVICES 4
static unsigned char device_list[MAX_SPI_DEVICES] = {
        INVALID_DEVICE_ID, INVALID_DEVICE_ID,
        INVALID_DEVICE_ID, INVALID_DEVICE_ID
};

// 设备片选延时计数（用于满足不同器件的时序要求）
static unsigned char device_delay[MAX_SPI_DEVICES] = {
        0, 0, 0, 0
};

/**
 * @brief 注册SPI设备
 *
 * @param device_id 设备ID
 * @param cs_delay 片选激活后的最小延时（单位：μs）
 * @return true 注册成功
 * @return false 注册失败（设备ID已存在或设备表满）
 */
unsigned char spi_register_device(unsigned char device_id, unsigned char cs_delay)
{
    for (int i = 0; i < MAX_SPI_DEVICES; i++) {
        // 找到空闲槽位
        if (device_list[i] == INVALID_DEVICE_ID) {
            device_list[i] = device_id;
            device_delay[i] = cs_delay;
            return 1;
        }
        // 设备已注册
        if (device_list[i] == device_id) {
            return 0;
        }
    }
    // 设备表已满
    return 0;
}

/**
 * @brief 启动指定SPI设备
 *
 * 该函数负责激活指定设备的片选信号，并确保满足片选建立时间
 *
 * @param device_id 要启动的设备ID
 */
void spi_start_device(unsigned char device_id)
{
    // 检查设备是否已注册
    unsigned char found = 0;
    unsigned char delay = 0;

    for (int i = 0; i < MAX_SPI_DEVICES; i++) {
        if (device_list[i] == device_id) {
            found = 1;
            delay = device_delay[i];
            break;
        }
    }

    if (!found) {
        // 设备未注册，尝试注册默认参数
        spi_register_device(device_id, 2);
        delay = 2;
    }

    // 如果当前有活动设备，先结束该设备
    if (current_device != INVALID_DEVICE_ID) {
        spi_end_device(current_device);
    }

    // 激活片选（拉低）
    SPI_CS = 0;

    // 满足片选建立时间要求
    if (delay > 0) {
        // 简单的延时循环 - 约1μs/循环 @12MHz
        for (unsigned char i = 0; i < delay; i++) {
            ASM_NOP();
            ASM_NOP();
            ASM_NOP();
            ASM_NOP();
        }
    }

    current_device = device_id;
}

/**
 * @brief 结束指定SPI设备
 *
 * 该函数负责释放片选信号，并确保满足片选保持时间
 *
 * @param device_id 要结束的设备ID
 */
void spi_end_device(unsigned char device_id)
{
    // 只处理当前活动设备
    if (current_device != device_id) {
        return;
    }

    // 释放片选（拉高）
    SPI_CS = 1;

    // 满足片选保持时间要求
    for (unsigned char i = 0; i < 2; i++) {
        ASM_NOP();
        ASM_NOP();
        ASM_NOP();
        ASM_NOP();
    }

    current_device = INVALID_DEVICE_ID;
}

/**
 * @brief 获取当前活动设备ID
 *
 * @return unsigned char 当前活动设备ID
 */
unsigned char spi_get_current_device(void)
{
    return current_device;
}

#endif // USE_SPI