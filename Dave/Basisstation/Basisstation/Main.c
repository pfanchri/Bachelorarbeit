/*
 * Main.c
 *
 *  Created on: Jun 13, 2016
 *      Author: Christof Pfannenmüller
 */
#include "Header_general.h" //including all Header files




int main(void){

	init();


led_on(LED_ALL);
delay(4000000);
led_off(LED_ALL);
led_on(LED1);
delay(4000000);
led_off(LED_ALL);
led_on(LED1);



set_TDA_status(TDA_ALL,1);

	delay(40000);

	spi_init(spi_master_ch);
	delay(40000);
	tda5340_get_serial_number(TDA6);
	tda5340_get_serial_number(TDA5);
	tda5340_get_serial_number(TDA6);






//function for general test purposes
//general_test();
	while (1) {

	}

}
