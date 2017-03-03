/* i2c.h */

/*
#include <errno.h>

#define I2C_OK      1
#define I2C_ERROR   0
*/
extern int fd_i2c;

int i2c_open(void);
int i2c_close(void);
uint8_t i2c_setaddress(uint8_t i2c_address);
int i2c_write(uint8_t i2c_address, uint8_t *buffer, int n);

