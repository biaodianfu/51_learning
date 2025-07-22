#include "config.h"
#if USE_DIGITRON_1
#include "digitron_1.h"

//共阳数码管0-9的段码表
unsigned char __code segCode[] = {
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
        0x90, // 9: 1001 0000
        0x7F  // .: 0111 1111
};

void show_number(unsigned char num, unsigned char dp) {
    // 显示数字0-9或小数点
    if (num < 10) {
        DIG_1 = segCode[num];
    } else {
        // 如果num不在0-9范围内，默认显示0
        DIG_1 = 0xFF; // 关闭所有段
    }
    // 控制小数点显示
    if (dp) {
        DIG_DP = 0; // 小数点亮
    } else {
        DIG_DP = 1; // 小数点灭
    }
}

#endif // USE_DIGITRON_1