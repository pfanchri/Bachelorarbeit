/*
 * Init.c
 *
 *  Created on: Jun 16, 2016
 *      Author Christof Pfannenmüller (student06)
 */
#include "Header_general.h" //including all Header files



//init
	void init(void){



		//set P_ON Pins as Output
		XMC_GPIO_SetMode(XMC_GPIO_PORT0, PIN_P_ON_TDA_1, XMC_GPIO_MODE_OUTPUT_PUSH_PULL);//TDA1
		XMC_GPIO_SetMode(XMC_GPIO_PORT1, PIN_P_ON_TDA_2, XMC_GPIO_MODE_OUTPUT_PUSH_PULL);
		XMC_GPIO_SetMode(XMC_GPIO_PORT5, PIN_P_ON_TDA_3, XMC_GPIO_MODE_OUTPUT_PUSH_PULL);
		XMC_GPIO_SetMode(XMC_GPIO_PORT5, PIN_P_ON_TDA_4, XMC_GPIO_MODE_OUTPUT_PUSH_PULL);
		XMC_GPIO_SetMode(XMC_GPIO_PORT3, PIN_P_ON_TDA_5, XMC_GPIO_MODE_OUTPUT_PUSH_PULL);
		XMC_GPIO_SetMode(XMC_GPIO_PORT0, PIN_P_ON_TDA_6, XMC_GPIO_MODE_OUTPUT_PUSH_PULL);//TDA6

	}
