/* snt.c - test program */

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
	printf("\n");
    
    for (j = 0; j < 3; j++)
    {

        printf("Now changing the intensities with gamma correction\n");
        for (i = 0; i < SN3218_GAMMA; i++)
        {
            sn3218_set_all_leds(sn3218_gamma[i]);
            msleep(50);
        }
        msleep(50);
        for (i = SN3218_GAMMA-1; i > 0; i--)
        {
            sn3218_set_all_leds(sn3218_gamma[i]);
            msleep(50);
        }
        printf("\n");
        fflush(stdout);
    }
	
	sn3218_close();
	return 0;
}
