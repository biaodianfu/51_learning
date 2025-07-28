#include "config.h"
#if USE_DIGITRON_8_MAX7219
#include "digitron_8_max7219.h"

// 数码管段码表 (0-9,A-F)
unsigned char __code seg_code[] = {
    0x7E, // 0
    0x30, // 1
    0x6D, // 2
    0x79, // 3
    0x33, // 4
    0x5B, // 5
    0x5F, // 6
    0x70, // 7
    0x7F, // 8
    0x7B // 9
};


// 写入寄存器函数
void max7219_write(unsigned char addr, unsigned char dat) {
    unsigned int frame;
    unsigned char i;

    // 构造16位数据帧
    frame = (unsigned int)addr << 8 | dat;

    CS = 0;  // 开始传输

    // 发送16位数据 (MSB先发)
    for(i = 0; i < 16; i++) {
        CLK = 0;  // 时钟下降沿

        // 设置数据位
        if(frame & 0x8000) {
            DIN = 1;
        } else {
            DIN = 0;
        }
        frame = frame << 1;  // 准备下一位

        // 短延时确保信号稳定
        _nop_(); _nop_(); _nop_();
        _nop_(); _nop_(); _nop_();

        CLK = 1;  // 时钟上升沿
        _nop_(); _nop_(); _nop_();
    }

    CLK = 0;    // 时钟恢复低电平
    LOAD = 1;   // 结束传输
}

//// 初始化MAX7219
//void MAX7219_Init(void) {
//    // 关闭显示测试
//    MAX7219_Write(0x0F, 0x00);
//
//    // 禁用BCD解码
//    MAX7219_Write(0x09, 0x00);
//
//    // 设置中等亮度
//    MAX7219_Write(0x0A, 0x07);
//
//    // 扫描所有8位数码管
//    MAX7219_Write(0x0B, 0x07);
//
//    // 正常操作模式
//    MAX7219_Write(0x0C, 0x01);
//
//    // 清空显示
//    MAX7219_Write(0x01, 0x00);  // Digit 0 (最右边)
//    MAX7219_Write(0x02, 0x00);
//    MAX7219_Write(0x03, 0x00);
//    MAX7219_Write(0x04, 0x00);
//    MAX7219_Write(0x05, 0x00);
//    MAX7219_Write(0x06, 0x00);
//    MAX7219_Write(0x07, 0x00);
//    MAX7219_Write(0x08, 0x00);  // Digit 7 (最左边)
//}
//
//// 设置数码管显示 (修正位序)
//void Set_Digit(unsigned char pos, unsigned char val) {
//    unsigned char reg;
//
//    // 调整位序：实际数码管位置0-7对应寄存器1-8
//    // 位置0: 最右边 (Digit0) -> 寄存器1
//    // 位置7: 最左边 (Digit7) -> 寄存器8
//    reg = pos + 1;  // 寄存器地址 = 位置 + 1
//
//    if(val < 16) {
//        MAX7219_Write(reg, digitTable[val]); // 显示数字
//    } else {
//        MAX7219_Write(reg, digitTable[16]); // 显示空格
//    }
//}
//
//// 显示整数值 (修正位序)
//void Display_Number(unsigned long num) {
//    unsigned char i;
//    unsigned char digits[8];  // 存储8位数字 (右到左)
//
//    // 分离数字 (从低位到高位)
//    for(i = 0; i < 8; i++) {
//        digits[i] = num % 10;   // 当前位数字
//        num = num / 10;         // 移除已处理数字
//    }
//
//    // 设置数码管 (右到左显示)，位置0为最右边
//    for(i = 0; i < 8; i++) {
//        // 设置第i位数码管 (从右向左)
//        Set_Digit(i, digits[i]);
//    }
//}
//

//// 主程序
//void main(void) {
//    unsigned long counter = 12345678; // 初始显示数字
//
//    // 初始化IO
//    DIN = 0;
//    LOAD = 1;
//    CLK = 0;
//    delay_ms(100);  // 电源稳定延时
//
//    // 初始化MAX7219
//    MAX7219_Init();
//
//    // 主循环
//    while(1) {
//        Display_Number(counter);  // 显示当前数值
//        counter = (counter + 1) % 100000000;  // 0-99999999循环
//        delay_ms(100);
//    }
//}

#endif // USE_DIGITRON_8_MAX7219
