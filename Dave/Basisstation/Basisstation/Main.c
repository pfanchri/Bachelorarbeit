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



	uint16_t spi_array_tx[10] = { 0 };
	uint16_t spi_array_rx[10] = { 0 };
	led_on(2);
	spi_init(spi_master_ch);
	spi_transfer(spi_master_ch, 0, spi_array_tx, spi_array_rx, 3);




	for (int var = 0; var < 10; ++var) {
		if (spi_array_rx[var]  !=  0) {
			led_on(5);
		}
	}

	while (1) {

	}

}
