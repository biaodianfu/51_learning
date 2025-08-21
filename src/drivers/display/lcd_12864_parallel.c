#include "config.h"
#if USE_LCD_12864_PARALLEL
#include "lcd_12864_parallel.h"

// 新增：忙标志检查函数
void lcd_wait_ready(void) {
    while(lcd_read_status() & 0x80); // 检查BF标志(DB7)
}

static void lcd_enable(void) {
    LCD_E = 1;
    delay_us(1);
    LCD_E = 0;
    delay_us(1);
}

// 修改：发送前添加忙等待
void lcd_send_byte(unsigned char dat, unsigned char mode) {
    lcd_wait_ready();  // ★★★ 关键修复 ★★★

    LCD_RW = 0;
    LCD_RS = (mode == DATA) ? 1 : 0;
    LCD_DATA = dat;
    lcd_enable();
}

unsigned char lcd_read_status(void) {
    unsigned char status;

    // 设置读模式
    LCD_RW = 1;
    LCD_RS = 0;         // 读状态

    // 准备读取数据
    LCD_DATA = 0xFF;    // 51单片机P2口设为输入

    // 产生使能信号
    LCD_E = 1;
    delay_us(1);
    status = LCD_DATA;   // 读取状态
    LCD_E = 0;

    LCD_RW = 0;         // 恢复写模式
    return status;
}

// 修改：初始化序列
void lcd_init(void) {
    LCD_RST = 0;
    delay_ms(10);
    LCD_RST = 1;
    delay_ms(20);

    // 修正初始化序列
    lcd_send_byte(0x30, CMD);  // 功能设置
    delay_ms(5);
    lcd_send_byte(0x30, CMD);  // ★ 第二次功能设置
    delay_ms(1);

    lcd_send_byte(0x0C, CMD);  // 显示控制
    delay_ms(1);

    lcd_send_byte(0x06, CMD);  // 进入模式
    delay_ms(1);

    lcd_clear();  // 清屏
}

// 修改：延长清屏时间
void lcd_clear(void) {
    lcd_send_byte(0x01, CMD);
    delay_ms(6);  // ★ 延长至6ms
}

// 修改：添加忙等待
void lcd_set_position(unsigned char row, unsigned char col) {
    const unsigned char row_addr[4] = {0x80, 0x90, 0x88, 0x98};
    unsigned char address = row_addr[row] + col;
    lcd_send_byte(address, CMD);
    lcd_wait_ready();  // ★ 等待地址设置完成
}

// 重构：中文处理逻辑
void lcd_print(const char *str) {
    unsigned char chinese_flag = 0;
    char high_byte = 0;

    while (*str) {
        if (*str >= 0xA1 && !chinese_flag) {
            high_byte = *str++;
            chinese_flag = 1;
            continue;
        }

        if (chinese_flag) {
            lcd_send_byte(high_byte, DATA);
            lcd_send_byte(*str, DATA);
            chinese_flag = 0;
        } else {
            lcd_send_byte(*str, DATA);
        }
        str++;
    }
}
#endif
