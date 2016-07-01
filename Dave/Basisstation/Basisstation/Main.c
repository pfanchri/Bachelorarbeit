/*
 * Main.c
 *
 *  Created on: Jun 13, 2016
 *      Author: Christof Pfannenmüller
 */
#include "Header_general.h" //including all Header files

// ISR für ERU1 OGU0 IRQ
extern void ERU0_0_IRQHandler(void)
{
	// LED toggle
	led_on(LED7);
}

int main(void) {

	init();
	tda5340_gpio_init(TDA1);
	led_on(LED_ALL);
	delay(4000000);
	led_off(LED_ALL);
	led_on(LED1);
	delay(4000000);
	led_off(LED_ALL);
	led_on(LED1);

	set_TDA_status(TDA_ALL, 1);
	spi_init(spi_master_ch);
	delay(4000);

	tda5340_get_serial_number(TDA6);
	tda5340_get_serial_number(TDA5);
	tda5340_get_serial_number(TDA6);

//	set_TDA_status(TDA_ALL, 0);
//	set_TDA_status(TDA_ALL, 1);
//
//	set_TDA_status(TDA_ALL, 0);
//	set_TDA_status(TDA_ALL, 1);
//	set_TDA_status(TDA_ALL, 0);
//	set_TDA_status(TDA_ALL, 1);

//function for general test purposes
//general_test();
	while (1) {

	}

}
