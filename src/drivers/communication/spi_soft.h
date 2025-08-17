#ifndef SPI_SOFT_H
#define SPI_SOFT_H

/* SPI模式枚举 */
typedef enum {
    SPI_MODE0,  // CPOL=0, CPHA=0 // 时钟空闲时为低电平，数据在时钟上升沿采样
    SPI_MODE1,  // CPOL=0, CPHA=1 // 时钟空闲时为低电平，数据在时钟下降沿采样
    SPI_MODE2,  // CPOL=1, CPHA=0 // 时钟空闲时为高电平，数据在时钟下降沿采样
    SPI_MODE3   // CPOL=1, CPHA=1 // 时钟空闲时为高电平，数据在时钟上升沿采样
} SPI_MODE;

/* SPI配置结构 */
typedef struct {
    SPI_MODE mode;
    unsigned int clock_div;  // 时钟分频系数
} SPI_CONFIG;

/* API函数声明 */
void spi_init(SPI_CONFIG config);
void spi_set_mode(SPI_MODE new_mode);
void spi_write_byte(unsigned char data);
unsigned char spi_read_byte(void);
void spi_write_data(unsigned char *data, unsigned int len);
void spi_read_data(unsigned char *buf, unsigned int len);

/* 设备管理函数 */
unsigned char spi_register_device(unsigned char device_id, unsigned char cs_delay);
void spi_start_device(unsigned char device_id);
void spi_end_device(unsigned char device_id);
unsigned char spi_get_current_device(void);

#endif //SPI_SOFT_H
