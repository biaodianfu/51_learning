#include "config.h"
#if USE_DIGITRON_4_HC595
#include "digitron_4_hc595.h"

// 共阳段码（dp g f e d c b a）
unsigned char __code segCode[17] = {
	0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,
	0x80,0x90,0x8C,0xBF,0xC6,0xA1,0x86,0xFF,0xBF  // 0~F和短横线
};

// 显示缓存（4 位数码管）
unsigned char  digits_buf[4] = {0xFF, 0xFF, 0xFF, 0xFF};


void LED_OUT(unsigned char X)
{
	unsigned char i;
	for(i = 0; i < 8; i++)
	{
		HC595_DIO = (X & 0x80) ? 1 : 0;
		HC595_SCLK = 0;
		HC595_SCLK = 1;
		X <<= 1;
	}
}

void refresh_digitron(void)
{
	unsigned char i;
	for(i = 0; i < 4; i++)
	{
		LED_OUT(digits_buf[i]);             // 段码保持不变
		LED_OUT(1 << (3 - i));              // 位选从左到右
		HC595_RCLK = 0;
		HC595_RCLK = 1;
	}
}

void set_number(unsigned int num, unsigned char leading_zero)
{
	unsigned char raw[4];

	if (num > 9999) num = 9999;

	raw[0] = (num / 1000) % 10;
	raw[1] = (num / 100) % 10;
	raw[2] = (num / 10) % 10;
	raw[3] = num % 10;

	unsigned char show = leading_zero;
	for(unsigned char i = 0; i < 4; i++)
	{
		if (!show && raw[i] == 0 && i < 3)
			digits_buf[i] = 0xFF;  // 空白
		else {
			show = 1;
			digits_buf[i] = segCode[raw[i]];
		}
	}
}

void delay_ms_refresh(unsigned int ms)
{
	while(ms--)
	{
		refresh_digitron(); // 刷新数码管
		delay_ms(1);
	}
}

#endif // USE_DIGITRON_4_HC595
