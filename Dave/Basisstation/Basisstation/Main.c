/*
 * Main.c
 *
 *  Created on: Jun 13, 2016
 *      Author: Christof Pfannenmüller
 */
#include "Header_general.h" //including all Header files

// ISR für TDA1  (ERU1 OGU0 IRQ)
extern void ERU1_0_IRQHandler(void) {
	// LED toggle
	led_on(LED2);
}
// ISR für TDA2  (ERU0 OGU0 IRQ)
extern void ERU0_0_IRQHandler(void) {
	// LED toggle
	led_on(LED3);
}
// ISR für TDA3  (ERU0 OGU1 IRQ)
extern void ERU0_1_IRQHandler(void) {
	// LED toggle
	led_on(LED4);

	//Check which Intterrupt has occured
	uint32_t status_tda3 = XMC_GPIO_GetInput(PORT_PP2_TDA_3, PIN_PP2_TDA_3);
	uint32_t status_tda6 = XMC_GPIO_GetInput(PORT_PP2_TDA_6, PIN_PP2_TDA_6);

	if (status_tda3==0||status_tda6!=0) {

	} else if (status_tda6==0||status_tda3!=0) {

	} else if (status_tda6==0||status_tda3==0) {

	}

}
// ISR für TDA4  (ERU1 OGU1 IRQ)
extern void ERU1_1_IRQHandler(void) {
	// LED toggle
	led_on(LED5);
}
// ISR für TDA5  (ERU0 OGU2 IRQ)
extern void ERU0_2_IRQHandler(void) {
	// LED toggle
	led_on(LED6);
}
// ISR für TDA6  (ERU1 OGU0 IRQ)
extern void ERU0_3_IRQHandler(void) {
	// LED toggle
	led_on(LED7);
}

int main(void) {

	init();
	spi_init(spi_master_ch);
//	tda5340_gpio_init(TDA1);
//	tda5340_gpio_init(TDA2);
//	tda5340_gpio_init(TDA3);
//	tda5340_gpio_init(TDA4);
//	tda5340_gpio_init(TDA5);
//	tda5340_gpio_init(TDA6);
	tda5340_gpio_init(TDA_ALL);

	delay(500);
	delay(500);

	led_on(LED_ALL);
	delay(4000000);
	led_off(LED_ALL);
	led_on(LED1);
	delay(4000000);
	led_off(LED_ALL);
	led_on(LED1);

	//set_TDA_status(TDA_ALL, 1);	delay(40000);

	set_TDA_status(TDA1, 1);
	delay(4000);
	set_TDA_status(TDA2, 1);
	delay(4000);
	set_TDA_status(TDA3, 1);
	delay(4000);
	set_TDA_status(TDA4, 1);
	delay(4000);
	set_TDA_status(TDA5, 1);
	delay(4000);
	set_TDA_status(TDA6, 1);
	delay(4000);

	delay(4000);
	tda5340_get_serial_number(TDA6);
	tda5340_get_serial_number(TDA6);
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
