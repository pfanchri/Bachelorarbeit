/*
 * Led.c
 *
 *  Created on: Jun 22, 2016
 *      Author: Christof Pfannenmüller
 */
#include "Header_general.h" //including all Header files



/**
 * aktivates a specific led;
 * Param led: 	0 -> all leds
 * 1 -> first led(top of the bord)
 * ...
 * 7 -> last led
 */
void led_on(uint8_t led) {
	//set corresonding LED Pin low (active low); Pins were set as Output in init()
	switch (led) {
	case 0:
		XMC_GPIO_SetOutputLow(PORT_LED_1, PIN_LED_1);
		XMC_GPIO_SetOutputLow(PORT_LED_2, PIN_LED_2);
		XMC_GPIO_SetOutputLow(PORT_LED_3, PIN_LED_3);
		XMC_GPIO_SetOutputLow(PORT_LED_4, PIN_LED_4);
		XMC_GPIO_SetOutputLow(PORT_LED_5, PIN_LED_5);
		XMC_GPIO_SetOutputLow(PORT_LED_6, PIN_LED_6);
		XMC_GPIO_SetOutputLow(PORT_LED_7, PIN_LED_7);
		break;
	case 1:
		XMC_GPIO_SetOutputLow(PORT_LED_1, PIN_LED_1);
		break;
	case 2:
		XMC_GPIO_SetOutputLow(PORT_LED_2, PIN_LED_2);
		break;
	case 3:
		XMC_GPIO_SetOutputLow(PORT_LED_3, PIN_LED_3);
		break;
	case 4:
		XMC_GPIO_SetOutputLow(PORT_LED_4, PIN_LED_4);
		break;
	case 5:
		XMC_GPIO_SetOutputLow(PORT_LED_5, PIN_LED_5);
		break;
	case 6:
		XMC_GPIO_SetOutputLow(PORT_LED_6, PIN_LED_6);
		break;
	case 7:
		XMC_GPIO_SetOutputLow(PORT_LED_7, PIN_LED_7);
		break;
	}
}




/**
 * deactivates a specific led;
 * Param led: 	0 -> all leds
 * 1 -> first led(top of the bord)
 * ...
 * 7 -> last led
 */
void led_off(uint8_t led) {
	//set corresonding LED Pin high (active low); Pins were set as Output in init()
	switch (led) {
		case 0:
			XMC_GPIO_SetOutputHigh(PORT_LED_1, PIN_LED_1);
			XMC_GPIO_SetOutputHigh(PORT_LED_2, PIN_LED_2);
			XMC_GPIO_SetOutputHigh(PORT_LED_3, PIN_LED_3);
			XMC_GPIO_SetOutputHigh(PORT_LED_4, PIN_LED_4);
			XMC_GPIO_SetOutputHigh(PORT_LED_5, PIN_LED_5);
			XMC_GPIO_SetOutputHigh(PORT_LED_6, PIN_LED_6);
			XMC_GPIO_SetOutputHigh(PORT_LED_7, PIN_LED_7);
			break;
		case 1:
			XMC_GPIO_SetOutputHigh(PORT_LED_1, PIN_LED_1);
			break;
		case 2:
			XMC_GPIO_SetOutputHigh(PORT_LED_2, PIN_LED_2);
			break;
		case 3:
			XMC_GPIO_SetOutputHigh(PORT_LED_3, PIN_LED_3);
			break;
		case 4:
			XMC_GPIO_SetOutputHigh(PORT_LED_4, PIN_LED_4);
			break;
		case 5:
			XMC_GPIO_SetOutputHigh(PORT_LED_5, PIN_LED_5);
			break;
		case 6:
			XMC_GPIO_SetOutputHigh(PORT_LED_6, PIN_LED_6);
			break;
		case 7:
			XMC_GPIO_SetOutputHigh(PORT_LED_7, PIN_LED_7);
			break;
		}
}
