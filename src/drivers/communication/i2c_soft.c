#include "config.h"
#if USE_LCD_1602_I2C
#include "i2c_soft.h"

void i2c_init(void) {
    // 初始化I2C引脚
    SDA = 1; // 设置SDA为高电平
    SCL = 1; // 设置SCL为高电平
}

void i2c_start(void) {
    SDA = 1; // 确保SDA为高电平
    SCL = 1; // 确保SCL为高电平
    SDA = 0; // 拉低SDA线，开始I2C通信
    delay_us(I2C_DELAY); // 确保起始条件稳定
    SCL = 0; // 拉低SCL线，准备发送数据
}

void i2c_stop(void) {
    SCL = 0; // 确保SCL为低电平
    SDA = 0; // 拉低SDA线，准备停止条件
    delay_us(I2C_DELAY); // 确保停止条件稳定
    SCL = 1; // 拉高SCL线，完成停止条件
    SDA = 1; // 拉高SDA线，结束I2C通信
}

void i2c_write_byte(unsigned char data) {
    for (unsigned char i = 0; i < 8; i++) {
        SDA = (data & 0x80) ? 1 : 0;
        delay_us(I2C_DELAY); // 确保数据稳定
        SCL = 1; // 拉高SCL线，准备发送数据
        delay_us(I2C_DELAY); // 等待SCL稳定
        SCL = 0; // 拉低SCL线，准备下一个位
        data <<= 1; // 左移数据，准备发送下一个位
    }
    SDA = 1; // 释放SDA线，等待ACK
    SCL = 1; // 拉高SCL线，等待ACK信号
    delay_us(I2C_DELAY); // 等待ACK信号
    SCL = 0; // 拉低SCL线，结束ACK接收
}

unsigned char i2c_read_byte(unsigned char ack) {
    unsigned char data = 0;
    SDA = 1; // 释放SDA线，准备读取数据
    for (int i = 0; i < 8; i++) {
        SCL = 1; // 拉高SCL线，准备读取数据
        delay_us(I2C_DELAY); // 等待数据稳定
        if (SDA) {
            data |= (1 << (7 - i)); // 读取高位
        }
        SCL = 0; // 拉低SCL线，准备下一个位
    }
    if (ack) {
        SDA = 0; // 发送ACK信号
    } else {
        SDA = 1; // 发送NACK信号
    }
    delay_us(I2C_DELAY); // 确保ACK/NACK信号稳定
    SCL = 1; // 拉高SCL线，完成ACK/NACK发送
    delay_us(I2C_DELAY); // 等待ACK/NACK信号稳定
    SCL = 0; // 拉低SCL线，结束读取
    return data;
}

void i2c_write(unsigned char addr, unsigned char data) {
    i2c_start(); // 发送起始条件
    i2c_write_byte(addr); // 发送设备地址
    i2c_write_byte(data); // 发送数据
    i2c_stop(); // 发送停止条件
}

unsigned char i2c_read(unsigned char addr, unsigned char ack) {
    unsigned char data;
    i2c_start(); // 发送起始条件
    i2c_write_byte(addr); // 发送设备地址
    data = i2c_read_byte(ack); // 读取数据
    i2c_stop(); // 发送停止条件
    return data; // 返回读取的数据
}

#endif
