/*
 * Main.c
 *
 *  Created on: Jun 13, 2016
 *      Author: Christof Pfannenmüller
 */
#include "Header_general.h" //including all Header files


#define SPI_TX_ARRAY_LENGH 20
#define SPI_RX_ARRAY_LENGH 20

int main(void){

	init();


led_on(0);
delay(4000000);
led_off(0);
led_on(1);
delay(4000000);
led_off(0);
led_on(1);


	uint16_t spi_array_tx[SPI_TX_ARRAY_LENGH] = { 0 };
	spi_array_tx[0] =0x05;
	spi_array_tx[1] =0xD0;
	uint16_t spi_array_rx[SPI_RX_ARRAY_LENGH] = { 0 };
	led_on(2);


	set_TDA_status(0,1);


led_on(6);
led_on(7);

			if (spi_array_rx[0]  ==  0 &&spi_array_rx[1]  ==  0&&spi_array_rx[2]  ==  0&&spi_array_rx[3]  ==  0&&spi_array_rx[4]  ==  0&&spi_array_rx[5]  ==  0
					&& spi_array_rx[6]  ==  0 &&spi_array_rx[7]  ==  0&&spi_array_rx[7]  ==  0&&spi_array_rx[8]  ==  0&&spi_array_rx[9]  ==  0	) {
				led_off(6);
			}


spi_init(spi_master_ch);
delay(4000000);
delay(4000000);
delay(4000000);
	spi_transfer(spi_master_ch, 0, spi_array_tx, spi_array_rx, 20);




	for (int var = 0; var < SPI_RX_ARRAY_LENGH; var++) {
		if (spi_array_rx[var]  !=  0) {
			led_on(5);
		}
	}

	while (1) {

	}

}
