#include "config.h"
#if USE_DIGITRON_4
#include "digitron_4.h"

// 共阳数码管段码表（0-9，顺序为dp g f e d c b a）
unsigned char __code segCode[10] = {
    0xC0, // 0: 1100 0000
    0xF9, // 1: 1111 1001
    0xA4, // 2: 1010 0100
    0xB0, // 3: 1011 0000
    0x99, // 4: 1001 1001
    0x92, // 5: 1001 0010
    0x82, // 6: 1000 0010
    0xF8, // 7: 1111 1000
    0x80, // 8: 1000 0000
    0x90, // 9: 1001 0000
};

// 位选编码（第1~4位）
unsigned char __code bitCode[4] = {
    0xFE, // 第1位 1111 1110
    0xFD, // 第2位 1111 1101
    0xFB, // 第3位 1111 1011
    0xF7  // 第4位 1111 0111
};


// 显示的每一位段码（可能为数字段码或0xFF空白）
unsigned char digits_seg[4] = {0xFF, 0xFF, 0xFF, 0xFF};

// 刷新当前某一位（调用频率：1~5ms 一次）
void refresh_digitron(void) {
    static unsigned char pos = 0;

    DIG_SEG = 0xFF; // 清段
    DIG_DIG = bitCode[pos];     // 位选
    DIG_SEG = digits_seg[pos];  // 显示该位内容

    pos = (pos + 1) % 4;
}

// 设置当前显示数字，支持是否显示前导零
void set_number(unsigned int num, unsigned char leading_zero) {
    if (num > 9999) num = 9999;

    unsigned char raw_digits[4] = {
        (num / 1000) % 10,
        (num / 100) % 10,
        (num / 10) % 10,
        num % 10
    };

    unsigned char show_flag = leading_zero;
    for (unsigned char i = 0; i < 4; i++) {
        if (!show_flag && raw_digits[i] == 0 && i < 3) {
            digits_seg[i] = 0xFF;  // 空白
        } else {
            show_flag = 1;
            digits_seg[i] = segCode[raw_digits[i]];
        }
    }
}

// 延时并保持刷新数码管显示
void delay_ms_refresh(unsigned int t) {
    while (t--) {
        refresh_digitron();
        delay_ms(1);
    }
}

#endif

