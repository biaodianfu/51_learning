#include "config.h"
#if USE_DIGITRON_4_HC595x4
#include "digitron_4_hc595x4.h"

// 共阳数码管段码表（0~9）
const unsigned char digit_to_segment[] = {
        0xC0, // 0
        0xF9, // 1
        0xA4, // 2
        0xB0, // 3
        0x99, // 4
        0x92, // 5
        0x82, // 6
        0xF8, // 7
        0x80, // 8
        0x90  // 9
};

void HC595_WriteByte(unsigned char dat) {
    for (unsigned char i = 0; i < 8; i++) {
        HC595_SDI = (dat & 0x80);  // 最高位
        HC595_SCLK = 1;
        HC595_SCLK = 0;
        dat <<= 1;
    }
}

void HC595_Display(unsigned char seg1, unsigned char seg2, unsigned char seg3, unsigned char seg4) {
    HC595_LOAD = 0;
    HC595_WriteByte(seg1);  // 千位
    HC595_WriteByte(seg2);  // 百位
    HC595_WriteByte(seg3);  // 十位
    HC595_WriteByte(seg4);  // 个位
    HC595_LOAD = 1;
}

void set_number(unsigned int num, unsigned char leading_zero) {
    unsigned char digits[4];
    digits[0] = num / 1000;
    digits[1] = (num / 100) % 10;
    digits[2] = (num / 10) % 10;
    digits[3] = num % 10;

    unsigned char seg[4];
    for (int i = 0; i < 4; i++) {
        if (!leading_zero && digits[i] == 0 && i < 3) {
            seg[3-i] = 0xFF;  // 空白
        } else {
            seg[3-i] = digit_to_segment[digits[i]];
            leading_zero = 1; // 后续全部补上
        }
    }

    HC595_Display(seg[0], seg[1], seg[2], seg[3]);
}

#endif // USE_DIGITRON_4_HC595x4
