/* sn3218.c */

#include <unistd.h>				/* Needed for I2C port */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <fcntl.h>				/* Needed for I2C port */
#include <sys/ioctl.h>			/* Needed for I2C port */
#include <linux/i2c-dev.h>		/* Needed for I2C port */
#include "i2c.h"
#include "sn3218.h"

uint8_t sn3218_gamma[SN3218_GAMMA] = 
{ 
      0,   1,   2,   4,   6,  10,  13,  18,
     22,  28,  33,  39,  46,  53,  61,  69,
     78,  86,  96, 106, 116, 126, 138, 149, 
     161, 173, 186, 199, 212, 226, 240, 255 
};

static uint8_t buffer[SN3218_NREGS], n;

/* Prototypes for static functions */
static uint8_t sn3218_update_registers(void);
static uint8_t sn3218_reset_registers(void);
static uint8_t sn3218_set_mode(uint8_t mode);
static uint8_t sn3218_set_lcr(uint8_t blkno, uint8_t mode);
static uint8_t sn3218_set_all_lcrs(uint8_t mode);


/* Public functions */

/* sn3218_open: open the I2C channel and set things up to start
 * normal operations on the SN3218.
 */
int sn3218_open(void)
{
    int status;
    
	status = i2c_open();
	if (status == -1)
		return SN3218_ERROR;
        
	if (sn3218_set_mode(SN3218_NORMAL) == SN3218_ERROR)
		return SN3218_ERROR;
        
	sn3218_set_all_lcrs(SN3218_LCRON);
	return SN3218_OK;
}

/* sn3218_close: shutdown the SN3218 and close the I2C channel.
 */
int sn3218_close(void)
{
	sn3218_set_mode(SN3218_SHUTDOWN);
    
    if (i2c_close())
        return SN3218_ERROR;
    else
        return SN3218_OK;
}

/* sn3218_set_led: user function to set a single LED to the indicated
 * intensity level (0-255)
 */
uint8_t sn3218_set_led(uint8_t ledno, uint8_t intensity)
{
	if (ledno < 1 || ledno > 18)
		return SN3218_ERROR;
	buffer[0] = ledno;
	buffer[1] = intensity;
	n = 2;
	if (i2c_write(SN3218_I2C_ADDRESS, buffer, n) == n)
	{
        sn3218_update_registers();
        return SN3218_OK;
    }
    else
        return SN3218_ERROR;
}	

/* set_all_leds: set all PWM's to the same intensity level
 */
uint8_t sn3218_set_all_leds(uint8_t intensity)
{
	buffer[0] = SN3218_REG_PWM0;
	memset(&buffer[1], intensity, SN3218_NLEDS);
	n = 1 + SN3218_NLEDS;
	if (i2c_write(SN3218_I2C_ADDRESS, buffer, n) == n)
	{
        sn3218_update_registers();
        return SN3218_OK;
    }
    else
        return SN3218_ERROR;
}

/* Private (static) functions */

/* sn3218_update_registers: updates the registers after write
 */
static uint8_t sn3218_update_registers(void)
{
	buffer[0] = SN3218_REG_UPDATE;
	buffer[1] = 0xFF; /* any value will do here */
	n = 2;
	if (i2c_write(SN3218_I2C_ADDRESS, buffer, n) == n)
	    return SN3218_OK;
    else
        return SN3218_ERROR;
}

/* sn3218_reset_registers: resets the SN3218 registers
 */
static uint8_t sn3218_reset_registers(void)
{
	buffer[0] = SN3218_REG_RESET;
	buffer[1] = 0xFF; /* any value will do here */
	n = 2;
	if (i2c_write(SN3218_I2C_ADDRESS, buffer, n) == n)
	    return SN3218_OK;
    else
        return SN3218_ERROR;
}


/* sn3218_set_mode: set SN3218_NORMAL or SN3218_SHUTDOWN mode
 */
static uint8_t sn3218_set_mode(uint8_t mode)
{
	if (mode != SN3218_SHUTDOWN && mode != SN3218_NORMAL)
		return SN3218_ERROR;
		
	buffer[0] = SN3218_REG_MODE;
	buffer[1] = mode;
	n = 2;
	if (i2c_write(SN3218_I2C_ADDRESS, buffer, n) == n)
	    return SN3218_OK;
    else
        return SN3218_ERROR;	
}

/* sn3218_set_lcr: sets a single block of LED's.
 * Only the lower 6 bits per LCR are relevant, so effective range 
 * is 0x00-0x3F (but 0x40-0xFF are also acceptable values).
 */
static uint8_t sn3218_set_lcr(uint8_t blkno, uint8_t mode)
{
    if (blkno < 1 || blkno > 3)
        return SN3218_ERROR;
    if (mode != SN3218_LCRON && mode != SN3218_LCROFF)
        return SN3218_ERROR;
        
    buffer[0] = SN3218_REG_LCR0 + blkno - 1;
	buffer[1] = mode;
	n = 2;
	if (i2c_write(SN3218_I2C_ADDRESS, buffer, n) == n)
	{
		sn3218_update_registers();
		return SN3218_OK;
	}
	else
		return SN3218_ERROR;
}

/* sn3218_setall_lcrs: set all LCR's to 'value'
 * Only the lower 6 bits per LCR are relevant, so effective range 
 * is 0x00-0x3F (but 0x40-0xFF are also acceptable values).
 */
static uint8_t sn3218_set_all_lcrs(uint8_t mode)
{
    if (mode != SN3218_LCRON && mode != SN3218_LCROFF)
        return SN3218_ERROR;

	buffer[0] = SN3218_REG_LCR0;
	buffer[1] = buffer[2] = buffer[3] = mode;
	n = 4;
	if (i2c_write(SN3218_I2C_ADDRESS, buffer, n) == n)
	{
		sn3218_update_registers();
		return SN3218_OK;
	}
	else
		return SN3218_ERROR;
}
