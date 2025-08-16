#include "config.h"

#if USE_OLED_12864_I2C
#include "oled_12864_i2c.h"
#include "drivers/communication/i2c_soft.h"
#include "drivers/display/font.h"

void oled_12864_init(void) {
    i2c_init();

    // 基础配置命令
    i2c_start();
    i2c_write_byte(0x78);        // OLED I2C地址 (0x3C << 1)

    // 显示控制设置
    i2c_write_byte(0xAE);        // 关闭显示，进入设置模式
    i2c_write_byte(0xA6);        // 正常显示模式（非反显），0为点亮，1为熄灭

    // 显示区域设置
    i2c_write_byte(0x00);        // 设置列地址低4位为0
    i2c_write_byte(0x10);        // 设置列地址高4位为0
    i2c_write_byte(0x40);        // 设置起始行地址为第0行
    i2c_write_byte(0xB0);        // 设置页地址为第0页

    // 硬件配置
    i2c_write_byte(0xA8);        // 设置多路复用比命令
    i2c_write_byte(0x3F);        // 多路复用比设置为63，对应1/64 duty (64行)
    i2c_write_byte(0xD3);        // 设置显示偏移命令
    i2c_write_byte(0x00);        // 显示偏移设置为0，无垂直偏移

    // 时序控制
    i2c_write_byte(0xD5);        // 设置显示时钟分频因子/振荡器频率命令
    i2c_write_byte(0x80);        // 时钟分频因子设置为1，振荡器频率设置为0
    i2c_write_byte(0xD9);        // 设置预充电周期命令
    i2c_write_byte(0xF1);        // 预充电周期设置为1个时钟周期，放电周期设置为15个时钟周期

    // 电压设置
    i2c_write_byte(0x81);        // 设置对比度控制命令
    i2c_write_byte(0xCF);        // 对比度值设置为207(0-255)
    i2c_write_byte(0xDB);        // 设置VCOMH反压命令
    i2c_write_byte(0x30);        // VCOMH设置为0.83倍VCC

    // 开启显示
    i2c_write_byte(0x8D);        // 设置充电泵命令
    i2c_write_byte(0x14);        // 启用内部充电泵
    i2c_write_byte(0xAF);        // 打开显示

    i2c_stop();
}

void oled_12864_clear(void) {
    i2c_start();
    i2c_write_byte(0x78); // OLED I2C地址，写模式
    i2c_write_byte(0x00); // 控制字节，表示后续是命令
    i2c_write_byte(0x00); // 设置低列地址为0
    i2c_write_byte(0x10); // 设置高列地址为0
    i2c_write_byte(0x40); // 设置起始行

    for (int page = 0; page < 8; page++) {
        i2c_start();
        i2c_write_byte(0x78); // OLED I2C地址，写模式
        i2c_write_byte(0x00); // 控制字节，表示后续是命令
        i2c_write_byte(0xB0 + page); // 设置页地址

        i2c_start();
        i2c_write_byte(0x78); // OLED I2C地址，写模式
        i2c_write_byte(0x40); // 控制字节，表示后续是数据
        for (int col = 0; col < 128; col++) {
            i2c_write_byte(0x00); // 清除数据
        }
    }
    i2c_stop();
}

void oled_12864_display_on(void) {
    i2c_start();
    i2c_write_byte(0x78);
    i2c_write_byte(0X8D); // OLED I2C地址，写模式
    i2c_write_byte(0X14); // 控制字节，表示后续是命令
    i2c_write_byte(0xAF); // 打开显示
    i2c_stop();
}


void oled_12864_display_off(void) {
    i2c_start();
    i2c_write_byte(0x78);
    i2c_write_byte(0X8D);  //SET DCDC命令
    i2c_write_byte(0X10);  //DCDC ON
    i2c_write_byte(0XAE);  //DISPLAY ON
    i2c_stop();
}

void oled_12864_set_cursor(unsigned char page, unsigned char col) {
    i2c_start();
    i2c_write_byte(0x78); // OLED I2C地址，写模式
    i2c_write_byte(0x00); // 控制字节，表示后续是命令
    i2c_write_byte(0xB0 + page); // 设置页地址
    i2c_write_byte(0x10 | ((col+2) >> 4));    // 设置高列地址 (0x10~0x1F)
    i2c_write_byte((col+2) & 0x0F);           // 设置低列地址 (0x00~0x0F)
    i2c_stop();
}

void oled_12864_write_char(unsigned char page, unsigned char col, unsigned char ch) {
    ch = ch - ' '; // 得到偏移后的值
    if (col > 127) {
        col = 0;
        if (page < 7) {
            page++;
        }
    }
    oled_12864_set_cursor(page, col);
    i2c_start();
    i2c_write_byte(0x78); // OLED I2C地址，写模式
    i2c_write_byte(0x40); // 控制字节，表示后续是数据
    for (int i = 0; i < 6; i++) {
        i2c_write_byte(FONT_8X6[ch][i]); // 写入数据
    }
    i2c_stop();
}


void oled_12864_write_string(unsigned char page, unsigned char col, const char *str) {
    unsigned char i = 0;
    while (str[i] != '\0' && page < 8) { // 增加页面边界检查
        oled_12864_write_char(page, col, str[i]);
        col += 6; // 修改为实际字符宽度
        if (col > 122) { // 考虑到实际字符宽度
            col = 2; // 重置为初始列位置
            page++; // 换行
            if (page >= 8) break; // 超出显示范围就退出
        }
        i++;
    }
}

#endif // USE_OLED_12864_I2C
