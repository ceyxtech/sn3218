/*  i2c.c
    Derived from: http://www.raspberry-projects.com/pi/programming-in-c/i2c/using-the-i2c-interface
*/

#include <unistd.h>		/* Needed for I2C port */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <fcntl.h>		/* Needed for I2C port */
#include <sys/ioctl.h>		/* Needed for I2C port */
#include <linux/i2c-dev.h>	/* Needed for I2C port */
#include <errno.h>
#include "i2c.h"

#define I2C_DEVICEFILE	"/dev/i2c-1"

int fd_i2c;	/* file descriptor for the I2C device file */

/* i2c_open: opens and locks the I2C device file
 * Returns fd_i2c > 0 (success) or -1 (failure, errno is set).
 */
int i2c_open(void)
{
    /* Open I2C device file */
	errno = 0;
	fd_i2c = open(I2C_DEVICEFILE, O_RDWR);
	if (fd_i2c < 0)
	    return -1;
    
    /* Set exclusive lock on I2C device file to block other processes */
    errno = 0;
    if (flock(fd_i2c, LOCK_EX | LOCK_NB)  == -1)
    {
        close(fd_i2c);
        return -1;
    }
    
	return fd_i2c;
}

/* i2c_close: unlocks and closes the I2C device file
 * Returns 0 (success) or -1 (failure, errno is set).
 */
int i2c_close(void)
{
    int status;
    
	errno = 0;
	if (flock(fd_i2c, LOCK_UN | LOCK_NB) == -1)
	    return -1;
	status = close(fd_i2c);
    fd_i2c = 0; /* Set to invalid value */
    return status;
}

/* i2c_setaddress: sets the I2C addres (device specific)
 * Returns the address set, or 0 (failure).
 * The address should not be zero.
 */
uint8_t i2c_setaddress(uint8_t i2c_address)
{
    if (i2c_address == 0)
        return 0;
	if (ioctl(fd_i2c, I2C_SLAVE, i2c_address) < 0)
		return 0;
	else
		return i2c_address;
}		

/* i2c_write: writes n bytes to the I2C device
 * Returns: n (number of bytes written) or 0 (failure, errno is set)
 */
int i2c_write(uint8_t i2c_address, uint8_t *buffer, int n)
{
	if (fd_i2c < 1)
		return 0;
		
	if (i2c_setaddress(i2c_address))
	{
	    errno = 0;
		if (write(fd_i2c, buffer, n) == n)
			return n;
		else
			return 0;
    }
	else
		return 0;
}
