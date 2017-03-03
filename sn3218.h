/* sn3218.h */

#include <unistd.h>     /* For usleep() */
#include <stdint.h>

#ifndef ON
#define ON	1
#define OFF	0
#endif

#define SN3218_OK       1
#define SN3218_ERROR    0

#define SN3218_I2C_ADDRESS  0x54    /* Fixed I2C address SN3218 */
#define SN3218_NREGS	    0x18	/* 24 dec. */

#define SN3218_REG_MODE		0x00
#define SN3218_REG_PWM0		0x01
#define SN3218_REG_LCR0		0x13
#define SN3218_REG_LCR1		0x14
#define SN3218_REG_LCR2		0x15
#define SN3218_REG_UPDATE	0x16
#define SN3218_REG_RESET	0x17


#define SN3218_SHUTDOWN	0x00
#define SN3218_NORMAL	0x01
#define SN3218_LCRON	0x3F    /* lower 6 bits high */
#define SN3218_LCROFF	0x00    /* lower 6 bits low */
#define SN3218_NLEDS	0x12	/* 0x12 == 18 dec */
#define SN3218_GAMMA	32		/* number of gamma intensities */

#define LED1	0x01
#define LED2	0x02
#define LED3	0x04
#define LED4	0x08
#define LED5	0x10
#define LED6	0x20

extern uint8_t sn3218_gamma[SN3218_GAMMA];

#define msleep(msec)	usleep(1000*(msec))

/* sn3218.c */
int sn3218_open(void);
int sn3218_close(void);
uint8_t sn3218_set_led(uint8_t ledno, uint8_t intensity);
uint8_t sn3218_set_all_leds(uint8_t intensity);
