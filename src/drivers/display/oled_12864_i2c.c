#include "config.h"

#if USE_OLED_12864_I2C
#include "oled_12864_i2c.h"
#include "drivers/communication/i2c_soft.h"
#include "drivers/display/font.h"

/**
 * @brief 向OLED写入一个字节数据
 *
 * 该函数通过I2C接口向OLED发送一个字节的数据或命令。
 * 根据mode参数决定是发送数据还是命令。
 *
 * @param dat 要发送的数据字节
 * @param mode 发送模式，OLED_CMD表示命令模式，OLED_DATA表示数据模式
 * @return 无
 */
void oled_write_byte(unsigned char dat, unsigned char mode) {
    i2c_start();

    // 发送设备地址
    if (i2c_write_byte(OLED_I2C_ADDR) != 0) {
        i2c_stop();
        return; // 地址无响应
    }

    // 发送控制字节
    if (mode) {
        if (i2c_write_byte(0x40) != 0) { // 数据模式
            i2c_stop();
            return;
        }
    } else {
        if (i2c_write_byte(0x00) != 0) { // 命令模式
            i2c_stop();
            return;
        }
    }

    // 发送数据字节
    if (i2c_write_byte(dat) != 0) {
        i2c_stop();
        return;
    }

    i2c_stop();
}

void oled_init(void) {
    i2c_init();

    // 显示控制设置
    oled_write_byte(0xAE, OLED_CMD);        // 关闭显示，进入设置模式
    oled_write_byte(0xA6, OLED_CMD);        // 正常显示模式（非反显），0为点亮，1为熄灭

    // 显示区域设置
    oled_write_byte(0x00, OLED_CMD);        // 设置列地址低4位为0
    oled_write_byte(0x10, OLED_CMD);        // 设置列地址高4位为0
    oled_write_byte(0x40, OLED_CMD);        // 设置起始行地址为第0行
    oled_write_byte(0xB0, OLED_CMD);        // 设置页地址为第0页

    // 硬件配置
    oled_write_byte(0xA8, OLED_CMD);        // 设置多路复用比命令
    oled_write_byte(0x3F, OLED_CMD);        // 多路复用比设置为63，对应1/64 duty (64行)
    oled_write_byte(0xD3, OLED_CMD);        // 设置显示偏移命令
    oled_write_byte(0x00, OLED_CMD);        // 显示偏移设置为0，无垂直偏移

    // 时序控制
    oled_write_byte(0xD5, OLED_CMD);        // 设置显示时钟分频因子/振荡器频率命令
    oled_write_byte(0x80, OLED_CMD);        // 时钟分频因子设置为1，振荡器频率设置为0
    oled_write_byte(0xD9, OLED_CMD);        // 设置预充电周期命令
    oled_write_byte(0xF1, OLED_CMD);        // 预充电周期设置为1个时钟周期，放电周期设置为15个时钟周期

    // 电压设置
    oled_write_byte(0x81, OLED_CMD);        // 设置对比度控制命令
    oled_write_byte(0xCF, OLED_CMD);        // 对比度值设置为207(0-255)
    oled_write_byte(0xDB, OLED_CMD);        // 设置VCOMH反压命令
    oled_write_byte(0x30, OLED_CMD);        // VCOMH设置为0.83倍VCC

    // 开启显示
    oled_write_byte(0x8D, OLED_CMD);        // 设置充电泵命令
    oled_write_byte(0x14, OLED_CMD);        // 启用内部充电泵
    oled_write_byte(0xAF, OLED_CMD);        // 打开显示
}

