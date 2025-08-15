#include "config.h"
#if USE_LCD_1602_I2C
#include <stdio.h>
#include "lcd_1602_i2c.h"
#include "drivers/communication/i2c_soft.h"

// LCD 地址和控制位定义
#define LCD_I2C_ADDR      I2C_ADDR
#define LCD_BACKLIGHT_ON  0x08
#define LCD_BACKLIGHT_OFF 0x00
#define LCD_CMD_CLEAR     0x01
#define LCD_CMD_HOME      0x02
#define LCD_ROW_0_BASE    0x80
#define LCD_ROW_1_BASE    0xC0

/**
 * @brief 通过I2C发送一个字节到LCD
 *
 * @param data 要发送的数据
 */
static void lcd1602_i2c_send(unsigned char data) {
    i2c_start();
    i2c_write_byte(LCD_I2C_ADDR);
    i2c_write_byte(data);
    i2c_stop();
}

/**
 * @brief 初始化LCD1602模块
 *
 * 包括初始化I2C接口、延时等待LCD上电稳定，
 * 执行特殊的初始化序列以确保进入4位模式，
 * 并设置显示参数。
 */
void lcd1602_init(void) {
    i2c_init();
    delay_ms(50); // 等待LCD上电稳定

    // 特殊初始化序列 - 用于确保进入4位模式
    lcd1602_send_init_byte(0x30); // 第一次尝试
    delay_ms(5);
    lcd1602_send_init_byte(0x30); // 第二次尝试
    delay_ms(1);
    lcd1602_send_init_byte(0x30); // 第三次尝试
    delay_ms(1);

    // 进入4位模式
    lcd1602_send_init_byte(0x20);
    delay_ms(1);

    // 4位模式下的初始化设置
    lcd1602_cmd(0x28); // 4位总线，2行显示，5x8点阵
    lcd1602_cmd(0x0C); // 开显示，关光标
    lcd1602_cmd(0x06); // 地址增量，光标右移
    lcd1602_cmd(LCD_CMD_CLEAR); // 清屏
    delay_ms(2);
}

/**
 * @brief 发送初始化字节到LCD（用于初始化阶段）
 *
 * @param byte 要发送的初始化字节
 */
static void lcd1602_send_init_byte(unsigned char byte) {
    lcd1602_i2c_send(byte | 0x04); // EN=1
    lcd1602_i2c_send(byte);        // EN=0
}

/**
 * @brief 向LCD写入4位数据
 *
 * @param data_value 要写入的数据（8位）
 * @param rs 控制信号：0表示命令，1表示数据
 */
static void lcd1602_write_4bit(unsigned char data_value, unsigned char rs) {
    unsigned char hi_nib = data_value & 0xF0;
    unsigned char lo_nib = (data_value << 4) & 0xF0;
    unsigned char control = rs | LCD_BACKLIGHT_ON;

    // 发送高4位
    lcd1602_i2c_send(hi_nib | control | 0x04); // EN=1
    lcd1602_i2c_send(hi_nib | control);        // EN=0

    // 发送低4位
    lcd1602_i2c_send(lo_nib | control | 0x04); // EN=1
    lcd1602_i2c_send(lo_nib | control);        // EN=0
}

/**
 * @brief 向LCD发送命令
 *
 * @param cmd 要发送的命令
 */
void lcd1602_cmd(unsigned char cmd) {
    lcd1602_write_4bit(cmd, 0x00); // RS=0表示命令
    if (cmd == LCD_CMD_CLEAR || cmd == LCD_CMD_HOME) {
        delay_ms(2); // 清屏和归位命令需要更长延时
    } else {
        delay_ms(1);
    }
}

/**
 * @brief 向LCD发送一个字符数据
 *
 * @param data 要发送的字符数据
 */
void lcd1602_write_char(unsigned char data) {
    lcd1602_write_4bit(data, 0x01); // RS=1表示数据
    delay_ms(1);
}

/**
 * @brief 在LCD上显示字符串
 *
 * @param str 指向要显示的字符串的指针
 */
void lcd1602_write_string(const char* str) {
    while (*str) {
        lcd1602_write_char(*str++);
    }
}

/**
 * @brief 设置LCD光标位置
 *
 * @param row 行号（0或1）
 * @param col 列号（0~15）
 */
void lcd1602_set_cursor(unsigned char row, unsigned char col) {
    unsigned char address;
    if (row == 0) {
        address = LCD_ROW_0_BASE + col;
    } else if (row == 1) {
        address = LCD_ROW_1_BASE + col;
    } else {
        return; // 不支持的行号
    }
    lcd1602_cmd(address);
}

/**
 * @brief 清除LCD屏幕
 */
void lcd1602_clear(void) {
    lcd1602_cmd(LCD_CMD_CLEAR);
    delay_ms(2);
}

/**
 * @brief 在LCD上显示无符号整数
 *
 * @param number 要显示的数字
 */
void lcd1602_display_number(unsigned int number) {
    char buffer[16];
    snprintf(buffer, sizeof(buffer), "%u", number); // 使用安全版本
    lcd1602_write_string(buffer);
}

/**
 * @brief 在LCD上显示字符串（与lcd1602_write_string功能相同）
 *
 * @param str 指向要显示的字符串的指针
 */
void lcd1602_display_string(const char* str) {
    lcd1602_write_string(str);
}

/**
 * @brief 控制LCD背光开关
 *
 * @param on 1表示打开背光，0表示关闭背光
 */
void lcd1602_backlight_control(unsigned char on) {
    lcd1602_i2c_send(on ? LCD_BACKLIGHT_ON : LCD_BACKLIGHT_OFF);
}

/**
 * @brief 打开LCD背光
 */
void lcd1602_backlight_on(void) {
    lcd1602_backlight_control(1);
}

/**
 * @brief 关闭LCD背光
 */
void lcd1602_backlight_off(void) {
    lcd1602_backlight_control(0);
}

#endif

