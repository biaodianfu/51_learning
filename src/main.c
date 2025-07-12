#include "STC89C5xRC.h"
#include "drivers/utils/delay.h"

void main()
{
    // 执行初始化
    while(1) {      // 无限循环，模拟loop
        P1 = 0x00;        // 点亮LED（假设低电平点亮）
        delay_ms(500);  // 延时500ms
        P1 = 0xFF;        // 熄灭LED
        delay_ms(500);  // 延时500ms
    }
}