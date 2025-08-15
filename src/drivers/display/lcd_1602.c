#include "config.h"
#if USE_LCD_1602
#include <stdio.h>  // for snprintf
#include "lcd1602.h"

/**
 * @brief 发送命令到LCD1602显示屏
 *
 * @param command 要发送的命令字节
 */
void lcd_send_command(unsigned char command) {
    LCD_RS = 0;         // 设置为命令模式
    LCD_RW = 0;         // 设置为写入模式
    LCD_EN = 1;         // 使能信号置高
    LCD_DATA = command; // 输出命令数据
    delay_us(50);       // 等待一段时间确保命令被处理
    LCD_EN = 0;         // 使能信号置低，完成传输
}

/**
 * @brief 初始化LCD1602显示屏
 *
 * 配置显示模式、显示开关控制、清屏和光标移动方向等基本设置。
 */
void lcd1602_init(void) {
    lcd_send_command(0x38); // 设置为8位数据接口，两行显示，5x7点阵字符
    lcd_send_command(0x0C); // 显示开，光标关，光标不闪烁
    lcd_send_command(0x01); // 清除屏幕
    lcd_send_command(0x06); // 设置输入模式，光标右移，显示不移动
}

/**
 * @brief 向LCD1602写入一个字符
 *
 * @param data 要显示的字符数据
 */
void lcd1602_write_char(unsigned char data) {
    LCD_RS = 1;         // 设置为数据模式
    LCD_RW = 0;         // 设置为写入模式
    LCD_EN = 1;         // 使能信号置高
    LCD_DATA = data;    // 输出字符数据
    delay_us(50);       // 等待一段时间确保数据被处理
    LCD_EN = 0;         // 使能信号置低，完成传输
}

/**
 * @brief 在LCD1602上显示字符串
 *
 * @param str 指向要显示的字符串的指针
 */
void lcd1602_write_string(const char* str) {
    while (*str) {
        lcd1602_write_char(*str++); // 逐个字符发送到LCD
    }
}

/**
 * @brief 设置LCD1602的光标位置
 *
 * @param row 行号（0或1）
 * @param col 列号（0~15）
 */
void lcd1602_set_cursor(unsigned char row, unsigned char col) {
    unsigned char address;
    if (row > 1) row = 1;       // 边界保护
    if (col > 15) col = 15;     // 边界保护
    if (row == 0) {
        address = 0x80 + col;   // 第一行地址从0x80开始
    } else {
        address = 0xC0 + col;   // 第二行地址从0xC0开始
    }
    lcd_send_command(address);  // 发送设置光标地址的命令
}


/**
 * @brief 清除LCD1602屏幕内容
 */
void lcd1602_clear(void) {
    lcd_send_command(0x01);     // 发送清屏命令
    delay_ms(2);                // 等待清屏完成
}

/**
 * @brief 在LCD1602上显示无符号整数
 *
 * @param number 要显示的数字
 */
void lcd1602_write_number(unsigned int number) {
    char buffer[16];
    snprintf(buffer, sizeof(buffer), "%u", number); // 将数字转换为字符串
    lcd1602_write_string(buffer);                   // 显示转换后的字符串
}

#endif


