/* sntest.c - test program */

#include <ncurses.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "sn3218.h"

int main(void)
{
	uint8_t i, j, mode, ledno;
	int retval;
	
	retval = sn3218_open();
	printf("sn3218_open: %d\n", retval);
	if (retval == SN3218_ERROR)
		exit(1);
	
	printf("set_mode shutdown: %d\n", sn3218_set_mode(SN3218_SHUTDOWN));
	printf("set_mode normal  : %d\n", sn3218_set_mode(SN3218_NORMAL));

	mode = SN3218_LCRON;
	retval = sn3218_set_all_lcrs(mode);
	printf("sn3218_set_all_lcrs(%d) = %d\n", mode, retval);
	
	mode = 5;
	retval = sn3218_set_all_leds(mode);
	printf("sn3218_set_all_leds(%d) = %d\n", mode, retval);
	msleep(1000);
	
	retval = sn3218_update_registers();
	printf("sn3218_update_registers() = %d\n", retval);
	
	retval = sn3218_reset_registers();
	printf("sn3218_reset_registers() = %d\n", retval);
	
	sn3218_set_mode(SN3218_NORMAL);
	sn3218_set_all_lcrs(SN3218_LCRON);
	ledno = 18;
	mode = 100;
	retval = sn3218_set_led(ledno, mode);
	printf("sn3218_set_led(%d, %d) = %d\n", ledno, mode, retval);
	msleep(1000);
	
	printf("Testing blocks\n");
	mode = LED6 | LED5 | LED4 | LED3 | LED2 | LED1;
	printf("%d\n", mode);
	sn3218_set_all_leds(25);
    msleep(1000);
	sn3218_set_all_lcrs(0x00);
	msleep(1000);
	sn3218_set_lcr(1, mode);
	msleep(1000);
	sn3218_set_lcr(1, 0x00);
	sn3218_set_lcr(2, mode);
	msleep(1000);
	sn3218_set_lcr(2, 0x00);
	sn3218_set_lcr(3, mode);
	msleep(1000);
	
	retval = sn3218_close();	
	printf("sn3218_close: %d\n", retval);

	return 0;
}
