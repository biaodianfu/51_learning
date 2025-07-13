//
// Created by qw on 25-7-12.
//

#ifndef CONFIG_H
#define CONFIG_H

#pragma once

// 系统配置
#define SYSTEM_CLOCK       11059200UL  // 系统时钟频率


// 外设配置
#define UART_BAUDRATE       9600        // 串口波特率

// 功能模块开关
#define LED_FLOW_LIGHT  1
#define USE_DIGITRON        1           // 数码管模块
#define USE_TEMPERATURE_SENSOR 1        // 温度传感器模块

// 引脚配置
#ifdef USE_DIGITRON
    #define DIGITRON_CLK_PIN    P2_0
    #define DIGITRON_DIO_PIN    P2_1
#endif


#endif //CONFIG_H

