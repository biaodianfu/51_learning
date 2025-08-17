#include "config.h"
#if USE_OLED_12864_SPI
#include "oled_12864_spi.h"
#include "drivers/communication/spi_soft.h"
#include "drivers/display/font.h"

/**
 * @brief 向OLED写入一个字节数据(SPI版本)
 *
 * @param dat 要发送的数据字节
 * @param mode 发送模式，OLED_CMD表示命令模式，OLED_DATA表示数据模式
 */
void oled_write_byte(unsigned char dat, unsigned char mode) {
    // 选择OLED设备
    spi_start_device(OLED_DEVICE);

    // 设置DC引脚状态
    OLED_DC = mode;

    // 发送数据
    spi_write_byte(dat);

    // 结束设备操作
    spi_end_device(OLED_DEVICE);
}

/**
 * @brief 向OLED写入多个字节数据(SPI版本)
 *
 * @param data 要发送的数据数组
 * @param len 数据长度
 * @param mode 发送模式，OLED_CMD表示命令模式，OLED_DATA表示数据模式
 */
void oled_write_multiple_bytes(unsigned char *data, unsigned int len, unsigned char mode) {
    spi_start_device(OLED_DEVICE);

    // 设置DC引脚状态
    OLED_DC = mode;

    // 批量发送数据
    spi_write_data(data, len);

    spi_end_device(OLED_DEVICE);
}

/**
 * @brief 初始化OLED显示屏(SPI版本)
 */
void oled_init(void) {
    // 初始化SPI（模式0，无分频）
    SPI_CONFIG spi_cfg = {SPI_MODE0, 1};
    spi_init(spi_cfg);

    // 复位OLED
    OLED_RES = 0;
    delay_ms(200); // 供应商例程中复位延时200ms
    OLED_RES = 1;
    delay_ms(10);

    // 供应商初始化序列
    oled_write_byte(0xAE, OLED_CMD); // 关闭显示
    oled_write_byte(0xFD, OLED_CMD); // 设置命令锁定（供应商特定）
    oled_write_byte(0x12, OLED_CMD); // 解锁命令（供应商特定）

    oled_write_byte(0xD5, OLED_CMD); // 设置显示时钟分频比/振荡器频率
    oled_write_byte(0xA0, OLED_CMD); // 供应商参数

    oled_write_byte(0xA8, OLED_CMD); // 设置多路复用比
    oled_write_byte(0x3F, OLED_CMD); // 设置为1/64 duty (64行)

//    oled_write_byte(0xD3, OLED_CMD); // 设置显示偏移
    oled_write_byte(0x00, OLED_CMD); // 无偏移

    oled_write_byte(0x40, OLED_CMD); // 设置起始行地址为0

    // 设置扫描方向（供应商例程中为正常方向）
    oled_write_byte(0xA1, OLED_CMD); // 段重映射正常（从左到右）
    oled_write_byte(0xC8, OLED_CMD); // COM输出扫描方向正常（从上到下）

    oled_write_byte(0xDA, OLED_CMD); // 设置COM引脚硬件配置
    oled_write_byte(0x12, OLED_CMD); // 供应商参数

    oled_write_byte(0x81, OLED_CMD); // 设置对比度控制
    oled_write_byte(0xBF, OLED_CMD); // 对比度值（0-255）

    oled_write_byte(0xD9, OLED_CMD); // 设置预充电周期
    oled_write_byte(0x25, OLED_CMD); // 供应商参数

    oled_write_byte(0xDB, OLED_CMD); // 设置VCOMH反压
    oled_write_byte(0x34, OLED_CMD); // 供应商参数

    oled_write_byte(0xA4, OLED_CMD); // 禁用整个显示开启（保留RAM内容）
    oled_write_byte(0xA6, OLED_CMD); // 正常显示（非反色）

    // 清屏并开启显示
    oled_clear();
    oled_write_byte(0xAF, OLED_CMD); // 开启显示
}

/**
 * @brief 清除OLED显示屏内容(SPI版本)
 */
