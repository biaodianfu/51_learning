#include "config.h"
#if USE_LCD_12864_SERIAL
#include "lcd_12864_serial.h"

// 内部函数：发送单bit
static void send_bit(unsigned char bit) {
    LCD_SID = bit;
    LCD_SCLK = 1;
    delay_us(1);
    LCD_SCLK = 0;
    delay_us(1);
}

// 内部函数：发送单字节
static void send_byte(unsigned char byte) {
    for (uint8_t i = 0; i < 8; i++) {
        send_bit(byte & 0x80);
        byte <<= 1;
    }
}

// 公共函数：发送数据/指令
void lcd_send_byte(unsigned char dat, unsigned char mode) {
    unsigned char ctrl_byte = 0xF8 | (mode << 1); // 控制字节
    LCD_CS = 1; // 使能片选
    send_byte(ctrl_byte);
    send_byte(dat & 0xF0);       // 高4位
    send_byte((dat & 0x0F) << 4);// 低4位
    LCD_CS = 0; // 禁用片选
}

// 初始化LCD
void lcd_init(void) {
    // 配置为串行模式

    delay_ms(50); // 上电延时

    lcd_send_byte(0x30, CMD); // 功能设置
    delay_ms(5);

    lcd_send_byte(0x0C, CMD); // 开显示
    delay_ms(1);

    lcd_clear();            // 清屏

    lcd_send_byte(0x06, CMD); // 光标右移
    delay_ms(1);
}

// 清屏
void lcd_clear(void) {
    lcd_send_byte(0x01, CMD); // 清屏指令
    delay_ms(5);             // 等待清屏完成
}

// 设置显示位置
void lcd_set_position(unsigned char row, unsigned char col) {
    const unsigned char row_addr[4] = {0x80, 0x90, 0x88, 0x98};
    unsigned char address = row_addr[row];

    // 中文每行最多8字符，英文最多16字符
    // 自动处理列偏移
    address += (col >> 1);

    lcd_send_byte(address, CMD);
    delay_ms(1);
}

// 打印单个字符（自动处理中文）
void lcd_putchar(char c) {
    static unsigned char chinese_flag = 0;
    static unsigned char chinese_high = 0;

    // 中文处理（GB2312编码范围）
    if (c >= 0xA1) {
        if (!chinese_flag) {
            // 中文字符第一个字节
            chinese_high = c;
            chinese_flag = 1;
            return;
        } else {
            // 中文字符第二个字节
            lcd_send_byte(chinese_high, DATA);
            lcd_send_byte(c, DATA;
            chinese_flag = 0;
            delay_ms(1);
            return;
        }
    }

    // ASCII字符（单字节）
    lcd_send_byte(c, DATA);
    delay_ms(1);
}

// 打印字符串（支持中文）
void lcd_print(const char *str) {
    while (*str) {
        lcd_putchar(*str++);
    }
}
#endif //USE_LCD_12864_SERIAL

