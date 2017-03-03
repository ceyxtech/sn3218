/* sntall.c - test program */

#include <ncurses.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "sn3218.h"

int main(void)
{
	uint8_t i;
	
	if (!sn3218_open())
	{
		fprintf(stderr, "Could not open SN3218 over I2C\n");
		exit(1);
	}
	
	for (i = 0; i < 5; i++)
	{
		printf("Switching on 18 LEDs at once ... ");
		fflush(stdout);
        sn3218_set_all_leds(1);
        msleep(200);
		printf("and off again\n");
        fflush(stdout);
        sn3218_set_all_leds(0);
        msleep(200);
	}
	
	sn3218_close();
	return 0;
}
