#include "config.h"

#if USE_DIGITRON_4
#include "digitron_4.h"

// 共阳数码管段码表（0-9，顺序为dp g f e d c b a）
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
    0x90, // 9: 1001 0000
};

// 位选编码（第1~4位）
const unsigned char __code bit_code[] = {
    0xFE, // 第1位 1111 1110
    0xFD, // 第2位 1111 1101
    0xFB, // 第3位 1111 1011
    0xF7  // 第4位 1111 0111
};

// 显示的每一位段码（可能为数字段码或0xFF空白）
unsigned char digits_seg[4] = {0xFF, 0xFF, 0xFF, 0xFF};

// 当前刷新位置（模块级静态变量以避免并发问题）
static unsigned char pos = 0;

/**
 * @brief 刷新当前某一位数码管显示
 *
 * 该函数用于动态扫描数码管，每次调用刷新一位数码管。
 * 调用频率建议为1~5ms一次，以保证显示稳定。
 */
void refresh_digitron(void) {
    DIG_SEG = 0xFF;              // 清除所有段选信号
    DIG_DIG = bit_code[pos];     // 设置当前位选信号
    DIG_SEG = digits_seg[pos];   // 输出当前位的段码

    pos = (pos + 1) % 4;         // 更新下一位刷新位置
}

/**
 * @brief 设置要显示的数字，并控制是否显示前导零
 *
 * @param num 要显示的数字，范围应为0~9999
 * @param leading_zero 是否显示前导零：
 *                     - 非0：显示前导零
 *                     - 0：不显示前导零，前面补空
 */
void set_number(unsigned int num, unsigned char leading_zero) {
    if (num > 9999) num = 9999;

    // 将数字分解为千、百、十、个位
    unsigned char raw_digits[4] = {
        (num / 1000) % 10,
        (num / 100) % 10,
        (num / 10) % 10,
        num % 10
    };

    unsigned char show_flag = leading_zero; // 标记是否已经开始显示数字

    // 处理每一位数字的显示逻辑
    for (unsigned char i = 0; i < 4; i++) {
        if (!show_flag && raw_digits[i] == 0 && i < 3) {
            digits_seg[i] = 0xFF;  // 空白
        } else {
            digits_seg[i] = seg_code[raw_digits[i]];
            show_flag = 1; // 一旦开始显示数字，后续都要显示
        }
    }
}

/**
 * @brief 延时指定毫秒数，并在延时期间持续刷新数码管显示
 *
 * @param t 延时时间（单位：毫秒）
 */
void delay_ms_refresh(unsigned int t) {
    while (t--) {
        refresh_digitron();       // 每毫秒刷新一次数码管
        delay_ms(1);              // 确保 delay_ms 已正确定义
    }
}

#endif