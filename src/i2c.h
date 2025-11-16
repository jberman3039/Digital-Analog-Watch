#define SCL_PIN 0 // PB0
#define SDA_PIN 1 // PB1

void init_i2c();
void i2c_start();
void i2c_stop();
void i2c_tx(unsigned char data_tx);
unsigned char i2c_rx();