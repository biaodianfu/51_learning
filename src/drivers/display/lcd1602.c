#include "config.h"
#if USE_LCD_1602
#include "lcd1602.h"

void lcd_send_command(unsigned char command) {
    // 发送命令到LCD1602
    LCD_RS = 0; // RS引脚低电平表示发送命令
    LCD_RW = 0; // RW引脚低电平表示写操作
    LCD_EN = 1; // 使能引脚高电平，开始传输
    LCD_DATA = command; // 将命令写入数据总线
    delay_us(50); // 等待命令执行
    LCD_EN = 0; // 使能引脚低电平，结束传输
}

void lcd1602_init(void) {
    // 初始化LCD1602显示器
    lcd_send_command(0x38); // 设置为8位数据模式，2行显示
    lcd_send_command(0x0C); // 显示开，光标关
    lcd_send_command(0x01); // 清屏
    lcd_send_command(0x06); // 写入新数据后光标右移
}

void lcd1602_write_char(unsigned char data) {
    // 写入字符到LCD1602
    LCD_RS = 1; // RS引脚高电平表示发送数据
    LCD_RW = 0; // RW引脚低电平表示写操作
    LCD_EN = 1; // 使能引脚高电平，开始传输
    LCD_DATA = data; // 将数据写入数据总线
    delay_us(50); // 等待数据写入完成
    LCD_EN = 0; // 使能引脚低电平，结束传输
}

void lcd1602_write_string(const char* str) {
    // 写入字符串到LCD1602
    while (*str) {
        lcd1602_write_char(*str++); // 逐个字符写入
    }
}

void lcd1602_set_cursor(unsigned char row, unsigned char col) {
    // 设置光标位置
    unsigned char address;
    if (row == 0) {
        address = 0x80 + col; // 第一行地址
    } else {
        address = 0xC0 + col; // 第二行地址
    }
    lcd_send_command(address); // 发送设置光标命令
}

void led1602_wirte_string_by_row(const char* str, unsigned char row) {
    // 按行写入字符串到LCD1602
    lcd1602_set_cursor(row, 0); // 设置光标到指定行的起始位置
    lcd1602_write_string(str); // 写入字符串
}

void lcd1602_clear(void) {
    // 清屏
    lcd_send_command(0x01); // 发送清屏命令
    delay_ms(2); // 等待清屏完成
}

void lcd1602_display_number(unsigned int number) {
    // 显示数字到LCD1602
    char buffer[16]; // 用于存储4位数字和结束符
    buffer[15] = '\0'; // 字符串结束符

    // 将数字转换为字符串，确保是4位，不足前面补0
    for (int i = 15; i >= 0; i--) {
        buffer[i] = (number % 10) + '0';
        number /= 10;
    }

    lcd1602_write_string(buffer); // 写入字符串到LCD
}

void lcd1602_display_string(const char* str) {
    // 显示字符串到LCD1602
    lcd1602_write_string(str); // 写入字符串到LCD
}

#endif
