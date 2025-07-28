#include "config.h"
#if USE_DIGITRON_4_HC595x4
#include "digitron_4_hc595x4.h"

// 共阳数码管段码表（0~9）
unsigned char __code seg_code[] = {
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

void send_bits(unsigned char data) {
    for (unsigned char i = 0; i < 8; i++) {
        HC595_SDI = (data & 0x80);  // 最高位
        HC595_SCLK = 1;
        HC595_SCLK = 0;
        data <<= 1;
    }
}



// 显示缓存（4 位数码管）
unsigned char digits_seg[] = {0xFF, 0xFF, 0xFF, 0xFF};

void set_number(unsigned int num, unsigned char leading_zero) {
    if (num > 9999) num = 9999; // 限制最大值为9999

    unsigned char raw_digits[4] = {
        (num / 1000) % 10,
        (num / 100) % 10,
        (num / 10) % 10,
        num % 10
    };

    unsigned char show_flag = leading_zero;
    for(unsigned char i = 0; i < 4; i++)
    {
        if (!show_flag && raw_digits[i] == 0 && i < 3)
            digits_seg[3-i] = 0xFF;  // 空白
        else {
            digits_seg[3-i] = seg_code[raw_digits[i]];
        }
    }
}

void refresh_digitron(void)
{
    HC595_LOAD = 0;
    for(unsigned char i = 0; i < 4; i++)
    {
        send_bits(digits_seg[i]); // 发送段码
    }
    HC595_LOAD = 1;
}

void delay_ms_refresh(unsigned int t) {
    while (t--) {
        refresh_digitron(); // 刷新显示
        delay_ms(1);
    }
}

#endif // USE_DIGITRON_4_HC595x4
