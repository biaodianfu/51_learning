#include "config.h"
#if USE_SOFT_I2C
#include "i2c_soft.h"

// 宏定义：设置引脚方向为输出（需根据平台实现）
//#define SDA_DIR_OUT()   /* 实现平台相关的SDA输出方向设置 */
//#define SCL_DIR_OUT()   /* 实现平台相关的SCL输出方向设置 */

/**
 * @brief 初始化I2C总线
 *
 * 将SDA和SCL引脚初始化为高电平状态，表示空闲状态。
 * 注意：引脚方向的设置应由平台相关代码完成。
 */
void i2c_init(void) {
//    SDA_DIR_OUT();      // 设置SDA为输出
//    SCL_DIR_OUT();      // 设置SCL为输出
    SDA = 1;            // 设置SDA为高电平
    SCL = 1;            // 设置SCL为高电平
}

/**
 * @brief 发送I2C起始信号
 *
 * 在SCL为高电平时拉低SDA，表示开始一次I2C通信。
 */
void i2c_start(void) {
    SDA = 1;            // 确保SDA为高电平
    SCL = 1;            // 确保SCL为高电平
    SDA = 0;            // 拉低SDA线，开始I2C通信
    delay_us(I2C_DELAY); // 确保起始条件稳定
    SCL = 0;            // 拉低SCL线，准备发送数据
}

/**
 * @brief 发送I2C停止信号
 *
 * 在SCL为高电平时拉高SDA，表示结束本次I2C通信。
 */
void i2c_stop(void) {
    SCL = 0;            // 确保SCL为低电平
    SDA = 0;            // 拉低SDA线，准备停止条件
    delay_us(I2C_DELAY); // 确保停止条件稳定
    SCL = 1;            // 拉高SCL线，完成停止条件
    SDA = 1;            // 拉高SDA线，结束I2C通信
}

/**
 * @brief 向I2C总线写入一个字节数据
 *
 * 通过SDA线逐位发送数据，高位先发。发送完成后读取从设备的ACK信号。
 *
 * @param data 要发送的数据字节
 * @return unsigned char 返回ACK状态：1表示收到ACK，0表示未收到ACK
 */
unsigned char i2c_write_byte(unsigned char data) {
    for (unsigned char i = 0; i < 8; i++) {
        SDA = (data & 0x80) ? 1 : 0;
        delay_us(I2C_DELAY); // 确保数据稳定
        SCL = 1;             // 拉高SCL线，准备发送数据
        delay_us(I2C_DELAY); // 等待SCL稳定
        SCL = 0;             // 拉低SCL线，准备下一个位
        data <<= 1;          // 左移数据，准备发送下一个位
    }
    SDA = 1;                 // 释放SDA线，等待ACK
    SCL = 1;                 // 拉高SCL线，等待ACK信号
    delay_us(I2C_DELAY);     // 等待ACK信号
    unsigned char ack = !SDA; // 读取ACK信号（低电平表示ACK）
    SCL = 0;                 // 拉低SCL线，结束ACK接收
    return ack;              // 返回ACK状态
}

/**
 * @brief 从I2C总线读取一个字节数据
 *
 * 通过SDA线逐位读取数据，高位先读。读取完成后根据参数决定是否发送ACK。
 *
 * @param ack 控制是否发送ACK：1表示发送ACK，0表示发送NACK
 * @return unsigned char 读取到的数据字节
 */
unsigned char i2c_read_byte(unsigned char ack) {
    unsigned char data = 0;
    SDA = 1;                 // 释放SDA线，准备读取数据
    for (unsigned char i = 0; i < 8; i++) {
        SCL = 1;             // 拉高SCL线，准备读取数据
        delay_us(I2C_DELAY); // 等待数据稳定
        if (SDA) {
            data |= (1 << (7 - i)); // 读取高位
        }
        SCL = 0;             // 拉低SCL线，准备下一个位
    }
    if (ack) {
        SDA = 0;             // 发送ACK信号
    } else {
        SDA = 1;             // 发送NACK信号
    }
    delay_us(I2C_DELAY);     // 确保ACK/NACK信号稳定
    SCL = 1;                 // 拉高SCL线，完成ACK/NACK发送
    delay_us(I2C_DELAY);     // 等待ACK/NACK信号稳定
    SCL = 0;                 // 拉低SCL线，结束读取
    return data;
}

/**
 * @brief 向指定地址的设备写入一个字节数据
 *
 * 发送起始信号，写入设备地址并检查ACK，再写入数据并检查ACK，最后发送停止信号。
 *
 * @param addr 设备地址（写操作）
 * @param data 要写入的数据
 * @return unsigned char 操作结果：1表示成功，0表示失败
 */
unsigned char i2c_write(unsigned char addr, unsigned char data) {
    i2c_start();                    // 发送起始条件
    if (!i2c_write_byte(addr)) {    // 发送设备地址，并检查ACK
        i2c_stop();                 // 若无ACK，发送停止条件
        return 0;                   // 返回失败
    }
    if (!i2c_write_byte(data)) {    // 发送数据，并检查ACK
        i2c_stop();                 // 若无ACK，发送停止条件
        return 0;                   // 返回失败
    }
    i2c_stop();                     // 发送停止条件
    return 1;                       // 返回成功
}

/**
 * @brief 从指定地址的设备读取一个字节数据
 *
 * 发送起始信号，写入设备地址并检查ACK，然后读取一个字节数据，最后发送停止信号。
 *
 * @param addr 设备地址（读操作）
 * @param ack 控制是否发送ACK：1表示发送ACK，0表示发送NACK
 * @return unsigned char 读取到的数据，若失败则返回0xFF
 */
unsigned char i2c_read(unsigned char addr, unsigned char ack) {
    unsigned char data;
    i2c_start();                    // 发送起始条件
    if (!i2c_write_byte(addr)) {    // 发送设备地址，并检查ACK
        i2c_stop();                 // 若无ACK，发送停止条件
        return 0xFF;                // 返回错误值
    }
    data = i2c_read_byte(ack);      // 读取数据
    i2c_stop();                     // 发送停止条件
    return data;                    // 返回读取的数据
}

#endif // USE_SOFT_I2C
