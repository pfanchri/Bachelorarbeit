/******************************************************************************
 * @file     Main.c
 * @brief    SPI example
 * @version  V1.0
 * @date     20. February 2015
 * @note
 * Copyright (C) 2015 Infineon Technologies AG. All rights reserved.
 ******************************************************************************
 * @par
 * Infineon Technologies AG (Infineon) is supplying this software for use with
 * Infineon�s microcontrollers.
 * This file can be freely distributed within development tools that are
 * supporting such microcontrollers.
 * @par
 * THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
 * OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
 * INFINEON SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL,
 * OR CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 *****************************************************************************/

#include <XMC4500.h>
#include <xmc_gpio.h>
#include <xmc_usic.h>
#include <xmc_spi.h>
#include "spi.h"
#include "portmakros.h"

int main(void) {
	uint16_t spi_array_tx[10] = { 0 };
	uint16_t spi_array_rx[10] = { 0 };

	spi_init(spi_master_ch);
	spi_transfer(spi_master_ch, 0, spi_array_tx, spi_array_rx, 3);

	/* Loop forever */
	while (1) {
	}
}
