#include "config.h"
#if USE_DIGITRON_8_HC164

#include "digitron_8_hc164.h"

/**
 * @brief 共阳数码管0-9的段码表
 *
 * 每个字节表示一个数字在共阳极数码管上的点亮模式。
 * 位顺序为 gfedcba，其中 0 表示点亮，1 表示熄灭。
 */
unsigned char __code seg_code[] = {
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

/**
 * @brief 发送16位数据到HC164移位寄存器
 *
 * 数据格式为高位字节为段选数据，低位字节为位选数据。
 * 使用AB引脚输出数据位，CP引脚提供时钟信号。
 *
 * @param data 要发送的16位数据
 */
void send_16bits(unsigned int data) {
    unsigned char high_byte = (data >> 8) & 0xFF;  // 段选数据（高位）
    unsigned char low_byte = data & 0xFF;          // 位选数据（低位）

    // 发送高位字节（段选）
    for (unsigned char i = 0; i < 8; i++) {
        CP = 0;
        AB = (high_byte & 0x80) ? 1 : 0;
        CP = 1;
        high_byte <<= 1;
    }

    // 发送低位字节（位选）
    for (unsigned char i = 0; i < 8; i++) {
        CP = 0;
        AB = (low_byte & 0x80) ? 1 : 0;
        CP = 1;
        low_byte <<= 1;
    }
}

/**
 * @brief 存储每个数码管显示的段码
 *
 * 数组中每个元素对应一个数码管的段码值。
 */
static unsigned char digits_seg[8] = {0};

/**
 * @brief 设置要显示的数字并转换为段码
 *
 * 将输入的数字分解为8位数字，并根据是否显示前导零决定显示方式。
 *
 * @param num 要显示的数字（最大99999999）
 * @param leading_zero 是否显示前导零（非0表示显示）
 */
void set_number(unsigned long num, unsigned char leading_zero) {
    if (num > 99999999) num = 99999999;

    unsigned char raw_digits[8];
    unsigned long temp = num;

    // 从低位到高位提取每一位数字
    for (signed char i = 7; i >= 0; i--) {
        raw_digits[i] = temp % 10;
        temp /= 10;
    }

    unsigned char show_flag = leading_zero || (num == 0);  // 至少显示一个0
    for (unsigned char i = 0; i < 8; i++) {
        if (!show_flag && raw_digits[i] == 0 && i < 7) {
            digits_seg[i] = 0xFF;  // 空白
        } else {
            show_flag = 1;  // 开始显示数字
            digits_seg[i] = seg_code[raw_digits[i]];
        }
    }
}

/**
 * @brief 刷新数码管显示
 *
 * 依次将每个数码管的段码和位选数据发送至HC164，
 * 实现动态扫描显示。
 */
void refresh_digitron(void) {
    for (unsigned char i = 0; i < 8; i++) {
        send_16bits((digits_seg[i] << 8) | (1 << i)); // 段码和位选
        delay_ms(1); // 确保数据稳定
    }
}

/**
 * @brief 延时并刷新数码管显示
 *
 * 在延时期间持续刷新数码管以保持显示效果。
 *
 * @param ms 延时毫秒数
 */
void delay_ms_refresh(unsigned int ms) {
    while (ms--) {
        refresh_digitron(); // 刷新数码管
        delay_ms(1);
    }
}

#endif // USE_DIGITRON_8_HC164