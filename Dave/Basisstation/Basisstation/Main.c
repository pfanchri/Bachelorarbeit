/*
 * Main.c
 *
 *  Created on: Jun 13, 2016
 *      Author: Christof Pfannenmüller
 */
#include "Header_general.h" //including all Header files

// Global variables
uint8_t query_interruptTDA1_flag = 0;
uint8_t query_interruptTDA2_flag = 0;
uint8_t query_interruptTDA3_flag = 0;
uint8_t query_interruptTDA4_flag = 0;
uint8_t query_interruptTDA5_flag = 0;
uint8_t query_interruptTDA6_flag = 0;

int main(void) {

	init();
	USB_Init(); //for virt. COM Port
	COM_wait_for_transfer();
	set_TDA_status(TDA_ALL, 1);
	delay(40000);
	tda5340_gpio_init(TDA_ALL);
	spi_init(spi_master_ch);

	delay(500);
	delay(500);

	led_on(LED_ALL);
	delay(4000000);
	led_off(LED_ALL);
	led_on(LED1);
	delay(4000000);
	led_off(LED_ALL);
	led_on(LED1);

//	set_TDA_status(TDA1, 1);
//	delay(4000);
//	set_TDA_status(TDA2, 1);
//	delay(4000);
//	set_TDA_status(TDA3, 1);
//	delay(4000000);
//	set_TDA_status(TDA4, 1);
//	delay(4000);
//	set_TDA_status(TDA5, 1);
//	delay(4000000);
//	set_TDA_status(TDA6, 1);
//	delay(4000);

	delay(40000);
	tda5340_init(TDA6); //Verzögerung nach set Status muss groß genug sein bis SPI Kom möglich ist 		delay(45000); müsste das richtige sein

	tda5340_set_mode_and_config(TDA6, RX_MODE, 0);

//	Ablaufschleife START+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	COM_send_string("Initialisierung beendet - ");
	uint32_t istateTDA1 = 0, istateTDA2 = 0, istateTDA3 = 0, istateTDA4 = 0, istateTDA5 = 0, istateTDA6 = 0;
	struct {
		uint8_t pmf;
		uint8_t prx;
		uint8_t rx;
		uint8_t ppl;
		uint8_t agc;
	} rssi;
	rssi rssi_TDA1 = { .pmf = 0, .prx = 0, .rx = 0, .ppl = 0, .agc = 0 };
	rssi rssi_TDA2 = { .pmf = 0, .prx = 0, .rx = 0, .ppl = 0, .agc = 0 };
	rssi rssi_TDA3 = { .pmf = 0, .prx = 0, .rx = 0, .ppl = 0, .agc = 0 };
	rssi rssi_TDA4 = { .pmf = 0, .prx = 0, .rx = 0, .ppl = 0, .agc = 0 };
	rssi rssi_TDA5 = { .pmf = 0, .prx = 0, .rx = 0, .ppl = 0, .agc = 0 };
	rssi rssi_TDA6 = { .pmf = 0, .prx = 0, .rx = 0, .ppl = 0, .agc = 0 };

	query_interruptTDA1_flag = 0;
	query_interruptTDA2_flag = 0;
	query_interruptTDA3_flag = 0;
	query_interruptTDA4_flag = 0;
	query_interruptTDA5_flag = 0;
	query_interruptTDA6_flag = 0;

//---------------------------------------------------------------
	COM_send_string("Warte auf Übertragungen\r\n");
	while (1) {
		if (query_interruptTDA1_flag) {
			query_interruptTDA1_flag = 0;
			istate = tda5340_interrupt_readout(TDA1);
		}
		if (query_interruptTDA2_flag) {
			query_interruptTDA2_flag = 0;
			istate = tda5340_interrupt_readout(TDA2);
		}
		if (query_interruptTDA3_flag) {
			query_interruptTDA3_flag = 0;
			istate = tda5340_interrupt_readout(TDA3);
		}
		if (query_interruptTDA4_flag) {
			query_interruptTDA4_flag = 0;
			istate = tda5340_interrupt_readout(TDA4);
		}
		if (query_interruptTDA5_flag) {
			query_interruptTDA5_flag = 0;
			istate = tda5340_interrupt_readout(TDA5);
		}
		if (query_interruptTDA6_flag) {
			query_interruptTDA6_flag = 0;
			istate = tda5340_interrupt_readout(TDA6);
		}
//----------------------------------------------------------------

		if (istateTDA1 & (1 << 1)) {
			rssiTDA1.pmf = tda5340_transfer(TDA1, READ_FROM_CHIP, RSSIPMF, 0xFF);
			rssiTDA1.rx = tda5340_transfer(TDA1, READ_FROM_CHIP, RSSIRX, 0xFF);
			rssiTDA1.agc = (tda5340_transfer(TDA1, READ_FROM_CHIP, AGCADRR, 0xFF) & 0x06) >> 1;
			istateTDA1 &= ~(1 << 1);
		}
		if (istateTDA2 & (1 << 1)) {
			rssiTDA2.pmf = tda5340_transfer(TDA2, READ_FROM_CHIP, RSSIPMF, 0xFF);
			rssiTDA2.rx = tda5340_transfer(TDA2, READ_FROM_CHIP, RSSIRX, 0xFF);
			rssiTDA2.agc = (tda5340_transfer(TDA2, READ_FROM_CHIP, AGCADRR, 0xFF) & 0x06) >> 1;
			istateTDA2 &= ~(1 << 1);
		}
		if (istateTDA3 & (1 << 1)) {
			rssiTDA3.pmf = tda5340_transfer(TDA3, READ_FROM_CHIP, RSSIPMF, 0xFF);
			rssiTDA3.rx = tda5340_transfer(TDA3, READ_FROM_CHIP, RSSIRX, 0xFF);
			rssiTDA3.agc = (tda5340_transfer(TDA3, READ_FROM_CHIP, AGCADRR, 0xFF) & 0x06) >> 1;
			istateTDA3 &= ~(1 << 1);
		}
		if (istateTDA4 & (1 << 1)) {
			rssiTDA4.pmf = tda5340_transfer(TDA4, READ_FROM_CHIP, RSSIPMF, 0xFF);
			rssiTDA4.rx = tda5340_transfer(TDA4, READ_FROM_CHIP, RSSIRX, 0xFF);
			rssiTDA4.agc = (tda5340_transfer(TDA4, READ_FROM_CHIP, AGCADRR, 0xFF) & 0x06) >> 1;
			istateTDA4 &= ~(1 << 1);
		}
		if (istateTDA5 & (1 << 1)) {
			rssiTDA5.pmf = tda5340_transfer(TDA5, READ_FROM_CHIP, RSSIPMF, 0xFF);
			rssiTDA5.rx = tda5340_transfer(TDA5, READ_FROM_CHIP, RSSIRX, 0xFF);
			rssiTDA5.agc = (tda5340_transfer(TDA5, READ_FROM_CHIP, AGCADRR, 0xFF) & 0x06) >> 1;
			istateTDA5 &= ~(1 << 1);
		}
		if (istateTDA6 & (1 << 1)) {
			rssiTDA6.pmf = TDA6340_transfer(TDA6, READ_FROM_CHIP, RSSIPMF, 0xFF);
			rssiTDA6.rx = TDA6340_transfer(TDA6, READ_FROM_CHIP, RSSIRX, 0xFF);
			rssiTDA6.agc = (TDA6340_transfer(TDA6, READ_FROM_CHIP, AGCADRR, 0xFF) & 0x06) >> 1;
			istateTDA6 &= ~(1 << 1);
		}
//-------------------------------------------------------------------------------
		if (istateTDA1 & (1 << 3)) {

			rssiTDA1.prx = tda5340_transfer(TDA1, READ_FROM_CHIP, RSSIPRX, 0xFF);
			rssiTDA1.ppl = tda5340_transfer(TDA1, READ_FROM_CHIP, RSSIPPL, 0xFF);
			tda5340_set_mode_and_config(TDA1, SLEEP_MODE, 0);
			if (!tda5340_receive(TDA1, rx_data, &length)) {
				if (length > 32)
					length = 32;
			}
			tda5340_set_mode_and_config(TDA1, RX_MODE, 0);
			istate &= ~(1 << 3);
		}
		if (istateTDA2 & (1 << 3)) {

			rssiTDA2.prx = tda5340_transfer(TDA2, READ_FROM_CHIP, RSSIPRX, 0xFF);
			rssiTDA2.ppl = tda5340_transfer(TDA2, READ_FROM_CHIP, RSSIPPL, 0xFF);
			tda5340_set_mode_and_config(TDA2, SLEEP_MODE, 0);
			if (!tda5340_receive(TDA2, rx_data, &length)) {
				if (length > 32)
					length = 32;
			}
			tda5340_set_mode_and_config(TDA2, RX_MODE, 0);
			istate &= ~(1 << 3);
		}
		if (istateTDA3 & (1 << 3)) {

			rssiTDA3.prx = tda5340_transfer(TDA3, READ_FROM_CHIP, RSSIPRX, 0xFF);
			rssiTDA3.ppl = tda5340_transfer(TDA3, READ_FROM_CHIP, RSSIPPL, 0xFF);
			tda5340_set_mode_and_config(TDA3, SLEEP_MODE, 0);
			if (!tda5340_receive(TDA3, rx_data, &length)) {
				if (length > 32)
					length = 32;
			}
			tda5340_set_mode_and_config(TDA3, RX_MODE, 0);
			istate &= ~(1 << 3);
		}
		if (istateTDA4 & (1 << 3)) {

			rssiTDA4.prx = tda5340_transfer(TDA4, READ_FROM_CHIP, RSSIPRX, 0xFF);
			rssiTDA4.ppl = tda5340_transfer(TDA4, READ_FROM_CHIP, RSSIPPL, 0xFF);
			tda5340_set_mode_and_config(TDA4, SLEEP_MODE, 0);
			if (!tda5340_receive(TDA4, rx_data, &length)) {
				if (length > 32)
					length = 32;
			}
			tda5340_set_mode_and_config(TDA4, RX_MODE, 0);
			istate &= ~(1 << 3);
		}
		if (istateTDA5 & (1 << 3)) {

			rssiTDA5.prx = tda5340_transfer(TDA5, READ_FROM_CHIP, RSSIPRX, 0xFF);
			rssiTDA5.ppl = tda5340_transfer(TDA5, READ_FROM_CHIP, RSSIPPL, 0xFF);
			tda5340_set_mode_and_config(TDA5, SLEEP_MODE, 0);
			if (!tda5340_receive(TDA5, rx_data, &length)) {
				if (length > 32)
					length = 32;
			}
			tda5340_set_mode_and_config(TDA5, RX_MODE, 0);
			istate &= ~(1 << 3);
		}
		if (istateTDA6 & (1 << 3)) {

			rssiTDA6.prx = tda5340_transfer(TDA6, READ_FROM_CHIP, RSSIPRX, 0xFF);
			rssiTDA6.ppl = tda5340_transfer(TDA6, READ_FROM_CHIP, RSSIPPL, 0xFF);
			tda5340_set_mode_and_config(TDA6, SLEEP_MODE, 0);
			if (!tda5340_receive(TDA6, rx_data, &length)) {
				if (length > 32)
					length = 32;
			}
			tda5340_set_mode_and_config(TDA6, RX_MODE, 0);
			istate &= ~(1 << 3);
		}
//-------------------------------------------------------------------------------------
		//send to COM
		COM_send_string("Übertragung erkannt\r\n")

	}
//	Ablaufschleife ENDE++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//TESTMODUL-START-------------------------------------------------------------------------------------------------------------------------------------------------------
	char tx_data[36] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	char rx_data[36] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	COM_send_string("aktuell Test mit TDA6\r\n");
	uint8_t length = 0;

	struct {
		uint8_t pmf;
		uint8_t prx;
		uint8_t rx;
		uint8_t ppl;
		uint8_t agc;
	} rssi = { .pmf = 0, .prx = 0, .rx = 0, .ppl = 0, .agc = 0 };

	uint32_t istate = 0, led1_ctr = 0, led2_ctr = 0;

	COM_send_string("Beginn while loop------------------------------- \r\n");

	// Main loop
	led_off(LED_ALL);
	query_interruptTDA6_flag = 0; //damit keine Auswirkungen von Iterruots beim Einschalten

	while (1) {			//COM_send_string(".");

		// NINT Interrupt handling

		if (query_interruptTDA6_flag) {
			query_interruptTDA6_flag = 0;
			istate = tda5340_interrupt_readout(TDA6);
			COM_send_string("Interrupt ist aufgetreten\r\n");
			COM_send_int_as_string(istate);
			led_on(LED5);
		}

		// -----------------------------------------------------------------------------------------------------------

//			if(XMC_GPIO_GetInput(BUTTON1)) {
//				tda5340_transmit(tx_data, 8);
//			}

		// -----------------------------------------------------------------------------------------------------------

		// Switch to Rx-Mode if Tx is finished
		if (istate & (1 << 18)) {
			tda5340_set_mode_and_config(TDA6, RX_MODE, 0); //TODO: was is
			istate &= ~(1 << 18);
			COM_send_string("Switch  to Rx-Mode\r\n");
		}

		// -----------------------------------------------------------------------------------------------------------

		// Frame sync - Config A
		if (istate & (1 << 1)) {
			rssi.pmf = tda5340_transfer(TDA6, READ_FROM_CHIP, RSSIPMF, 0xFF);
			rssi.rx = tda5340_transfer(TDA6, READ_FROM_CHIP, RSSIRX, 0xFF);
			rssi.agc = (tda5340_transfer(TDA6, READ_FROM_CHIP, AGCADRR, 0xFF) & 0x06) >> 1;
			istate &= ~(1 << 1);
			COM_send_string("Frame sync - Config A\r\n");
		}

		// End of message - Config A
		if (istate & (1 << 3)) {
			// delay(5000);
			rssi.prx = tda5340_transfer(TDA6, READ_FROM_CHIP, RSSIPRX, 0xFF);
			rssi.ppl = tda5340_transfer(TDA6, READ_FROM_CHIP, RSSIPPL, 0xFF);

			tda5340_set_mode_and_config(TDA6, SLEEP_MODE, 0);
			COM_send_string("sleep-Mode\r\n");
			if (!tda5340_receive(TDA6, rx_data, &length)) {
				led_on(LED2);
				COM_send_string("set led high\r\n");
				if (length > 32)
					length = 32;

				led2_ctr = 400000;
			}

			tda5340_set_mode_and_config(TDA6, RX_MODE, 0);
			istate &= ~(1 << 3);
		}

		// -----------------------------------------------------------------------------------------------------------

		// LED-Timeout-Turnoff
		if (led1_ctr) {
			led1_ctr--;

			if (!led1_ctr)
				led_off(LED1);
		}

		if (led2_ctr) {
			led2_ctr--;

			if (!led2_ctr)
				led_off(LED2);
		}

		// -----------------------------------------------------------------------------------------------------------
	}

	tda5340_set_mode_and_config(TDA6, RX_MODE, 0); // ANPASSEN AN MEJHRE TDAs

//TESTMODUL-ENDE---------------------------------------------------------------------------------------------------------------------------------------------------------

//function for general test purposes
//general_test();
	while (1) {

	}

}
