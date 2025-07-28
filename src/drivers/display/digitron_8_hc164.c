#include "config.h"
#if USE_DIGITRON_8_HC164
#include "digitron_8_hc164.h"

//共阳数码管0-9的段码表
unsigned char __code seg_code[] = {
// gfedcba 顺序 (0=亮,1=灭)
        0xC0, // 0: 1100 0000
        0xF9, // 1: 1111 1001
        0xA4, // 2: 1010 0100
        0xB0, // 3: 1011 0000
        0x99, // 4: 1001 1001
        0x92, // 5: 1001 0010
        0x82, // 6: 1000 0010
        0xF8, // 7: 1111 1000
        0x80, // 8: 1000 0000
        0x90  // 9: 1001 0000
};

void send_16bits(unsigned int data) {
    unsigned char num, c;
    num = (data >> 8) & 0xFF;  // 段选数据（高位）
    for (c = 0; c < 8; c++) {
        CP = 0;
        AB = (num & 0x80) ? 1 : 0;
        CP = 1;
        num <<= 1;
    }

    num = data & 0xFF;  // 位选数据（低位）
    for (c = 0; c < 8; c++) {
        CP = 0;
        AB = (num & 0x80) ? 1 : 0;
        CP = 1;
        num <<= 1;
    }
}

static unsigned char digits_seg[8] = {0};

void set_number(unsigned long num, unsigned char leading_zero) {
    if(num > 99999999) num = 99999999;

    unsigned char raw_digits[8] = {
            (num / 10000000) % 10,
            (num / 1000000) % 10,
            (num / 100000) % 10,
            (num / 10000) % 10,
            (num / 1000) % 10,
            (num / 100) % 10,
            (num / 10) % 10,
            num % 10
    };

    unsigned char show_flag = leading_zero;
    for(unsigned char i = 0; i < 8; i++)
    {
        if (!show_flag && raw_digits[i] == 0 && i < 7)
            digits_seg[i] = 0xFF;  // 空白
        else {
            digits_seg[i] = seg_code[raw_digits[i]];
        }
    }
}

void refresh_digitron(void) {
    for(unsigned char i = 0; i < 8; i++) {
        send_16bits((digits_seg[i] << 8) | (1 << i)); // 段码和位选
    }
    send_16bits(0xFF00); // 最终消隐
}

void delay_ms_refresh(unsigned int ms)
{
    while(ms--)
    {
        refresh_digitron(); // 刷新数码管
        delay_ms(1);
    }
}

#endif // USE_DIGITRON_8_HC164S