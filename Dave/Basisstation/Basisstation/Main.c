/*
 * Main.c
 *
 *  Created on: Jun 13, 2016
 *      Author: Christof Pfannenmüller
 */
#include "Header_general.h" //including all Header files


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

void led_on(uint8_t led){

}

void led_off(uint8_t led){

}


int main(void) {
	uint16_t spi_array_tx[10] = { 0 };
	uint16_t spi_array_rx[10] = { 0 };

	spi_init(spi_master_ch);
	spi_transfer(spi_master_ch, 0, spi_array_tx, spi_array_rx, 3);










	void init(void);

	while (1) {
	}
}


