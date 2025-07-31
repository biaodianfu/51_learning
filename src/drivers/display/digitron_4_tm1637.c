#include "config.h"

#if USE_DIGITRON_4_TM1637
#include "digitron_4_tm1637.h"

/**
 * @brief 七段数码管段码表（共阴极）
 *
 * 每个字节表示一个数字对应的段点亮情况：
 * bit0 ~ bit6 分别对应 a ~ g 段
 */
unsigned char __code seg_code[] = {
    0x3f, // 0: 0011 1111
    0x06, // 1: 0000 0110
    0x5b, // 2: 0101 1011
    0x4f, // 3: 0100 1111
    0x66, // 4: 0110 0110
    0x6d, // 5: 0110 1101
    0x7d, // 6: 0111 1101
    0x07, // 7: 0000 0111
    0x7f, // 8: 0111 1111
    0x6f  // 9: 0110 1111
};

/**
 * @brief 微秒级延时函数（约5us）
 *
 * 使用多个空操作指令实现短时间延时
 */
void tm1637_delay(void) {
    ASM_NOP();ASM_NOP();ASM_NOP();ASM_NOP();ASM_NOP();
}

/**
 * @brief 发送起始信号到 TM1637
 *
 * 起始条件：CLK 高电平时 DIO 由高变低
 */
void tm1637_start(void) {
    TM1637_DIO = 1;
    TM1637_CLK = 1;
    tm1637_delay();
    TM1637_DIO = 0;
    tm1637_delay();
    TM1637_CLK = 0;
}

/**
 * @brief 发送停止信号到 TM1637
 *
 * 停止条件：CLK 高电平时 DIO 由低变高
 */
void tm1637_stop(void) {
    TM1637_CLK = 0;
    TM1637_DIO = 0;
    tm1637_delay();
    TM1637_CLK = 1;
    tm1637_delay();
    TM1637_DIO = 1;
}

/**
 * @brief 向 TM1637 发送一个字节数据
 *
 * 数据在 CLK 下降沿时从 DIO 输出，高位先发
 * 发送完成后等待并检测 ACK 信号
 *
 * @param data 要发送的数据（8位）
 */
void tm1637_send_bits(unsigned char data) {
    for (unsigned i = 0; i < 8; i++) {
        TM1637_CLK = 0;
        TM1637_DIO = (data & 0x01);
        tm1637_delay();
        TM1637_CLK = 1;
        tm1637_delay();
        data >>= 1;
    }

    // 等待 ACK
    TM1637_CLK = 0;
    TM1637_DIO = 1;
    tm1637_delay();
    TM1637_CLK = 1;
    tm1637_delay();
    // 检查 ACK（可选）
    // if (TM1637_DIO != 0) { /* 处理错误 */ }
    TM1637_CLK = 0;
}

/**
 * @brief 初始化 TM1637 显示器
 *
 * 设置显示开启，并将亮度设置为最高（亮度等级 7）
 */
void tm1637_init(void) {
    tm1637_start();
    tm1637_send_bits(0x88 + 7); // 0x88 = 显示开 + 亮度最低，+7 为最高亮度
    tm1637_stop();
}

/**
 * @brief 在指定位置显示一个数字或符号
 *
 * @param index 数码管位置（0~3）
 * @param data 要显示的段码数据
 */
void tm1637_display_data(unsigned index, unsigned data) {
    tm1637_start();
    tm1637_send_bits(0xC0 + index); // 地址 = 0xC0 + digit位置
    tm1637_send_bits(data);
    tm1637_stop();
}

/**
 * @brief 清除所有数码管显示
 *
 * 将四个数码管全部设置为空白状态
 */
void tm1637_clear(void) {
    for (unsigned char i = 0; i < 4; i++) {
        tm1637_display_data(i, 0x00); // 空白
    }
}

/**
 * @brief 数码管显示缓存数组
 *
 * 存储每个数码管当前要显示的段码值
 */
unsigned char digits_seg[] = {0x00, 0x00, 0x00, 0x00};

/**
 * @brief 将整数转换为四位数码管显示格式
 *
 * 支持前导零控制功能。如果 leading_zero 为 0，
 * 则高位的 0 不显示（空白），直到遇到第一个非零数字。
 *
 * @param num 要显示的数字（0~9999）
 * @param leading_zero 是否显示前导零（0=不显示，非0=显示）
 */
void set_number(unsigned int num, unsigned char leading_zero) {
    if (num > 9999) num = 9999; // 限制最大值为9999

    unsigned char raw_digits[4] = {
        (num / 1000) % 10,
        (num / 100) % 10,
        (num / 10) % 10,
        num % 10
    };

    unsigned char show_flag = leading_zero; // 标记是否已经开始显示数字

    for(unsigned char i = 0; i < 4; i++)
    {
        if (!show_flag && raw_digits[i] == 0 && i < 3)
            digits_seg[i] = 0x00;  // 空白
        else {
            digits_seg[i] = seg_code[raw_digits[i]];
            show_flag = 1; // 一旦显示了非零数字，后续数字都显示
        }
    }
}

/**
 * @brief 刷新数码管显示内容
 *
 * 先设置地址自增模式，然后依次发送四个数码管的段码
 */
void refresh_digitron(void)
{
    // 先设置地址模式
    tm1637_start();
    tm1637_send_bits(0x44); // 地址模式固定
    tm1637_stop();

    for(unsigned char i = 0; i < 4; i++)
    {
        tm1637_display_data(i, digits_seg[i]); // 发送段码
    }
}

/**
 * @brief 延时并刷新显示
 *
 * 在延时期间持续刷新数码管显示，防止闪烁
 * 延时结束后清除显示
 *
 * @param t 延时毫秒数
 */
void delay_ms_refresh(unsigned int t) {
    while (t--) {
        refresh_digitron(); // 刷新显示
        delay_ms(1);
    }
    tm1637_clear(); // 清除显示
}

#endif