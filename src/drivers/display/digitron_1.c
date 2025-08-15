#include "config.h"
#if USE_DIGITRON_1
#include "digitron_1.h"

// 定义小数点状态常量以增强可读性
#define DP_ON  0
#define DP_OFF 1

/**
 * @brief 共阳数码管0-9的段码表，用于显示数字0到9
 *
 * 段码按照gfedcba顺序排列，0表示该段点亮，1表示该段熄灭。
 * 例如：0xC0 对应二进制 1100 0000，表示数码管显示数字0。
 */
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

/**
 * @brief 在数码管上显示一个数字，并控制小数点是否点亮
 *
 * 该函数根据输入的数字在数码管上显示出对应的段码。如果输入数字超出0~9范围，
 * 则关闭所有段（显示空白）。同时根据dp参数决定是否点亮小数点。
 *
 * @param num 要显示的数字，有效值为0~9
 * @param dp 小数点控制参数，非0时点亮小数点，0时熄灭小数点
 */
void show_number(unsigned char num, unsigned char dp) {
    // 显示数字0-9或小数点
    if (num < 10) {
        DIG_1 = seg_code[num];
    } else {
        // 如果num不在0-9范围内，默认关闭所有段
        DIG_1 = 0xFF;
    }

    // 确保 dp 参数归一化为 0 或 1，并控制小数点显示
    if ((dp != 0)) {
        DIG_DP = DP_ON;   // 小数点亮
    } else {
        DIG_DP = DP_OFF;  // 小数点灭
    }
}

#endif // USE_DIGITRON_1