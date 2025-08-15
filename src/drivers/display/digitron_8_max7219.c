#include "config.h"
#if USE_DIGITRON_8_MAX7219
#include "digitron_8_max7219.h"

/**
 * @brief 数码管段码表，用于显示数字0-9。
 * 每个字节表示一个数字在共阴极数码管上的点亮段。
 */
const unsigned char __code seg_code[] = {
    0x7E, // 0
    0x30, // 1
    0x6D, // 2
    0x79, // 3
    0x33, // 4
    0x5B, // 5
    0x5F, // 6
    0x70, // 7
    0x7F, // 8
    0x7B  // 9
};

/**
 * @brief 向MAX7219发送一个字节数据，带延时以确保信号稳定。
 *
 * @param data 要发送的字节数据
 */
void write_max7219_byte_with_delay(unsigned char data) {
    for (unsigned char i = 0; i < 8; i++) {
        MAX7219_CLK = 0;
        MAX7219_DIN = (data & 0x80) ? 1 : 0;
        data <<= 1;

        // 短延时确保信号稳定
        ASM_NOP(); ASM_NOP(); ASM_NOP();
        ASM_NOP(); ASM_NOP(); ASM_NOP();

        MAX7219_CLK = 1;
        ASM_NOP(); ASM_NOP(); ASM_NOP();
    }
}

/**
 * @brief 向MAX7219写入指定地址的数据。
 *
 * @param addr 寄存器地址
 * @param data 要写入的数据
 */
void max7219_write(unsigned char addr, unsigned char data) {
    MAX7219_CS = 0;
    write_max7219_byte_with_delay(addr);
    write_max7219_byte_with_delay(data);
    MAX7219_CS = 1;
    MAX7219_CLK = 0;
}

/**
 * @brief 初始化MAX7219芯片。
 * 包括关闭测试模式、禁用BCD解码、设置亮度和扫描位数等。
 */
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

/**
 * @brief 存储每个数码管要显示的段码。
 */
static unsigned char digits_seg[8] = {0};

/**
 * @brief 将一个无符号长整型数字转换为8位数码管显示格式。
 *
 * @param num 要显示的数字（最大99999999）
 * @param leading_zero 是否显示前导零（非零表示显示）
 */
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

    unsigned char show_flag = leading_zero || (num == 0); // 当num为0时至少显示一位
    for(unsigned char i = 0; i < 8; i++)
    {
        if (!show_flag && raw_digits[i] == 0 && i < 7)
            digits_seg[7-i] = 0x00;  // 空白
        else {
            digits_seg[7-i] = seg_code[raw_digits[i]];
            show_flag = 1; // 一旦开始显示数字，后续数字都要显示
        }
    }
}

/**
 * @brief 刷新数码管显示内容。
 * 将digits_seg数组中的段码写入到对应的数码管寄存器中。
 */
void refresh_digitron(void) {
    for(unsigned char i = 0; i < 8; i++) {
        max7219_write(i + 1, digits_seg[i]); // 寄存器1-8对应Digit0-Digit7
    }
}

/**
 * @brief 延时并刷新数码管显示。
 * 在延时期间持续刷新数码管以保持显示效果。
 *
 * @param ms 延时时间（毫秒）
 */
void delay_ms_refresh(unsigned int ms)
{
    // max7219_init(); // 初始化应移至系统启动时调用，此处移除
    while(ms--)
    {
        refresh_digitron(); // 刷新数码管
        delay_ms(1);       // 延时1毫秒
    }
}


#endif // USE_DIGITRON_8_MAX7219