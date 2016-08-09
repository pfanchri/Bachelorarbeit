/*
 * ISRs.c
 *
 *  Created on: Jul 7, 2016
 *      Author: student06
 */

#include "Header_general.h" //including all Header files

// ISR für TDA1  (ERU1 OGU0 IRQ)
extern void ERU1_0_IRQHandler(void) {
	query_interruptTDA1_flag = 1;
	COM_send_string("INTERRUPT1\r\n");
}
// ISR für TDA2  (ERU0 OGU0 IRQ)
extern void ERU0_0_IRQHandler(void) {
	query_interruptTDA2_flag = 1;
	COM_send_string("INTERRUPT2\r\n");
}
// ISR für TDA3 + TDA6  (ERU0 OGU1 IRQ)
extern void ERU0_1_IRQHandler(void) {
	//XMC_ERU_ETL_ClearStatusFlag(XMC_ERU0, 1);
	COM_send_string("ISR 3 und 6 \r\n");

//	//Check which Interrupt has occurred
//	uint32_t status_tda3 = XMC_GPIO_GetInput(PORT_PP2_TDA_3, PIN_PP2_TDA_3);
//	uint32_t status_tda6 = XMC_GPIO_GetInput(PORT_PP2_TDA_6, PIN_PP2_TDA_6);
//	if ((!status_tda3) && (status_tda6)) {
//		COM_send_string("INTERRUPT3\r\n");
//		query_interruptTDA3_flag = 1;
//	}
// if ((status_tda6 == 0) && (status_tda3 != 0)) {
//		COM_send_string("INTERRUPT6\r\n");
//		query_interruptTDA6_flag = 1;
//	}
// if ((status_tda6 == 0) && (status_tda3 == 0)) {
//		COM_send_string("INTERRUPT 3&6 \r\n");
//		query_interruptTDA3_flag = 1;
//		query_interruptTDA6_flag = 1;
//	}
	query_interruptTDA3_flag = 1;
	query_interruptTDA6_flag = 1;
}
// ISR für TDA4  (ERU1 OGU1 IRQ)
extern void ERU1_1_IRQHandler(void) {
	query_interruptTDA4_flag = 1;
	COM_send_string("INTERRUPT4\r\n");
}
// ISR für TDA5  (ERU0 OGU2 IRQ)
extern void ERU0_2_IRQHandler(void) {
	COM_send_string("INTERRUPT5\r\n");
	query_interruptTDA5_flag = 1;
}
//// ISR für TDA6  (ERU1 OGU0 IRQ)
//extern void ERU0_3_IRQHandler(void) {
//	// LED toggle
//	led_on(LED7);
//}
