/*
 * Main.c
 *
 *  Created on: Jun 13, 2016
 *      Author: Christof Pfannenmüller
 */
#include "Header_general.h" //including all Header files



int main(void) {
	uint16_t spi_array_tx[10] = { 0 };
	uint16_t spi_array_rx[10] = { 0 };

	spi_init(spi_master_ch);
	spi_transfer(spi_master_ch, 0, spi_array_tx, spi_array_rx, 3);










	void init(void);

	while (1) {
	}
}


