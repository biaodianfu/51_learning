#ifndef I2C_SOFT_H
#define I2C_SOFT_H
void i2c_init(void);
void i2c_start(void);
void i2c_stop(void);
void i2c_write_byte(unsigned char data);
unsigned char i2c_read_byte(unsigned char ack);
void i2c_write(unsigned char addr, unsigned char data);
unsigned char i2c_read(unsigned char addr, unsigned char ack);

#endif //I2C_SOFT_H
