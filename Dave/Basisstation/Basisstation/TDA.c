/*
 * TDA.c
 *
 *  Created on: Jun 22, 2016
 *      Author: Christof Pfannenmüller
 */


void set_TDA_status(uint8_t TDA, uint8_t status){
XMC_GPIO_SetMode(XMC_GPIO_PORT1, led, XMC_GPIO_MODE_OUTPUT_PUSH_PULL);
if(status==0){
//set P_ON Pin low
if(TDA==1) XMC_GPIO_SetOutputLow(XMC_GPIO_PORT1, led);
if(TDA==1) XMC_GPIO_SetOutputLow(XMC_GPIO_PORT1, led);

}else if(status==1){
//set P_ON Pin high

}

}
