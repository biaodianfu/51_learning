#include "config.h"
#include "drivers/display/lcd_12864_parallel.h"
void main() {
    // ��ʼ��LCD
    lcd_init();

    // ����
    lcd_clear();

    while (1) {
        // ��ѭ�������ֳ�������
        lcd_set_position(0, 0);
        lcd_print("Hello, World!");
        delay_ms(1000); // ��ʱ1��
        lcd_set_position(1, 0);
        lcd_print("51 Learning");
        delay_ms(1000); // ��ʱ1��
        lcd_set_position(2, 0);
        lcd_print("��ã����磡"); // ��Ҫ�������ļ�ת��ΪGB2312����
        delay_ms(1000); // ��ʱ1��
    }
}