void oled_clear(void) {
    for (unsigned char page = 0; page < 8; page++) {
        // 设置页地址
        oled_write_byte(0xB0 | page, OLED_CMD);
        // 重置列地址（供应商方式）
        oled_write_byte(0x00, OLED_CMD);  // 列低地址
        oled_write_byte(0x10, OLED_CMD);  // 列高地址

        // 单次I2C传输发送整行数据
        i2c_start();
        if (i2c_write_byte(OLED_I2C_ADDR) != 0) {
            i2c_stop();
            continue;
        }

        if (i2c_write_byte(0x40) != 0) { // 数据模式开始
            i2c_stop();
            continue;
        }

        // 连续发送128个0x00（不中断I2C）
        for (unsigned char col = 0; col < OLED_WIDTH; col++) {
            if (i2c_write_byte(0x00) != 0) {
                i2c_stop();
                break;
            }
        }
        i2c_stop();
    }
}

// 开启OLED显示（添加电荷泵控制）
void oled_display_on(void) {
    oled_write_byte(0x8D, OLED_CMD);  // SET DCDC命令（供应商命令）
    oled_write_byte(0x14, OLED_CMD);  // DCDC ON（关键添加）
    oled_write_byte(0xAF, OLED_CMD);   // 开启显示
}

// 关闭OLED显示（添加电荷泵控制）
void oled_display_off(void) {
    oled_write_byte(0x8D, OLED_CMD);  // SET DCDC命令（供应商命令）
    oled_write_byte(0x10, OLED_CMD);  // DCDC OFF（关键添加）
    oled_write_byte(0xAE, OLED_CMD);   // 关闭显示
}

void oled_set_cursor(unsigned char col, unsigned char page) {
    if (col >= OLED_WIDTH || page >= OLED_HEIGHT/OLED_CHAR_HEIGHT) return;
    oled_write_byte(0xB0 | page, OLED_CMD); // 设置页地址
    // 设置列地址
    oled_write_byte(0x00 | (col & 0x0F), OLED_CMD);  // 列地址低4位
    oled_write_byte(0x10 | ((col >> 4) & 0x0F), OLED_CMD); // 列地址高4位
}

void oled_display_char(unsigned char col, unsigned char page, char ch) {
    if (page >= OLED_HEIGHT/OLED_CHAR_HEIGHT) return; // 防止越界

    // 检查列边界（字体宽度6像素）
    if (col > OLED_WIDTH - OLED_CHAR_WIDTH) {
        col = 0;
        if (++page >= OLED_HEIGHT/OLED_CHAR_HEIGHT) return; // 增加页边界检查
    }

    unsigned char c = ch - ' ';
    oled_set_cursor(col, page);

    for (unsigned char i = 0; i < OLED_CHAR_WIDTH; i++) {
        oled_write_byte(FONT_8X6[c][i], OLED_DATA);
    }
}

void oled_display_string(unsigned char col, unsigned char page, const char *str) {
    unsigned char i = 0;
    while (str[i] != '\0' && page < OLED_HEIGHT/OLED_CHAR_HEIGHT) {
        // 修正参数顺序：col, page
        oled_display_char(col, page, str[i]);

        col += OLED_CHAR_WIDTH;
        if (col > OLED_WIDTH - OLED_CHAR_WIDTH) {
            col = 0;
            if (++page >= OLED_HEIGHT/OLED_CHAR_HEIGHT) break;
        }
        i++;
    }
}

void oled_display_inverse(unsigned char mode) {
    if (mode==0) {
        oled_write_byte(0xA6, OLED_CMD); // 正常显示
    } else {
        oled_write_byte(0xA7, OLED_CMD); // 反色显示
    }
}

void oled_display_turn(unsigned char mode) {
    if (mode == 0) {
        oled_write_byte(0xC0, OLED_CMD); // 正扫描方向（从上到下）
        oled_write_byte(0xA0, OLED_CMD); // 正常段重映射（从左到右）
    } else {
        oled_write_byte(0xC8, OLED_CMD); // 反扫描方向（从下到上）
        oled_write_byte(0xA1, OLED_CMD); // 反向段重映射（从右到左）
    }
}

#endif // USE_OLED_12864_I2C
