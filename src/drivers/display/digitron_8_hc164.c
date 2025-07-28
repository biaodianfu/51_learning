#include "config.h"
#if USE_DIGITRON_8_HC164
#include "digitron_8_hc164.h"

unsigned char __code tab[] = {
    0xc0, // 0 (共阳极数码管)
    0xf9, // 1
    0xa4, // 2
    0xb0, // 3
    0x99, // 4
    0x92, // 5
    0x82, // 6
    0xf8, // 7
    0x80, // 8
    0x90 // 9
};

static unsigned char display_digits[8] = {0};

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


void set_number(unsigned long num) {
    if(num > 99999999) num = 99999999;

    // 数字分解（不变）
    for(int i = 7; i >= 0; i--) {
        display_digits[i] = num % 10;
        num /= 10;
    }

    // 动态扫描优化
    for (unsigned char i = 0; i < 8; i++) {
        // 消隐阶段
        send_16bits(0xFF00);  // 全灭
        delay_us(5);          // 消隐时间

        // 数据显示
        unsigned char seg_code = tab[display_digits[i]];
        unsigned int data = (seg_code << 8) | (1 << i);
        send_16bits(data);

        // 显示时间（根据亮度需求调整）
        delay_us(30);
    }
    // 最终消隐
    send_16bits(0xFF00);
}


#endif // USE_DIGITRON_8_HC164S