#ifndef CONFIG_H
#define CONFIG_H

# include "common.h"
# include "STC89C5xRC.h"
# include "utils/delay.h"

// 功能模块开关
#define USE_LED_8BIT 0
#define USE_LED_1BIT_5050 0
#define USE_LED_MATRIX_8x8_MAX7219 0
#define USE_LED_MATRIX_8x8_MAX7219x4 0 // 使用HC595驱动的8x8 LED矩阵
#define USE_LED_MATRIX_8x8_HC595 0
#define USE_LED_MATRIX_8x8_HT16K33 0
#define USE_DIGITRON_1 0
#define USE_DIGITRON_4 0
#define USE_DIGITRON_4_HC595 0
#define USE_DIGITRON_4_HC595x4 0
#define USE_DIGITRON_4_TM1637 0
#define USE_DIGITRON_4_uart 0
#define USE_DIGITRON_8_HC164 0
#define USE_DIGITRON_8_MAX7219 0
#define USE_UART 0
#define USE_LCD_1602 0
#define USE_LCD_1602_I2C 1 // 使用I2C接口的LCD1602
#define USE_SOFT_I2C 1 // 使用软件I2C

// LED效果配置
#if USE_LED_8BIT
#define LED_PORT P2
#define FLOW_DELAY_MS      100     // 流水灯切换间隔
#define BLINK_DELAY_MS     500     // 闪烁间隔
#endif

// LED 1位5050配置
#if USE_LED_1BIT_5050
#define LED_R P20
#define LED_B P21
#define LED_G P22
#endif

#if USE_LED_MATRIX_8x8_MAX7219
#define MAX7219_CLK P20 // 时钟引脚
#define MAX7219_CS P21 // 片选引脚
#define MAX7219_DIN P22 // 数据输入引脚
#endif // USE_LED_MATRIX_8x8_MAX7219

#if USE_DIGITRON_1
// 数码管1位数字显示的引脚定义
// 1位共阳数码管的段码定义
#define DIG_1 P1
//#define DIG_A P10
//#define DIG_B P11
//#define DIG_C P12
//#define DIG_D P13
//#define DIG_E P14
//#define DIG_F P15
//#define DIG_G P16
#define DIG_DP P17 // 小数点引脚
#endif // USE_DIGITRON_1

#if USE_DIGITRON_4
#define DIG_DIG P2
#define DIG_SEG P1
//#define DIG_D1 P20
//#define DIG_D2 P21
//#define DIG_D3 P22
//#define DIG_D4 P23
//#define DIG_A P10
//#define DIG_B P11
//#define DIG_C P12
//#define DIG_D P13
//#define DIG_E P14
//#define DIG_F P15
//#define DIG_G P16
#define DIG_DP P17 // 小数点引脚
#endif // USE_DIGITRON_4

#if USE_DIGITRON_4_HC595
#define HC595_DIO P20 // 串行数据输入
#define HC595_RCLK P21 // 时钟脉冲信号——上升沿有效
#define HC595_SCLK P22 // 打入信号————上升沿有效
#endif // USE_DIGITRON_4_HC595

#if USE_DIGITRON_4_HC595x4
#define HC595_SDI P20 // 串行数据输入
#define HC595_SCLK P21 // 移位时钟
#define HC595_LOAD P22 // 锁存时钟
#endif // USE_DIGITRON_4_HC595x4

#if USE_DIGITRON_4_TM1637
#define TM1637_CLK P20 // 时钟引脚
#define TM1637_DIO P21 // 数据引脚
#endif // USE_DIGITRON_4_TM1637

#if USE_DIGITRON_8_HC164
#define AB P20 // 串行数据输入（通常合并为一个数据输入）
#define CP P21 // 时钟脉冲信号——上升沿有效
#endif // USE_DIGITRON_8_HC164

#if USE_DIGITRON_8_MAX7219
#define MAX7219_CS P20 // 片选引脚
#define MAX7219_CLK P21 // 时钟引脚
#define MAX7219_DIN P22 // 数据输入引脚
#endif // USE_DIGITRON_8_MAX7219

#if USE_LED_MATRIX_8x8_HC595
#define HC595_DI P20 // 串行数据输入
#define HC595_CLK P21 // 移位时钟
#define HC595_LAT P22 // 锁存时钟
#endif // USE_LED_MATRIX_8x8_HC595


#if USE_LED_MATRIX_8x8_MAX7219x4
#define MAX7219_CLK P20 // 时钟引脚
#define MAX7219_CS P21 // 片选引脚
#define MAX7219_DIN P22 // 数据输入引脚
#endif // USE_LED_MATRIX_8x8_MAX7219x4

#if USE_LED_MATRIX_8x8_HT16K33
#define SCL P20 // 时钟引脚
#define SDA P21 // 数据输入引脚
#define HT16K33_ADDR 0x70     // 芯片I²C地址
#define WRITE_ADDR   (HT16K33_ADDR << 1)  // 写地址：0xE0
#endif // USE_LED_MATRIX_8x8_HT16K33

#if USE_UART
#define UART_BAUD 9600 // 波特率设置
#endif // USE_UART

#if USE_LCD_1602
#define LCD_RS P20 // RS引脚
#define LCD_RW P21 // RW引脚
#define LCD_EN P22 // EN引脚
#define LCD_DATA P0 // 数据引脚（8位数据总线）
#endif // USE_LCD_1602

#if USE_LCD_1602_I2C
#define I2C_ADDR 0x4E // I2C地址
#endif // USE_LCD_1602_I2C

#if USE_SOFT_I2C
#define SDA P20 // I2C数据引脚
#define SCL P21 // I2C时钟引脚
#define I2C_DELAY 5 // I2C延时，单位为毫秒
#endif // USE_SOFT_I2C


#endif //CONFIG_H

