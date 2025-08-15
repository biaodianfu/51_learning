#ifndef I2C_SOFT_H
#define I2C_SOFT_H
/**
 * @brief 初始化I2C总线
 *
 * 配置I2C总线所需的GPIO引脚为开漏输出模式，
 * 并将SDA和SCL引脚初始化为高电平状态
 */
void i2c_init(void);

/**
 * @brief 发送I2C起始信号
 *
 * 在I2C总线上发送起始条件：SDA从高电平变为低电平，
 * 此时SCL保持高电平，用于标识一次数据传输的开始
 */
void i2c_start(void);

/**
 * @brief 发送I2C停止信号
 *
 * 在I2C总线上发送停止条件：SDA从低电平变为高电平，
 * 此时SCL保持高电平，用于标识一次数据传输的结束
 */
void i2c_stop(void);

/**
 * @brief 向I2C总线写入一个字节数据
 *
 * 通过I2C总线发送一个字节数据，从最高位开始逐位发送，
 * 并等待从设备的应答信号
 *
 * @param data 要写入的字节数据
 * @return unsigned char 从设备的应答信号，0表示应答成功，1表示无应答
 */
unsigned char i2c_write_byte(unsigned char data);

/**
 * @brief 从I2C总线读取一个字节数据
 *
 * 从I2C总线接收一个字节数据，从最高位开始逐位接收，
 * 根据ack参数决定是否发送应答信号
 *
 * @param ack 应答控制，0表示发送应答，1表示发送非应答
 * @return unsigned char 读取到的字节数据
 */
unsigned char i2c_read_byte(unsigned char ack);

/**
 * @brief 向指定地址的I2C设备写入数据
 *
 * 向指定地址的I2C设备发送一个字节数据，包含完整的
 * 起始信号、设备地址发送、数据写入和停止信号流程
 *
 * @param addr I2C设备地址
 * @param data 要写入的数据
 * @return unsigned char 操作结果，0表示成功，1表示失败
 */
unsigned char i2c_write(unsigned char addr, unsigned char data);

/**
 * @brief 从指定地址的I2C设备读取数据
 *
 * 从指定地址的I2C设备读取一个字节数据，包含完整的
 * 起始信号、设备地址发送、数据读取和停止信号流程
 *
 * @param addr I2C设备地址
 * @param ack 应答控制，0表示发送应答，1表示发送非应答
 * @return unsigned char 读取到的数据
 */
unsigned char i2c_read(unsigned char addr, unsigned char ack);

#endif //I2C_SOFT_H