void oled_clear(void) {
    for (unsigned char page = 0; page < 8; page++) {
        // 设置页地址
        oled_write_byte(0xB0 | page, OLED_CMD);
        // 设置列地址从0开始
        oled_write_byte(0x00, OLED_CMD);  // 列低地址 (0-15)
        oled_write_byte(0x10, OLED_CMD);  // 列高地址 (16-127)

        // 单次传输整行128字节的0x00
        unsigned char __code zero_data[128] = {0};
        oled_write_multiple_bytes(zero_data, 128, OLED_DATA);
    }

    // 确保所有数据都已写入
    delay_ms(1);
}


/**
 * @brief 打开OLED显示屏(SPI版本)
 */
void oled_display_on(void) {
    oled_write_byte(0x8D, OLED_CMD);  // SET DCDC命令（供应商命令）
    oled_write_byte(0x14, OLED_CMD);  // DCDC ON
    oled_write_byte(0xAF, OLED_CMD);   // 开启显示
}

/**
 * @brief 关闭OLED显示屏(SPI版本)
 */
void oled_display_off(void) {
    oled_write_byte(0x8D, OLED_CMD);  // SET DCDC命令（供应商命令）
    oled_write_byte(0x10, OLED_CMD);  // DCDC OFF
    oled_write_byte(0xAE, OLED_CMD);   // 关闭显示
}

/**
 * @brief 设置OLED显示屏的光标位置(SPI版本)
 */
void oled_set_cursor(unsigned char col, unsigned char page) {
    if (col >= OLED_WIDTH || page >= OLED_HEIGHT/OLED_CHAR_HEIGHT) return;

    oled_write_byte(0xB0 | page, OLED_CMD);  // 设置页地址
    oled_write_byte((((col) & 0xF0) >> 4) | 0x10, OLED_CMD); // 列高地址
    oled_write_byte((col) & 0x0F, OLED_CMD);    // 列低地址
}


/**
 * @brief 在OLED显示屏上显示一个字符(SPI版本)
 */
/**
 * @brief 在OLED显示屏上显示一个字符(SPI版本)
 */
void oled_display_char(unsigned char col, unsigned char page, char ch) {
    if (page >= OLED_HEIGHT/OLED_CHAR_HEIGHT) return; // 防止越界

    // 检查列边界（字体宽度6像素）
    if (col > OLED_WIDTH - OLED_CHAR_WIDTH) {
        col = 0;
        if (++page >= OLED_HEIGHT/OLED_CHAR_HEIGHT) return; // 增加页边界检查
    }

    // 使用统一的光标设置函数
    oled_set_cursor(col, page);

    // 发送字体数据
    spi_start_device(OLED_DEVICE);
    OLED_DC = OLED_DATA;  // 数据模式

    unsigned char c = ch - ' ';
    for (unsigned char i = 0; i < OLED_CHAR_WIDTH; i++) {
        spi_write_byte(FONT_8X6[c][i]);
    }

    spi_end_device(OLED_DEVICE);
}

/**
 * @brief 在OLED显示屏上显示字符串(SPI版本)
 */
void oled_display_string(unsigned char col, unsigned char page, const char *str) {
    unsigned char i = 0;

    while (str[i] != '\0' && page < OLED_HEIGHT/OLED_CHAR_HEIGHT) {
        oled_display_char(col, page, str[i]);

        col += OLED_CHAR_WIDTH;
        if (col > OLED_WIDTH - OLED_CHAR_WIDTH) {
            col = 0;
            if (++page >= OLED_HEIGHT/OLED_CHAR_HEIGHT) break;
        }
        i++;
    }
}

/**
 * @brief 设置OLED显示屏的显示模式(SPI版本)
 */
void oled_display_inverse(unsigned char mode) {
    if (mode==0) {
        oled_write_byte(0xA6, OLED_CMD); // 正常显示
    } else {
        oled_write_byte(0xA7, OLED_CMD); // 反色显示
    }
}

/**
 * @brief 设置OLED显示屏的扫描方向(SPI版本)
 */
void oled_display_turn(unsigned char mode) {
    if (mode == 0) {
        oled_write_byte(0xC0, OLED_CMD); // 正扫描方向（从上到下）
        oled_write_byte(0xA0, OLED_CMD); // 正常段重映射（从左到右）
    } else {
        oled_write_byte(0xC8, OLED_CMD); // 反扫描方向（从下到上）
        oled_write_byte(0xA1, OLED_CMD); // 反向段重映射（从右到左）
    }
}

#endif // USE_OLED_12864_SPI
