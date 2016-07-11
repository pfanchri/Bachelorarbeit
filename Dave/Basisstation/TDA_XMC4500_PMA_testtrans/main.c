/*
 * main.c
 *
 *  Created on: 2015 Jul 23 12:47:16
 *  Author: pflaum
 */

#include "global.h"     //Declarations from DAVE3 Code Generation (includes SFR declaration)
#include <stdlib.h>

// Global variables
volatile uint8_t query_interrupt_flag = 0, button_pressed_flag = 0;

// -------------------------------------------------------------------------------------------------------------------

void delay(long unsigned int i) {
	while (i--) __NOP();
}

// -------------------------------------------------------------------------------------------------------------------

int16_t dig_to_dbm(uint8_t dig, uint8_t agc) {
	int32_t dbm_val =  (712L * dig - 231628L + 3289L * agc) / 2048UL;
	return (int16_t)dbm_val;
}

// -------------------------------------------------------------------------------------------------------------------

int main(void) {
	// Variables
	char tx_data[36] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	char rx_data[36] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	uint8_t length = 0;

	struct {
		uint8_t pmf;
		uint8_t prx;
		uint8_t rx;
		uint8_t ppl;
		uint8_t agc;
	} rssi = { .pmf = 0, .prx = 0, .rx  = 0, .ppl = 0, .agc = 0 };

	uint32_t istate = 0, led1_ctr = 0, led2_ctr = 0;

	// ---------------------------------------------------------------------------------------------------------------

	// Initializations
	USBD_VCOM_Init(&USBD_VCOM_0);
	USBD_VCOM_Connect();
	button_init(0);
	led_init();

	// ---------------------------------------------------------------------------------------------------------------

	tda5340_gpio_init();
	spi_init(spi_master_ch);

	XMC_GPIO_SetOutputLow(TDA5340_PON);
	delay(10000);
	XMC_GPIO_SetOutputHigh(TDA5340_PON);
	delay(100000);
	tda5340_init();


	// ---------------------------------------------------------------------------------------------------------------

	delay(25000);
	XMC_GPIO_SetOutputHigh(LED2);
	delay(25000);
	XMC_GPIO_SetOutputLow(LED2);

	tda5340_set_mode_and_config(RX_MODE);

	// ---------------------------------------------------------------------------------------------------------------

	// Main loop
	while (1) {
		// NINT Interrupt handling
		if (query_interrupt_flag) {
			query_interrupt_flag = 0;
			istate               = tda5340_interrupt_readout();
		}

		// -----------------------------------------------------------------------------------------------------------

		if(XMC_GPIO_GetInput(BUTTON1)) {
			tda5340_transmit(tx_data, 8);
		}

		// -----------------------------------------------------------------------------------------------------------

		// Switch to Rx-Mode if Tx is finished
		if (istate & (1 << 18)) {
			tda5340_set_mode_and_config(RX_MODE);
			istate &= ~(1 << 18);
		}

		// -----------------------------------------------------------------------------------------------------------

		// Frame sync - Config A
		if (istate & (1 << 1)) {
			rssi.pmf = tda5340_transfer(READ_FROM_CHIP, RSSIPMF, 0xFF);
			rssi.rx  = tda5340_transfer(READ_FROM_CHIP, RSSIRX, 0xFF);
			rssi.agc = (tda5340_transfer(READ_FROM_CHIP, AGCADRR, 0xFF) & 0x06) >> 1;
			istate  &= ~(1 << 1);
		}

		// End of message - Config A
		if (istate & (1 << 3)) {
			// delay(5000);
			rssi.prx = tda5340_transfer(READ_FROM_CHIP, RSSIPRX, 0xFF);
			rssi.ppl = tda5340_transfer(READ_FROM_CHIP, RSSIPPL, 0xFF);

			tda5340_set_mode_and_config(SLEEP_MODE);

			if (!tda5340_receive(rx_data, &length)) {
				XMC_GPIO_SetOutputHigh(LED2);

				if (length > 32) length = 32;

				led2_ctr = 100000;
			}

			tda5340_set_mode_and_config(RX_MODE);
			istate &= ~(1 << 3);
		}

		// -----------------------------------------------------------------------------------------------------------

		// LED-Timeout-Turnoff
		if (led1_ctr) {
			led1_ctr--;

			if (!led1_ctr) XMC_GPIO_SetOutputLow(LED1);
		}

		if (led2_ctr) {
			led2_ctr--;

			if (!led2_ctr) XMC_GPIO_SetOutputLow(LED2);
		}

		// -----------------------------------------------------------------------------------------------------------
	}

	return 0;
}

// -------------------------------------------------------------------------------------------------------------------

void ERU0_0_IRQHandler(void) {
	query_interrupt_flag = 1;
}
