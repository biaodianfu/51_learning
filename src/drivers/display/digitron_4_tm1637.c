#include "config.h"
#if USE_DIGITRON_4_TM1637
#include "digitron_4_tm1637.h"

static const __code unsigned char SEG_TAB[] = {
    0x3f, // 0
    0x06, // 1
    0x5b, // 2
    0x4f, // 3
    0x66, // 4
    0x6d, // 5
    0x7d, // 6
    0x07, // 7
    0x7f, // 8
    0x6f, // 9
    0x00  // 空白
};

// 延时函数（~5us）
void TM1637_delay(void) {
    __asm__("nop"); __asm__("nop"); __asm__("nop"); __asm__("nop"); __asm__("nop");
}

void TM1637_start(void) {
    TM1637_DIO = 1;
    TM1637_CLK = 1;
    TM1637_delay();
    TM1637_DIO = 0;
    TM1637_delay();
    TM1637_CLK = 0;
}

void TM1637_stop(void) {
    TM1637_CLK = 0;
    TM1637_DIO = 0;
    TM1637_delay();
    TM1637_CLK = 1;
    TM1637_delay();
    TM1637_DIO = 1;
}

void TM1637_write_byte(unsigned char data) {
    for (unsigned i = 0; i < 8; i++) {
        TM1637_CLK = 0;
        TM1637_DIO = (data & 0x01);
        TM1637_delay();
        TM1637_CLK = 1;
        TM1637_delay();
        data >>= 1;
    }

    // 等待 ACK
    TM1637_CLK = 0;
    TM1637_DIO = 1;
    TM1637_delay();
    TM1637_CLK = 1;
    TM1637_delay();
    TM1637_CLK = 0;
}

// 设置亮度（0-7）
void TM1637_init(void) {
    TM1637_start();
    TM1637_write_byte(0x88 + 7); // 0x88 = 显示开 + 亮度最低，+7 为最高亮度
    TM1637_stop();
}

// 写入一个数字（0~9或空白）
void TM1637_display_digit(unsigned index, unsigned digit) {
    TM1637_start();
    TM1637_write_byte(0x44); // 地址模式固定
    TM1637_stop();

    TM1637_start();
    TM1637_write_byte(0xC0 + index); // 地址 = 0xC0 + digit位置
    TM1637_write_byte(SEG_TAB[digit]);
    TM1637_stop();
}

// 显示一个 0~9999 数字，支持前导零
void TM1637_display_number(unsigned int num, unsigned char leading_zero) {
    unsigned char d[4];

    d[0] = (num / 1000) % 10;
    d[1] = (num / 100) % 10;
    d[2] = (num / 10) % 10;
    d[3] = num % 10;

    unsigned char show = leading_zero;

    for (unsigned char i = 0; i < 4; i++) {
        if (!show && d[i] == 0 && i < 3)
            TM1637_display_digit(i, 10); // 空白
        else {
            show = 1;
            TM1637_display_digit(i, d[i]);
        }
    }
}

void TM1637_clear(void) {
    for (unsigned char i = 0; i < 4; i++) {
        TM1637_display_digit(i, 10); // 空白
    }
}

#endif
