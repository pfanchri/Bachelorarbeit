/*
 * TDA.c
 *
 *  Created on: Jun 22, 2016
 *      Author: Christof Pfannenmüller
 */
#include "Header_general.h" //including all Header files



/**
 * sets TDA(s) in give mode
 * Param TDA: 	TDA_ALL -> all TDAs
 * 				TDA1 -> TDA1 will be set
 * 				TDA2 -> TDA2  ...
 * Param status:0 -> Power down mode
 * 				1 -> Sleep mode
 */
void set_TDA_status(uint8_t TDA, uint8_t status){
if(status==0){
//set P_ON Pin low; Pins were set as Output in init()
if(TDA==0||TDA==1){ XMC_GPIO_SetOutputLow(PORT_P_ON_TDA_1, PIN_P_ON_TDA_1);}
if(TDA==0||TDA==2){ XMC_GPIO_SetOutputLow(PORT_P_ON_TDA_2, PIN_P_ON_TDA_2);}
if(TDA==0||TDA==3){ XMC_GPIO_SetOutputLow(PORT_P_ON_TDA_3, PIN_P_ON_TDA_3);}
if(TDA==0||TDA==4){ XMC_GPIO_SetOutputLow(PORT_P_ON_TDA_4, PIN_P_ON_TDA_4);}
if(TDA==0||TDA==5){ XMC_GPIO_SetOutputLow(PORT_P_ON_TDA_5, PIN_P_ON_TDA_5);}
if(TDA==0||TDA==6){ XMC_GPIO_SetOutputLow(PORT_P_ON_TDA_6, PIN_P_ON_TDA_6);}

}else if(status==1){
//set P_ON Pin high; Pins were set as Output in init()
	if(TDA==0||TDA==1){ XMC_GPIO_SetOutputHigh(PORT_P_ON_TDA_1, PIN_P_ON_TDA_1);}
	if(TDA==0||TDA==2){ XMC_GPIO_SetOutputHigh(PORT_P_ON_TDA_2, PIN_P_ON_TDA_2);}
	if(TDA==0||TDA==3){ XMC_GPIO_SetOutputHigh(PORT_P_ON_TDA_3, PIN_P_ON_TDA_3);}
	if(TDA==0||TDA==4){ XMC_GPIO_SetOutputHigh(PORT_P_ON_TDA_4, PIN_P_ON_TDA_4);}
	if(TDA==0||TDA==5){ XMC_GPIO_SetOutputHigh(PORT_P_ON_TDA_5, PIN_P_ON_TDA_5);}
	if(TDA==0||TDA==6){ XMC_GPIO_SetOutputHigh(PORT_P_ON_TDA_6, PIN_P_ON_TDA_6);}
}

}
