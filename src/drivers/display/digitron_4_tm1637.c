#include "config.h"

#if USE_DIGITRON_4_TM1637
#include "digitron_4_tm1637.h"

unsigned char __code seg_code[] = {
    0x3f, // 0: 0011 1111
    0x06, // 1: 0000 0110
    0x5b, // 2: 0101 1011
    0x4f, // 3: 0100 1111
    0x66, // 4: 0110 0110
    0x6d, // 5: 0110 1101
    0x7d, // 6: 0111 1101
    0x07, // 7: 0000 0111
    0x7f, // 8: 0111 1111
    0x6f  // 9: 0110 1111
};

// 延时函数（~5us）
void tm1637_delay(void) {
    ASM_NOP();ASM_NOP();ASM_NOP();ASM_NOP();ASM_NOP();
}

void tm1637_start(void) {
    TM1637_DIO = 1;
    TM1637_CLK = 1;
    tm1637_delay();
    TM1637_DIO = 0;
    tm1637_delay();
    TM1637_CLK = 0;
}

void tm1637_stop(void) {
    TM1637_CLK = 0;
    TM1637_DIO = 0;
    tm1637_delay();
    TM1637_CLK = 1;
    tm1637_delay();
    TM1637_DIO = 1;
}

void tm1637_send_bits(unsigned char data) {
    for (unsigned i = 0; i < 8; i++) {
        TM1637_CLK = 0;
        TM1637_DIO = (data & 0x01);
        tm1637_delay();
        TM1637_CLK = 1;
        tm1637_delay();
        data >>= 1;
    }

    // 等待 ACK
    TM1637_CLK = 0;
    TM1637_DIO = 1;
    tm1637_delay();
    TM1637_CLK = 1;
    tm1637_delay();
    TM1637_CLK = 0;
}

// 设置亮度（0-7）
void tm1637_init(void) {
    tm1637_start();
    tm1637_send_bits(0x88 + 7); // 0x88 = 显示开 + 亮度最低，+7 为最高亮度
    tm1637_stop();
}

// 写入一个数字（0~9或空白）
void tm1637_display_data(unsigned index, unsigned data) {
    tm1637_start();
    tm1637_send_bits(0x44); // 地址模式固定
    tm1637_stop();

    tm1637_start();
    tm1637_send_bits(0xC0 + index); // 地址 = 0xC0 + digit位置
    tm1637_send_bits(data);
    tm1637_stop();
}

void tm1637_clear(void) {
    for (unsigned char i = 0; i < 4; i++) {
        tm1637_display_data(i, 0x00); // 空白
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
            digits_seg[i] = 0x00;  // 空白
        else {
            digits_seg[i] = seg_code[raw_digits[i]];
        }
    }
}

void refresh_digitron(void)
{
    for(unsigned char i = 0; i < 4; i++)
    {
        tm1637_display_data(i,digits_seg[i]); // 发送段码
    }
}

void delay_ms_refresh(unsigned int t){
    tm1637_init(); // 初始化TM1637
    while (t--) {
        refresh_digitron(); // 刷新显示
        delay_ms(1);
    }
    tm1637_clear(); // 清除显示
}




#endif
