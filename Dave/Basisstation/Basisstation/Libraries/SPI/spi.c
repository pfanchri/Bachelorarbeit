/*
 * spi.c
 *
 *  Created on: Oct 1, 2015
 *      Author: pflaum
 *      adapt by Pfannenmüller
 */

#include <XMC4500.h>

#include <xmc_gpio.h>
#include <xmc_usic.h>
#include <xmc_spi.h>

#include "spi.h"
#include "portmakros.h"

XMC_USIC_CH_t *spi_master_ch = SPI_CHANNEL;

void spi_init(XMC_USIC_CH_t *const channel) {
	XMC_GPIO_PORT_t *master_rx_pin     = SPI_RX_P;
	const uint8_t master_rx_pin_nr     = SPI_RX_PIN;
	XMC_GPIO_PORT_t *master_tx_pin     = SPI_TX_P;
	const uint8_t master_tx_pin_nr     = SPI_TX_PIN;
	XMC_GPIO_PORT_t *master_clck_pin   = SPI_CLCK_P;
	const uint8_t master_clck_pin_nr   = SPI_CLCK_PIN;
	XMC_GPIO_PORT_t *master_selo_pin_0 = SPI_SELO_P_0;
	const uint8_t master_selo_pin_0_nr = SPI_SELO_PIN_0;

	#if (NUMBER_OF_SPI_SLAVES > 1)
		XMC_GPIO_PORT_t *master_selo_pin_1 = SPI_SELO_P_1;
		const uint8_t master_selo_pin_1_nr = SPI_SELO_PIN_1;
	#endif
	#if (NUMBER_OF_SPI_SLAVES > 2)
		XMC_GPIO_PORT_t *master_selo_pin_2 = SPI_SELO_P_2;
		const uint8_t master_selo_pin_2_nr = SPI_SELO_PIN_2;
	#endif
	#if (NUMBER_OF_SPI_SLAVES > 3)
		XMC_GPIO_PORT_t *master_selo_pin_3 = SPI_SELO_P_3;
		const uint8_t master_selo_pin_3_nr = SPI_SELO_PIN_3;
	#endif
	#if (NUMBER_OF_SPI_SLAVES > 4)
		XMC_GPIO_PORT_t *master_selo_pin_4 = SPI_SELO_P_4;
		const uint8_t master_selo_pin_4_nr = SPI_SELO_PIN_4;
	#endif
	#if (NUMBER_OF_SPI_SLAVES > 5)
		XMC_GPIO_PORT_t *master_selo_pin_5 = SPI_SELO_P_5;
		const uint8_t master_selo_pin_5_nr = SPI_SELO_PIN_5;
	#endif

	//Master Mode
	/*SPI Configuration*/
	XMC_SPI_CH_CONFIG_t spi_config = {
		.baudrate       = SPI_BAUDRATE,
		.bus_mode       = XMC_SPI_CH_BUS_MODE_MASTER,
		.selo_inversion = SPI_SLAVE_SEL_POLARITY,
		.parity_mode    = XMC_USIC_CH_PARITY_MODE_NONE,
	};

	/*GPIO Input pin configuration*/
	XMC_GPIO_CONFIG_t master_rx_pin_config = {
		.mode = XMC_GPIO_MODE_INPUT_PULL_UP
	};
	XMC_GPIO_Init(master_rx_pin, master_rx_pin_nr, &master_rx_pin_config);

	/*GPIO Output pin configuration*/
	XMC_GPIO_CONFIG_t master_tx_pin_config = {
		.mode         = SPI_ALT_OUT,
		.output_level = XMC_GPIO_OUTPUT_LEVEL_LOW
	};
	XMC_GPIO_Init(master_tx_pin, master_tx_pin_nr, &master_tx_pin_config);

	/*GPIO Clock pin configuration*/
	XMC_GPIO_CONFIG_t master_clck_pin_config = { .mode = SPI_ALT_OUT };
	XMC_GPIO_Init(master_clck_pin, master_clck_pin_nr, &master_clck_pin_config);

	XMC_GPIO_CONFIG_t master_selo_pin_config = { .mode = SPI_ALT_OUT };
	XMC_GPIO_Init(master_selo_pin_0, master_selo_pin_0_nr, &master_selo_pin_config);

	#if (NUMBER_OF_SPI_SLAVES > 1)
		XMC_GPIO_Init(master_selo_pin_1, master_selo_pin_1_nr, &master_selo_pin_config);
	#endif
	#if (NUMBER_OF_SPI_SLAVES > 2)
		XMC_GPIO_Init(master_selo_pin_2, master_selo_pin_2_nr, &master_selo_pin_config);
	#endif
	#if (NUMBER_OF_SPI_SLAVES > 3)
		XMC_GPIO_Init(master_selo_pin_3, master_selo_pin_3_nr, &master_selo_pin_config);
	#endif
	#if (NUMBER_OF_SPI_SLAVES > 4)
		XMC_GPIO_Init(master_selo_pin_4, master_selo_pin_4_nr, &master_selo_pin_config);
	#endif
	#if (NUMBER_OF_SPI_SLAVES > 5)
		XMC_GPIO_Init(master_selo_pin_5, master_selo_pin_5_nr, &master_selo_pin_config);
	#endif

	/*Initialize SPI*/
	XMC_SPI_CH_Init(channel, &spi_config);
	XMC_SPI_CH_ConfigureShiftClockOutput(channel, SPI_CLK_MODE,
	                                     XMC_USIC_CH_BRG_SHIFT_CLOCK_OUTPUT_SCLK);

	/*Start SPI*/
	XMC_SPI_CH_Start(channel);

	/*Settings (Bit-Order, Word-Length, FIFO)*/
	if (SPI_MSB_FIRST) XMC_SPI_CH_SetBitOrderMsbFirst(channel);
	else   XMC_SPI_CH_SetBitOrderLsbFirst(channel);

	XMC_SPI_CH_SetWordLength(channel, SPI_WORDLENGTH);
	XMC_USIC_CH_RXFIFO_Configure(channel, 0, 1, 0);

	/*Input source selected*/
	XMC_SPI_CH_SetInputSource(channel, SPI_CH_INPUT, USIC_IN);
}

void spi_transfer(XMC_USIC_CH_t *const channel, uint8_t selo, uint16_t *data_in, uint16_t *data_out, uint8_t length) {
	if (selo < NUMBER_OF_SPI_SLAVES) {
		XMC_SPI_CH_EnableSlaveSelect(channel, XMC_SPI_CH_SLAVE_SELECT_0 << selo);

		for (uint8_t i = 0; i < length; i++) {
			data_out[i] = spi_byte(channel, data_in[i]);
		}

		XMC_SPI_CH_DisableSlaveSelect(channel);
	}
}

uint8_t spi_byte(XMC_USIC_CH_t *const channel, uint16_t data) {
	XMC_SPI_CH_Transmit(channel, data, XMC_SPI_CH_MODE_STANDARD);

	/*Wait till the byte has been transmitted*/
	while (!(XMC_SPI_CH_GetStatusFlag(channel) & XMC_SPI_CH_STATUS_FLAG_TRANSMIT_SHIFT_INDICATION)) {
		/* wait for ACK */
	}

	XMC_SPI_CH_ClearStatusFlag(channel, XMC_SPI_CH_STATUS_FLAG_TRANSMIT_SHIFT_INDICATION);

	while (XMC_USIC_CH_RXFIFO_IsEmpty(channel)) ;

	return (uint8_t)XMC_SPI_CH_GetReceivedData(channel);
}
