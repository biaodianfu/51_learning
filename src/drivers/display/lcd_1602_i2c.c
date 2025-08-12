#include <stdio.h>
#include "config.h"
#if USE_LCD_1602_I2C
#include "lcd_1602_i2c.h"
#include "drivers/communication/i2c_soft.h"

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
    lcd1602_cmd(0x01); // 清屏
    delay_ms(2);
}

// 发送初始化字节的特殊函数
static void lcd1602_send_init_byte(unsigned char byte) {
    i2c_start();
    i2c_write_byte(I2C_ADDR);
    i2c_write_byte(byte | 0x04); // EN=1
    i2c_write_byte(byte);        // EN=0
    i2c_stop();
}

// 4位数据写入函数
static void lcd1602_write_4bit(unsigned char data_value, unsigned char rs) {
    unsigned char hi_nib = data_value & 0xF0;
    unsigned char lo_nib = (data_value << 4) & 0xF0;

    // 控制位设置：RS + 背光(0x08)
    unsigned char control = rs | 0x08;

    // 发送高4位
    i2c_start();
    i2c_write_byte(I2C_ADDR);
    i2c_write_byte(hi_nib | control | 0x04); // EN=1
    i2c_write_byte(hi_nib | control);        // EN=0
    i2c_stop();

    // 发送低4位
    i2c_start();
    i2c_write_byte(I2C_ADDR);
    i2c_write_byte(lo_nib | control | 0x04); // EN=1
    i2c_write_byte(lo_nib | control);        // EN=0
    i2c_stop();
}

// 发送命令
void lcd1602_cmd(unsigned char cmd) {
    lcd1602_write_4bit(cmd, 0x00); // RS=0表示命令
    if(cmd == 0x01 || cmd == 0x02) {
        delay_ms(2); // 清屏和归位命令需要更长延时
    } else {
        delay_ms(1);
    }
}

// 发送数据
void lcd1602_write_char(unsigned char data) {
    lcd1602_write_4bit(data, 0x01); // RS=1表示数据
    delay_ms(1);
}

void lcd1602_write_string(const char* str) {
    while (*str) {
        lcd1602_write_char(*str++);
    }
}

void lcd1602_set_cursor(unsigned char row, unsigned char col) {
    unsigned char address;
    if (row == 0) {
        address = 0x80 + col; // 第一行地址
    } else {
        address = 0xC0 + col; // 第二行地址
    }
    lcd1602_cmd(address);
}

void lcd1602_clear(void) {
    lcd1602_cmd(0x01); // 发送清屏命令
    delay_ms(2);
}

void lcd1602_display_number(unsigned int number) {
    char buffer[16];
    sprintf(buffer, "%d", number);
    lcd1602_write_string(buffer);
}

void lcd1602_display_string(const char* str) {
    lcd1602_write_string(str);
}

void lcd1602_backlight_on(void) {
    i2c_start();
    i2c_write_byte(I2C_ADDR);
    i2c_write_byte(0x08); // 打开背光(背光控制位为0x08)
    i2c_stop();
}

void lcd1602_backlight_off(void) {
    i2c_start();
    i2c_write_byte(I2C_ADDR);
    i2c_write_byte(0x00); // 关闭背光
    i2c_stop();
}

#endif