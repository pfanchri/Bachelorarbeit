/*
 * Main.c
 *
 *  Created on: Jun 13, 2016
 *      Author: Christof Pfannenmüller
 */
#include "Header_general.h" //including all Header files

// ISR für TDA1  (ERU1 OGU0 IRQ)
extern void ERU1_0_IRQHandler(void)
{
	// LED toggle
	led_on(LED2);
}
// ISR für TDA2  (ERU0 OGU0 IRQ)
extern void ERU0_0_IRQHandler(void)
{
	// LED toggle
	led_on(LED3);
}
// ISR für TDA3  (ERU0 OGU1 IRQ)
extern void ERU0_1_IRQHandler(void)
{
	// LED toggle
	led_on(LED4);
}
// ISR für TDA4  (ERU1 OGU1 IRQ)
extern void ERU1_1_IRQHandler(void)
{
	// LED toggle
	led_on(LED5);
}
// ISR für TDA5  (ERU0 OGU2 IRQ)
extern void ERU0_2_IRQHandler(void)
{
	// LED toggle
	led_on(LED6);
}
// ISR für TDA6  (ERU1 OGU0 IRQ)
extern void ERU0_3_IRQHandler(void)
{
	// LED toggle
	led_on(LED7);
}

int main(void) {

	init();
	spi_init(spi_master_ch);
	tda5340_gpio_init(TDA5);


	led_on(LED_ALL);
	delay(4000000);
	led_off(LED_ALL);
	led_on(LED1);
	delay(4000000);
	led_off(LED_ALL);
	led_on(LED1);

	set_TDA_status(TDA5, 1);	delay(40000);

	delay(4000);
	// INterrupt  1&2 funktioniert rest noch nciht
	tda5340_get_serial_number(TDA5);
	tda5340_get_serial_number(TDA5);
	tda5340_get_serial_number(TDA5);

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
