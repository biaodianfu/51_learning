#include "config.h"

#if USE_DIGITRON_4_HC595
#include "digitron_4_hc595.h"

#define SEGMENT_BLANK 0xFF

// 共阳段码（dp g f e d c b a）
const unsigned char __code seg_code[] = {
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

// 显示缓存（4 位数码管），0xFF 表示灭
unsigned char digits_seg[] = {SEGMENT_BLANK, SEGMENT_BLANK, SEGMENT_BLANK, SEGMENT_BLANK};

/**
 * @brief 发送一个字节的数据到HC595移位寄存器
 * @param data 要发送的8位数据
 * @return 无返回值
 *
 * 该函数通过位操作将一个字节的数据逐位发送到HC595移位寄存器中，
 * 使用软件模拟SPI通信协议，先发送最高位(MSB)。
 */
void send_bits(const unsigned char data) {
    // 循环发送数据的每一位，从最高位开始
    for(unsigned char i = 0; i < 8; i++) {
        HC595_DIO = (data & 0x80) ? 1 : 0;  // 发送最高位
        HC595_SCLK = 0;
        HC595_SCLK = 1;
        data <<= 1;
    }
}

/**
 * @brief 刷新数码管显示
 *
 * 该函数循环刷新4位数码管的显示内容，
 * 每次发送一个段码和对应的位选信号。
 * 位选信号从左到右依次激活每一位数码管。
 */
void refresh_digitron(void)
{
    for(unsigned char i = 0; i < 4; i++)
    {
        send_bits(digits_seg[i]);             // 段码保持不变
        send_bits(1 << (3 - i));              // 位选从左到右
        HC595_RCLK = 0;
        HC595_RCLK = 1;
    }
}

/**
 * @brief 设置要显示的数字
 * @param num 要显示的数字，范围为0~9999
 * @param leading_zero 是否显示前导零，非0表示显示
 * @return 无返回值
 *
 * 该函数将输入的数字分解为4位，并根据是否显示前导零决定每一位的显示内容。
 * 如果输入数字超过9999，则截断为9999。
 */
void set_number(unsigned int num, unsigned char leading_zero) {
    if (num > 9999) num = 9999;

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
            digits_seg[i] = SEGMENT_BLANK;  // 空白
        else {
            digits_seg[i] = seg_code[raw_digits[i]];
            show_flag = 1; // 一旦开始显示数字，后续都要显示
        }
    }

    // 特殊处理：输入为0时，至少显示一个0
    if (num == 0) {
        digits_seg[3] = seg_code[0];
    }
}

/**
 * @brief 延时并刷新数码管显示
 * @param ms 延时毫秒数
 * @return 无返回值
 *
 * 该函数在延时期间持续刷新数码管显示，以保证显示稳定。
 * 每毫秒刷新一次数码管。
 */
void delay_ms_refresh(unsigned int ms)
{
    while(ms--)
    {
        refresh_digitron(); // 刷新数码管
        delay_ms(1);
    }
}

#endif // USE_DIGITRON_4_HC595
