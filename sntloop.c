/*  sntloop.c
	Test program: switches all leds on and off again separately.
 */

#include <ncurses.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "sn3218.h"

int main(void)
{
	uint8_t i, j;
	
	if (!sn3218_open())
	{
		fprintf(stderr, "Could not open SN3218 over I2C\n");
		exit(1);
	}
	
	printf("Switching on  %d LED's:  ", SN3218_NLEDS);
	for (i = 1; i <= SN3218_NLEDS; i++)
	{
		printf("%d ", i);
		fflush(stdout);
		sn3218_set_led(i, 1);
		msleep(100);
	}
	msleep(100);
	
	
	printf("\nSwitching off %d LED's:  ", SN3218_NLEDS);
	for (i = 1; i <= SN3218_NLEDS; i++)
	{
		printf("%d ", i);
		fflush(stdout);
		sn3218_set_led(i, 0);
		msleep(100);
	}
	printf("\n");
	
	sn3218_close();
	return 0;
}
