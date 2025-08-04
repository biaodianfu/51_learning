#include "config.h"
#if USE_DIGITRON_4_HC595x4
#include "digitron_4_hc595x4.h"

/**
 * @brief 共阳数码管段码表（0~9）
 *
 * 用于驱动共阳极数码管显示数字0到9的段码值。
 * 每个字节对应一个数字的亮灭状态，bit为0表示该段点亮。
 */
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

/**
 * @brief 向HC595移位寄存器发送8位数据
 *
 * 通过软件模拟SPI方式，将一个字节的数据逐位发送给HC595。
 * 数据从高位开始传输。
 *
 * @param data 要发送的8位数据
 */
void send_bits(unsigned char data) {
    for (unsigned char i = 0; i < 8; i++) {
        HC595_SCLK = 1;
        HC595_SDI = (data & 0x80);  // 取最高位
        HC595_SCLK = 1;
        data <<= 1;
    }
}


/**
 * @brief 数码管显示缓存（4 位）
 *
 * 存储每一位数码管要显示的段码值。初始值为0xFF，表示所有段都不亮（空白）。
 */
unsigned char digits_seg[] = {0xFF, 0xFF, 0xFF, 0xFF};

/**
 * @brief 设置要显示的数字
 *
 * 将输入的数字分解为千、百、十、个位，并根据是否显示前导零来决定数码管的显示内容。
 * 如果数字超过9999，则限制为9999。
 *
 * @param num 要显示的数字（范围：0~9999）
 * @param leading_zero 是否显示前导零（非0表示显示）
 */
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
            digits_seg[3-i] = 0xFF;  // 不显示前导零时设为空白
        else {
            digits_seg[3-i] = seg_code[raw_digits[i]];
            show_flag = 1; // 一旦显示了非零数字，后续数字都显示
        }
    }
}

/**
 * @brief 刷新数码管显示
 *
 * 将当前digits_seg数组中的段码依次发送到4个HC595芯片，
 * 并通过LOAD信号锁存输出，更新数码管显示内容。
 */
void refresh_digitron(void)
{
    HC595_LOAD = 0;
    for(unsigned char i = 0; i < 4; i++)
    {
        send_bits(digits_seg[i]); // 发送段码
    }
    HC595_LOAD = 1;
}

/**
 * @brief 延时并刷新显示
 *
 * 在延时期间持续刷新数码管显示，防止显示闪烁。
 *
 * @param t 延时时间（单位：毫秒）
 */
void delay_ms_refresh(unsigned int t) {
    while (t--) {
        refresh_digitron(); // 刷新显示
        delay_ms(1);
    }
}

#endif // USE_DIGITRON_4_HC595x4