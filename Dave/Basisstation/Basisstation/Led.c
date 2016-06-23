/*
 * Led.c
 *
 *  Created on: Jun 22, 2016
 *      Author: Christof Pfannenmüller
 */
#include "Header_general.h" //including all Header files

void led_on(uint8_t led) {
	//set corresonding LED Pin low (active low); Pins were set as Output in init()
	switch (led) {
	case 0:
		XMC_GPIO_SetOutputLow(XMC_GPIO_PORT6, PIN_LED_1);
		XMC_GPIO_SetOutputLow(XMC_GPIO_PORT6, PIN_LED_2);
		XMC_GPIO_SetOutputLow(XMC_GPIO_PORT6, PIN_LED_3);
		XMC_GPIO_SetOutputLow(XMC_GPIO_PORT6, PIN_LED_4);
		XMC_GPIO_SetOutputLow(XMC_GPIO_PORT6, PIN_LED_5);
		XMC_GPIO_SetOutputLow(XMC_GPIO_PORT6, PIN_LED_6);
		XMC_GPIO_SetOutputLow(XMC_GPIO_PORT6, PIN_LED_7);
		break;
	case 1:
		XMC_GPIO_SetOutputLow(XMC_GPIO_PORT6, PIN_LED_1);
		break;
	case 2:
		XMC_GPIO_SetOutputLow(XMC_GPIO_PORT6, PIN_LED_2);
		break;
	case 3:
		XMC_GPIO_SetOutputLow(XMC_GPIO_PORT6, PIN_LED_3);
		break;
	case 4:
		XMC_GPIO_SetOutputLow(XMC_GPIO_PORT6, PIN_LED_4);
		break;
	case 5:
		XMC_GPIO_SetOutputLow(XMC_GPIO_PORT6, PIN_LED_5);
		break;
	case 6:
		XMC_GPIO_SetOutputLow(XMC_GPIO_PORT6, PIN_LED_6);
		break;
	case 7:
		XMC_GPIO_SetOutputLow(XMC_GPIO_PORT6, PIN_LED_7);
		break;
	}
}

void led_off(uint8_t led) {
	//set corresonding LED Pin high (active low); Pins were set as Output in init()
	switch (led) {
		case 0:
			XMC_GPIO_SetOutputHigh(XMC_GPIO_PORT6, PIN_LED_1);
			XMC_GPIO_SetOutputHigh(XMC_GPIO_PORT6, PIN_LED_2);
			XMC_GPIO_SetOutputHigh(XMC_GPIO_PORT6, PIN_LED_3);
			XMC_GPIO_SetOutputHigh(XMC_GPIO_PORT6, PIN_LED_4);
			XMC_GPIO_SetOutputHigh(XMC_GPIO_PORT6, PIN_LED_5);
			XMC_GPIO_SetOutputHigh(XMC_GPIO_PORT6, PIN_LED_6);
			XMC_GPIO_SetOutputHigh(XMC_GPIO_PORT6, PIN_LED_7);
			break;
		case 1:
			XMC_GPIO_SetOutputHigh(XMC_GPIO_PORT6, PIN_LED_1);
			break;
		case 2:
			XMC_GPIO_SetOutputHigh(XMC_GPIO_PORT6, PIN_LED_2);
			break;
		case 3:
			XMC_GPIO_SetOutputHigh(XMC_GPIO_PORT6, PIN_LED_3);
			break;
		case 4:
			XMC_GPIO_SetOutputHigh(XMC_GPIO_PORT6, PIN_LED_4);
			break;
		case 5:
			XMC_GPIO_SetOutputHigh(XMC_GPIO_PORT6, PIN_LED_5);
			break;
		case 6:
			XMC_GPIO_SetOutputHigh(XMC_GPIO_PORT6, PIN_LED_6);
			break;
		case 7:
			XMC_GPIO_SetOutputHigh(XMC_GPIO_PORT6, PIN_LED_7);
			break;
		}
}
