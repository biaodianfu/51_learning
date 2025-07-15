//
// Created by qw on 25-7-15.
//

#ifndef INC_51_LEARNING_LED_1BIT_5050_CONFIG_H
#define INC_51_LEARNING_LED_1BIT_5050_CONFIG_H
#include "STC89C5xRC.h"

// SDCC兼容的LED控制引脚定义
//__sbit __at(0xA0) LED_R;  // P2.0 -> 位地址0xA0 (红色)
//__sbit __at(0xA1) LED_B;  // P2.1 -> 位地址0xA1 (蓝色)
//__sbit __at(0xA2) LED_G;  // P2.2 -> 位地址0xA2 (绿色)
//
// 使用P2端口的位定义LED颜色
#define LED_R P20
#define LED_B P21
#define LED_G P22

#endif //INC_51_LEARNING_LED_1BIT_5050_CONFIG_H
