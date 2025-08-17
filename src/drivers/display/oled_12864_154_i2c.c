//#include "config.h"
//#include <stdio.h>  // for snprintf
//#if USE_OLED_12864_154_I2C
//#include "oled_12864_154_i2c.h"
//#include "drivers/communication/i2c_soft.h"
//#include "font.h" // 包含字体数据
//
///**
// * @brief 初始化OLED显示屏
// *
// * 该函数完成OLED的初始化配置，包括复位、设置显示参数、清屏等操作。
// * 主要配置包括：显示时钟分频、多路复用比、显示偏移、起始行地址、
// * 段/列映射、行扫描方向、COM引脚配置、对比度控制、预充电周期、
// * VCOMH设置等。
// *
// * @param 无
// * @return 无
// */
//
//void oled_display_inverse(unsigned char mode) {
//    if (mode==0) {
//        oled_write_byte(0xA6, OLED_CMD); // 正常显示
//    } else {
//        oled_write_byte(0xA7, OLED_CMD); // 反色显示
//    }
//}
//
//void oled_init(void) {
//    // 修正复位时序（文档1第8.8节）
//    OLED_RES = 0;
//    delay_us(5);  // >3µs即可
//    OLED_RES = 1;
//    delay_ms(10);
//
//    i2c_init();
//
//    // ==== 初始化序列 ====
//    oled_write_byte(0xAE, OLED_CMD);  // 关闭显示
//
//    // 命令解锁（文档1表9-1）
//    oled_write_byte(0xFD, OLED_CMD);
//    oled_write_byte(0x12, OLED_CMD);
//
//    // 硬件配置（文档2第4.1节）
//    oled_write_byte(0xD5, OLED_CMD);
//    oled_write_byte(0xA0, OLED_CMD);
//    oled_write_byte(0xA8, OLED_CMD);
//    oled_write_byte(0x3F, OLED_CMD);  // 64行
//    oled_write_byte(0xD3, OLED_CMD);
//    oled_write_byte(0x00, OLED_CMD);  // 无偏移
//    oled_write_byte(0x40, OLED_CMD);  // 起始行=0
//    oled_write_byte(0xA1, OLED_CMD);  // 段重映射
//    oled_write_byte(0xC8, OLED_CMD);  // 扫描方向
//    oled_write_byte(0xDA, OLED_CMD);
//    oled_write_byte(0x12, OLED_CMD);  // COM引脚配置
//
//    // 电压配置（文档2第3.2节）
//    oled_write_byte(0x81, OLED_CMD);
//    oled_write_byte(0xBF, OLED_CMD);  // 对比度
//    oled_write_byte(0xD9, OLED_CMD);
//    oled_write_byte(0x25, OLED_CMD);  // 预充电
//    oled_write_byte(0xDB, OLED_CMD);
//    oled_write_byte(0x34, OLED_CMD);  // VCOMH
//
//    oled_write_byte(0xA4, OLED_CMD);
//    oled_write_byte(0xA6, OLED_CMD);
//
//    // ==== 关键修复点 ====
//    oled_write_byte(0x8D, OLED_CMD);  // 电荷泵使能（文档2第4.2节）
//    oled_write_byte(0x14, OLED_CMD);  // DC/DC ON
//
//    oled_clear();
//    oled_write_byte(0xAF, OLED_CMD);  // 开启显示
//}
///**
// * @brief 清除OLED屏幕显示内容
// *
// * 该函数将OLED屏幕的所有像素点设置为0，实现清屏功能。
// * 通过遍历所有页和列，向每个位置写入0x00数据。
// *
// * @param 无
// * @return 无
// */
//
///**
// * @brief 设置OLED显示光标位置
// *
// * 该函数设置OLED的显示光标位置，用于指定后续显示内容的位置。
// * 参数col表示列地址(0-127)，page表示页地址(0-7)。
// *
// * @param col 列地址，取值范围0-127
// * @param page 页地址，取值范围0-7
// * @return 无
// */
//void oled_set_cursor(unsigned char col, unsigned char page) {
//    if (col >= 128 || page >= 8) return;
//    oled_write_byte(0xB0 | page, OLED_CMD); // 设置页地址
//    // 设置列地址
//    oled_write_byte(0x00 | (col & 0x0F), OLED_CMD);  // 列地址低4位
//    oled_write_byte(0x10 | ((col >> 4) & 0x0F), OLED_CMD); // 列地址高4位
//}
//
//// 开启OLED显示（添加电荷泵控制）
//void oled_display_on(void) {
//    oled_write_byte(0x8D, OLED_CMD);  // SET DCDC命令（供应商命令）
//    oled_write_byte(0x14, OLED_CMD);  // DCDC ON（关键添加）
//    oled_write_byte(0xAF, OLED_CMD);   // 开启显示
//}
//
//// 关闭OLED显示（添加电荷泵控制）
//void oled_display_off(void) {
//    oled_write_byte(0x8D, OLED_CMD);  // SET DCDC命令（供应商命令）
//    oled_write_byte(0x10, OLED_CMD);  // DCDC OFF（关键添加）
//    oled_write_byte(0xAE, OLED_CMD);   // 关闭显示
//}
//
///**
// * @brief 向OLED写入一个字节数据
// *
// * 该函数通过I2C接口向OLED发送一个字节的数据或命令。
// * 根据mode参数决定是发送数据还是命令。
// *
// * @param dat 要发送的数据字节
// * @param mode 发送模式，OLED_CMD表示命令模式，OLED_DATA表示数据模式
// * @return 无
// */
//void oled_write_byte(unsigned char dat, unsigned char mode) {
//    i2c_start();
//
//    // 发送设备地址
//    if (i2c_write_byte(OLED_I2C_ADDR) != 0) {
//        i2c_stop();
//        return; // 地址无响应
//    }
//
//    // 发送控制字节
//    if (mode) {
//        if (i2c_write_byte(0x40) != 0) { // 数据模式
//            i2c_stop();
//            return;
//        }
//    } else {
//        if (i2c_write_byte(0x00) != 0) { // 命令模式
//            i2c_stop();
//            return;
//        }
//    }
//
//    // 发送数据字节
//    if (i2c_write_byte(dat) != 0) {
//        i2c_stop();
//        return;
//    }
//
//    i2c_stop();
//}
//
///**
// * @brief 在指定位置显示一个字符
// *
// * 该函数在OLED的指定位置显示一个字符。
// * 字符通过查找字体表获取点阵数据进行显示。
// *
// * @param col 列地址，取值范围0-127
// * @param page 页地址，取值范围0-7
// * @param ch 要显示的字符
// * @return 无
// */
//void oled_show_char(unsigned char col, unsigned char page, char ch) {
//    if (page >= 8) return; // 防止越界
//
//    // 检查列边界（字体宽度6像素）
//    if (col > 122) {
//        col = 0;
//        if (++page >= 8) return; // 增加页边界检查
//    }
//
//    unsigned char c = ch - ' ';
//    oled_set_cursor(col, page);
//
//    for (unsigned char i = 0; i < 6; i++) {
//        oled_write_byte(FONT_8X6[c][i], OLED_DATA);
//    }
//}
//
///**
// * @brief 在指定位置显示字符串
// *
// * 该函数在OLED的指定位置显示一个字符串。
// * 通过逐个显示字符实现字符串显示功能。
// *
// * @param col 列地址，取值范围0-127
// * @param page 页地址，取值范围0-7
// * @param str 要显示的字符串指针
// * @return 无
// */
//void oled_show_string(unsigned char col, unsigned char page, const char *str) {
//    unsigned char i = 0;
//    while (str[i] != '\0' && page < 8) {
//        // 修正参数顺序：col, page
//        oled_show_char(col, page, str[i]);
//
//        col += 6;
//        if (col > 122) {
//            col = 0;
//            if (++page >= 8) break;
//        }
//        i++;
//    }
//}
//
//#endif // USE_OLED_12864_154_I2C