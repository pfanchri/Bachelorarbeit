/*
 * Main.c
 *
 *  Created on: Jun 13, 2016
 *      Author: Christof Pfannenmüller
 */
#include "Header_general.h" //including all Header files




int main(void){

	init();


led_on(0);
delay(4000000);
led_off(0);
led_on(1);
delay(4000000);
led_off(0);
led_on(1);

//function for generall test purposes
general_test();
	while (1) {

	}

}
