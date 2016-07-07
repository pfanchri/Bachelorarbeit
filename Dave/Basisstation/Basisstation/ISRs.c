/*
 * ISRs.c
 *
 *  Created on: Jul 7, 2016
 *      Author: student06
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
// ISR für TDA3 + TDA6  (ERU0 OGU1 IRQ)
extern void ERU0_1_IRQHandler(void) {
	// LED toggle

	//Check which Intterrupt has occured
	uint32_t status_tda3 = XMC_GPIO_GetInput(PORT_PP2_TDA_3, PIN_PP2_TDA_3);
	uint32_t status_tda6 = XMC_GPIO_GetInput(PORT_PP2_TDA_6, PIN_PP2_TDA_6);
	if (status_tda3 == 0 && status_tda6 != 0) {
		led_on(LED4);
	} else if (status_tda6 == 0 && status_tda3 != 0) {
		led_on(LED7);
	} else if (status_tda6 == 0 && status_tda3 == 0) {
		led_off(LED1);
//		led_on(LED4);
//		led_on(LED7);
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
//// ISR für TDA6  (ERU1 OGU0 IRQ)
//extern void ERU0_3_IRQHandler(void) {
//	// LED toggle
//	led_on(LED7);
//}
