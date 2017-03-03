/*  sntrandom.c
	Test program: switches all leds on and off again separately.
 */

#include <ncurses.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>
#include "sn3218.h"

/*	Returns a random number in the range 1..18.
 */
#define FACTOR  (RAND_MAX / SN3218_NLEDS)
int sntrand(void)
{
	return rand() / FACTOR + 1;
}
	
int main(void)
{
	uint8_t led;
	int i, n;
	time_t timer;
	
	if (!sn3218_open())
	{
		fprintf(stderr, "Could not open SN3218 over I2C\n");
		exit(1);
	}

	srand(time(&timer));	/* Seed the random generator */
	n = 1000;
	printf("Random leds: %d\n", n);
	
	for (i = 0; i < n; i++)
	{
		led = sntrand();
		sn3218_set_led(led, 10);
		printf(" %2d", led);
		fflush(stdout);
		msleep(20);
		sn3218_set_led(led, 0);
		msleep(20);
	}

	printf("\n");	
	sn3218_close();
	return 0;
}
