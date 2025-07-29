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

// 初始化MAX7219
void max7219_init(void) {
    // 关闭显示测试
    max7219_write(0x0F, 0x00);

    // 禁用BCD解码
    max7219_write(0x09, 0x00);

    // 设置中等亮度
    max7219_write(0x0A, 0x07);

    // 扫描所有8位数码管
    max7219_write(0x0B, 0x07);

    // 正常操作模式
    max7219_write(0x0C, 0x01);

    // 清空显示
    max7219_write(0x01, 0x00);  // Digit 0 (最右边)
    max7219_write(0x02, 0x00);
    max7219_write(0x03, 0x00);
    max7219_write(0x04, 0x00);
    max7219_write(0x05, 0x00);
    max7219_write(0x06, 0x00);
    max7219_write(0x07, 0x00);
    max7219_write(0x08, 0x00);  // Digit 7 (最左边)
}

static unsigned char digits_seg[8] = {0};

void set_number(unsigned long num, unsigned char leading_zero) {
    if(num > 99999999) num = 99999999;

    unsigned char raw_digits[8] = {
            (num / 10000000) % 10,
            (num / 1000000) % 10,
            (num / 100000) % 10,
            (num / 10000) % 10,
            (num / 1000) % 10,
            (num / 100) % 10,
            (num / 10) % 10,
            num % 10
    };

    unsigned char show_flag = leading_zero;
    for(unsigned char i = 0; i < 8; i++)
    {
        if (!show_flag && raw_digits[i] == 0 && i < 7)
            digits_seg[i] = 0x00;  // 空白
        else {
            digits_seg[i] = seg_code[raw_digits[i]];
        }
    }
}

void refresh_digitron(void) {
    for(unsigned char i = 0; i < 8; i++) {
        max7219_write(i + 1, digits_seg[i]); // 寄存器1-8对应Digit0-Digit7
    }
}




void delay_ms_refresh(unsigned int ms)
{
    max7219_init(); // 初始化MAX7219
    while(ms--)
    {
        refresh_digitron(); // 刷新数码管
        delay_ms(1);       // 延时1毫秒
    }
}

#endif // USE_DIGITRON_8_MAX7219
