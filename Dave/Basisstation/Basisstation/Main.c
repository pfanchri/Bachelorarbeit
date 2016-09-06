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

int16_t dig_to_dbm(uint8_t dig, uint8_t agc) {
	int32_t dbm_val = (712L * dig - 231628L + 3289L * agc) / 2048UL;
	return (int16_t) dbm_val;
}

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
	tda5340_init(TDA1); //Verzögerung nach set Status muss groß genug sein bis SPI Kom möglich ist 		delay(45000); müsste das richtige sein
	tda5340_set_mode_and_config(TDA1, RX_MODE, 0);

	delay(40000);

	//für gesamte Platine:
	tda5340_init(TDA2);
	tda5340_set_mode_and_config(TDA2, RX_MODE, 0);
	tda5340_init(TDA3);
	tda5340_set_mode_and_config(TDA3, RX_MODE, 0);
	tda5340_init(TDA4);
	tda5340_set_mode_and_config(TDA4, RX_MODE, 0);
	tda5340_init(TDA5);
	tda5340_set_mode_and_config(TDA5, RX_MODE, 0);
	tda5340_init(TDA6);
	tda5340_set_mode_and_config(TDA6, RX_MODE, 0);

//	Ablaufschleife START+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	COM_send_string("Initialisierung beendet - ");
	uint8_t data_recieved = 0;
	uint32_t istateTDA1 = 0, istateTDA2 = 0, istateTDA3 = 0, istateTDA4 = 0, istateTDA5 = 0, istateTDA6 = 0;
	uint8_t lengthTDA1 = 0, lengthTDA2 = 0, lengthTDA3 = 0, lengthTDA4 = 0, lengthTDA5 = 0, lengthTDA6 = 0;
	uint32_t transfernumber = 0;
	uint32_t led_ctr = 0;
	char rx_data_TDA1[36] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };//TODO: Test ob er auch wiklich gesetzt wird; aktuell sind vor und nach dem empfangen inhalt der variable gleich
	char rx_data_TDA2[36] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	char rx_data_TDA3[36] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	char rx_data_TDA4[36] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	char rx_data_TDA5[36] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	char rx_data_TDA6[36] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	struct rssi {
		uint8_t pmf;
		uint8_t prx;
		uint8_t rx;
		uint8_t ppl;
		uint8_t agc;
	};

	struct rssi rssiTDA1 = { .pmf = 0, .prx = 0, .rx = 0, .ppl = 0, .agc = 0 };
	struct rssi rssiTDA2 = { .pmf = 0, .prx = 0, .rx = 0, .ppl = 0, .agc = 0 };
	struct rssi rssiTDA3 = { .pmf = 0, .prx = 0, .rx = 0, .ppl = 0, .agc = 0 };
	struct rssi rssiTDA4 = { .pmf = 0, .prx = 0, .rx = 0, .ppl = 0, .agc = 0 };
	struct rssi rssiTDA5 = { .pmf = 0, .prx = 0, .rx = 0, .ppl = 0, .agc = 0 };
	struct rssi rssiTDA6 = { .pmf = 0, .prx = 0, .rx = 0, .ppl = 0, .agc = 0 };

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
			istateTDA1 = tda5340_interrupt_readout(TDA1);
		}
		if (query_interruptTDA2_flag) {
			query_interruptTDA2_flag = 0;
			istateTDA2 = tda5340_interrupt_readout(TDA2);
		}
		if (query_interruptTDA3_flag) {
			query_interruptTDA3_flag = 0;
			istateTDA3 = tda5340_interrupt_readout(TDA3);
		}
		if (query_interruptTDA4_flag) {
			query_interruptTDA4_flag = 0;
			istateTDA4 = tda5340_interrupt_readout(TDA4);
		}
		if (query_interruptTDA5_flag) {
			query_interruptTDA5_flag = 0;
			istateTDA5 = tda5340_interrupt_readout(TDA5);
		}
		if (query_interruptTDA6_flag) {
			query_interruptTDA6_flag = 0;
			led_on(LED3);
			istateTDA6 = tda5340_interrupt_readout(TDA6);
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
			rssiTDA6.pmf = tda5340_transfer(TDA6, READ_FROM_CHIP, RSSIPMF, 0xFF);
			rssiTDA6.rx = tda5340_transfer(TDA6, READ_FROM_CHIP, RSSIRX, 0xFF);
			rssiTDA6.agc = (tda5340_transfer(TDA6, READ_FROM_CHIP, AGCADRR, 0xFF) & 0x06) >> 1;
			istateTDA6 &= ~(1 << 1);
		}
//-------------------------------------------------------------------------------
		if (istateTDA1 & (1 << 3)) {

			rssiTDA1.prx = tda5340_transfer(TDA1, READ_FROM_CHIP, RSSIPRX, 0xFF);
			rssiTDA1.ppl = tda5340_transfer(TDA1, READ_FROM_CHIP, RSSIPPL, 0xFF);
			tda5340_set_mode_and_config(TDA1, SLEEP_MODE, 0);
			if (!tda5340_receive(TDA1, rx_data_TDA1, &lengthTDA1)) {
				if (lengthTDA1 > 32)
					lengthTDA1 = 32;
			}
			tda5340_set_mode_and_config(TDA1, RX_MODE, 0);
			data_recieved = 1;
			istateTDA1 &= ~(1 << 3);
		}
		if (istateTDA2 & (1 << 3)) {

			rssiTDA2.prx = tda5340_transfer(TDA2, READ_FROM_CHIP, RSSIPRX, 0xFF);
			rssiTDA2.ppl = tda5340_transfer(TDA2, READ_FROM_CHIP, RSSIPPL, 0xFF);
			tda5340_set_mode_and_config(TDA2, SLEEP_MODE, 0);
			if (!tda5340_receive(TDA2, rx_data_TDA2, &lengthTDA2)) {
				if (lengthTDA2 > 32)
					lengthTDA2 = 32;
			}
			tda5340_set_mode_and_config(TDA2, RX_MODE, 0);
			data_recieved = 1;
			istateTDA2 &= ~(1 << 3);
		}
		if (istateTDA3 & (1 << 3)) {

			rssiTDA3.prx = tda5340_transfer(TDA3, READ_FROM_CHIP, RSSIPRX, 0xFF);
			rssiTDA3.ppl = tda5340_transfer(TDA3, READ_FROM_CHIP, RSSIPPL, 0xFF);
			tda5340_set_mode_and_config(TDA3, SLEEP_MODE, 0);
			if (!tda5340_receive(TDA3, rx_data_TDA3, &lengthTDA3)) {
				if (lengthTDA3 > 32)
					lengthTDA3 = 32;
			}
			tda5340_set_mode_and_config(TDA3, RX_MODE, 0);
			data_recieved = 1;
			istateTDA3 &= ~(1 << 3);
		}
		if (istateTDA4 & (1 << 3)) {

			rssiTDA4.prx = tda5340_transfer(TDA4, READ_FROM_CHIP, RSSIPRX, 0xFF);
			rssiTDA4.ppl = tda5340_transfer(TDA4, READ_FROM_CHIP, RSSIPPL, 0xFF);
			tda5340_set_mode_and_config(TDA4, SLEEP_MODE, 0);
			if (!tda5340_receive(TDA4, rx_data_TDA4, &lengthTDA4)) {
				if (lengthTDA4 > 32)
					lengthTDA4 = 32;
			}
			tda5340_set_mode_and_config(TDA4, RX_MODE, 0);
			data_recieved = 1;
			istateTDA4 &= ~(1 << 3);
		}
		if (istateTDA5 & (1 << 3)) {

			rssiTDA5.prx = tda5340_transfer(TDA5, READ_FROM_CHIP, RSSIPRX, 0xFF);
			rssiTDA5.ppl = tda5340_transfer(TDA5, READ_FROM_CHIP, RSSIPPL, 0xFF);
			tda5340_set_mode_and_config(TDA5, SLEEP_MODE, 0);
			if (!tda5340_receive(TDA5, rx_data_TDA5, &lengthTDA5)) {
				if (lengthTDA5 > 32)
					lengthTDA5 = 32;
			}
			tda5340_set_mode_and_config(TDA5, RX_MODE, 0);
			data_recieved = 1;
			istateTDA5 &= ~(1 << 3);
		}
		if (istateTDA6 & (1 << 3)) {

			rssiTDA6.prx = tda5340_transfer(TDA6, READ_FROM_CHIP, RSSIPRX, 0xFF);
			rssiTDA6.ppl = tda5340_transfer(TDA6, READ_FROM_CHIP, RSSIPPL, 0xFF);
			tda5340_set_mode_and_config(TDA6, SLEEP_MODE, 0);
			if (!tda5340_receive(TDA6, rx_data_TDA6, &lengthTDA6)) {
				if (lengthTDA6 > 32)
					lengthTDA6 = 32;
			}
			tda5340_set_mode_and_config(TDA6, RX_MODE, 0);
			data_recieved = 1;
			istateTDA6 &= ~(1 << 3);
		}
//-------------------------------------------------------------------------------------
		//send to COM
		if (data_recieved) {
			transfernumber++;
			COM_send_string("#################### Übertragung erkannt ####################\r\n");
			COM_send_string("Übertragung Nummer ");
			COM_send_int_as_string(transfernumber);
			COM_send_string("\r\n\r\n");
			COM_send_string("TDA1:");
			COM_send_string("\r\nPMF:");
			COM_send_int_as_string(rssiTDA1.pmf);
			COM_send_string("\r\nPRX:");
			COM_send_int_as_string(rssiTDA1.prx);
			COM_send_string("\r\nRX:");
			COM_send_int_as_string(rssiTDA1.rx);
			COM_send_string("\r\nPPL:");
			COM_send_int_as_string(rssiTDA1.ppl);
			COM_send_string("\r\nAGC:");
			COM_send_int_as_string(rssiTDA1.agc);
			COM_send_string("\r\nEmpfangsleistung (dBm):");
			if (dig_to_dbm(rssiTDA1.ppl, rssiTDA1.agc) < 0) {
				COM_send_string("-");
			}
			COM_send_int_as_string(abs(dig_to_dbm(rssiTDA1.ppl, rssiTDA1.agc)));
			COM_send_string("\r\n");
			COM_send_string("Empfangene Daten:");
			for (int i = 0; i <= lengthTDA1; ++i) {
				COM_send_int_as_string(rx_data_TDA1[i]);

			}
			COM_send_string("\r\n\r\n");

			COM_send_string("TDA2:");
			COM_send_string("\r\nPMF:");
			COM_send_int_as_string(rssiTDA2.pmf);
			COM_send_string("\r\nPRX:");
			COM_send_int_as_string(rssiTDA2.prx);
			COM_send_string("\r\nRX:");
			COM_send_int_as_string(rssiTDA2.rx);
			COM_send_string("\r\nPPL:");
			COM_send_int_as_string(rssiTDA2.ppl);
			COM_send_string("\r\nAGC:");
			COM_send_int_as_string(rssiTDA2.agc);
			COM_send_string("\r\nEmpfangsleistung (dBm):");
			if (dig_to_dbm(rssiTDA2.ppl, rssiTDA2.agc) < 0) {
				COM_send_string("-");
			}
			COM_send_int_as_string(abs(dig_to_dbm(rssiTDA2.ppl, rssiTDA2.agc)));
			COM_send_string("\r\n");
			COM_send_string("Empfangene Daten:");
			for (int i = 0; i <= lengthTDA2; ++i) {
				COM_send_int_as_string(rx_data_TDA2[i]);

			}
			COM_send_string("\r\n\r\n");

			COM_send_string("TDA3:");
			COM_send_string("\r\nPMF:");
			COM_send_int_as_string(rssiTDA3.pmf);
			COM_send_string("\r\nPRX:");
			COM_send_int_as_string(rssiTDA3.prx);
			COM_send_string("\r\nRX:");
			COM_send_int_as_string(rssiTDA3.rx);
			COM_send_string("\r\nPPL:");
			COM_send_int_as_string(rssiTDA3.ppl);
			COM_send_string("\r\nAGC:");
			COM_send_int_as_string(rssiTDA3.agc);
			COM_send_string("\r\nEmpfangsleistung (dBm):");
			if (dig_to_dbm(rssiTDA3.ppl, rssiTDA3.agc) < 0) {
				COM_send_string("-");
			}
			COM_send_int_as_string(abs(dig_to_dbm(rssiTDA3.ppl, rssiTDA3.agc)));
			COM_send_string("\r\n");
			COM_send_string("Empfangene Daten:");
			for (int i = 0; i <= lengthTDA3; ++i) {
				COM_send_int_as_string(rx_data_TDA3[i]);

			}
			COM_send_string("\r\n\r\n");

			COM_send_string("TDA4:");
			COM_send_string("\r\nPMF:");
			COM_send_int_as_string(rssiTDA4.pmf);
			COM_send_string("\r\nPRX:");
			COM_send_int_as_string(rssiTDA4.prx);
			COM_send_string("\r\nRX:");
			COM_send_int_as_string(rssiTDA4.rx);
			COM_send_string("\r\nPPL:");
			COM_send_int_as_string(rssiTDA4.ppl);
			COM_send_string("\r\nAGC:");
			COM_send_int_as_string(rssiTDA4.agc);
			COM_send_string("\r\nEmpfangsleistung (dBm):");
			if (dig_to_dbm(rssiTDA4.ppl, rssiTDA4.agc) < 0) {
				COM_send_string("-");
			}
			COM_send_int_as_string(abs(dig_to_dbm(rssiTDA4.ppl, rssiTDA4.agc)));
			COM_send_string("\r\n");
			COM_send_string("Empfangene Daten:");
			for (int i = 0; i <= lengthTDA4; ++i) {
				COM_send_int_as_string(rx_data_TDA4[i]);

			}
			COM_send_string("\r\n\r\n");

			COM_send_string("TDA5:");
			COM_send_string("\r\nPMF:");
			COM_send_int_as_string(rssiTDA5.pmf);
			COM_send_string("\r\nPRX:");
			COM_send_int_as_string(rssiTDA5.prx);
			COM_send_string("\r\nRX:");
			COM_send_int_as_string(rssiTDA5.rx);
			COM_send_string("\r\nPPL:");
			COM_send_int_as_string(rssiTDA5.ppl);
			COM_send_string("\r\nAGC:");
			COM_send_int_as_string(rssiTDA5.agc);
			COM_send_string("\r\nEmpfangsleistung (dBm):");
			if (dig_to_dbm(rssiTDA5.ppl, rssiTDA5.agc) < 0) {
				COM_send_string("-");
			}
			COM_send_int_as_string(abs(dig_to_dbm(rssiTDA5.ppl, rssiTDA5.agc)));
			COM_send_string("\r\n");
			COM_send_string("Empfangene Daten:");
			for (int i = 0; i <= lengthTDA5; ++i) {
				COM_send_int_as_string(rx_data_TDA5[i]);

			}
			COM_send_string("\r\n\r\n");

			COM_send_string("TDA6:");
			COM_send_string("\r\nPMF:");
			COM_send_int_as_string(rssiTDA6.pmf);
			COM_send_string("\r\nPRX:");
			COM_send_int_as_string(rssiTDA6.prx);
			COM_send_string("\r\nRX:");
			COM_send_int_as_string(rssiTDA6.rx);
			COM_send_string("\r\nPPL:");
			COM_send_int_as_string(rssiTDA6.ppl);
			COM_send_string("\r\nAGC:");
			COM_send_int_as_string(rssiTDA6.agc);
			COM_send_string("\r\nEmpfangsleistung (dBm):");
			if (dig_to_dbm(rssiTDA6.ppl, rssiTDA6.agc) < 0) {
				COM_send_string("-");
			}
			COM_send_int_as_string(abs(dig_to_dbm(rssiTDA6.ppl, rssiTDA6.agc)));
			COM_send_string("\r\n");
			COM_send_string("Empfangene Daten:");
			for (int i = 0; i <= lengthTDA6; ++i) {
				COM_send_int_as_string(rx_data_TDA6[i]);

			}
			COM_send_string("\r\n\r\n");

			led_ctr = 400000;
			led_on(LED7);
			data_recieved = 0;
		}

		if (led_ctr) {
			led_ctr--;

			if (!led_ctr)
				led_off(LED7);
		}
	}
//	Ablaufschleife ENDE++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

////TESTMODUL-START-------------------------------------------------------------------------------------------------------------------------------------------------------
//	char tx_data[36] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
//	char rx_data[36] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
//	COM_send_string("aktuell Test mit TDA6\r\n");
//	uint8_t length = 0;
//
//	struct {
//		uint8_t pmf;
//		uint8_t prx;
//		uint8_t rx;
//		uint8_t ppl;
//		uint8_t agc;
//	} rssi = { .pmf = 0, .prx = 0, .rx = 0, .ppl = 0, .agc = 0 };
//
//	uint32_t istate = 0, led1_ctr = 0, led2_ctr = 0;
//
//	COM_send_string("Beginn while loop------------------------------- \r\n");
//
//	// Main loop
//	led_off(LED_ALL);
//	query_interruptTDA6_flag = 0; //damit keine Auswirkungen von Iterruots beim Einschalten
//
//	while (1) {			//COM_send_string(".");
//
//		// NINT Interrupt handling
//
//		if (query_interruptTDA6_flag) {
//			query_interruptTDA6_flag = 0;
//			istate = tda5340_interrupt_readout(TDA6);
//			COM_send_string("Interrupt ist aufgetreten\r\n");
//			COM_send_int_as_string(istate);
//			led_on(LED5);
//		}
//
//		// -----------------------------------------------------------------------------------------------------------
//
////			if(XMC_GPIO_GetInput(BUTTON1)) {
////				tda5340_transmit(tx_data, 8);
////			}
//
//		// -----------------------------------------------------------------------------------------------------------
//
//		// Switch to Rx-Mode if Tx is finished
//		if (istate & (1 << 18)) {
//			tda5340_set_mode_and_config(TDA6, RX_MODE, 0); //TODO: was is
//			istate &= ~(1 << 18);
//			COM_send_string("Switch  to Rx-Mode\r\n");
//		}
//
//		// -----------------------------------------------------------------------------------------------------------
//
//		// Frame sync - Config A
//		if (istate & (1 << 1)) {
//			rssi.pmf = tda5340_transfer(TDA6, READ_FROM_CHIP, RSSIPMF, 0xFF);
//			rssi.rx = tda5340_transfer(TDA6, READ_FROM_CHIP, RSSIRX, 0xFF);
//			rssi.agc = (tda5340_transfer(TDA6, READ_FROM_CHIP, AGCADRR, 0xFF) & 0x06) >> 1;
//			istate &= ~(1 << 1);
//			COM_send_string("Frame sync - Config A\r\n");
//		}
//
//		// End of message - Config A
//		if (istate & (1 << 3)) {
//			// delay(5000);
//			rssi.prx = tda5340_transfer(TDA6, READ_FROM_CHIP, RSSIPRX, 0xFF);
//			rssi.ppl = tda5340_transfer(TDA6, READ_FROM_CHIP, RSSIPPL, 0xFF);
//
//			tda5340_set_mode_and_config(TDA6, SLEEP_MODE, 0);
//			COM_send_string("sleep-Mode\r\n");
//			if (!tda5340_receive(TDA6, rx_data, &length)) {
//				led_on(LED2);
//				COM_send_string("set led high\r\n");
//				if (length > 32)
//					length = 32;
//
//				led2_ctr = 400000;
//			}
//
//			tda5340_set_mode_and_config(TDA6, RX_MODE, 0);
//			istate &= ~(1 << 3);
//		}
//
//		// -----------------------------------------------------------------------------------------------------------
//
//		// LED-Timeout-Turnoff
//		if (led1_ctr) {
//			led1_ctr--;
//
//			if (!led1_ctr)
//				led_off(LED1);
//		}
//
//		if (led2_ctr) {
//			led2_ctr--;
//
//			if (!led2_ctr)
//				led_off(LED2);
//		}
//
//		// -----------------------------------------------------------------------------------------------------------
//	}
//
//	tda5340_set_mode_and_config(TDA6, RX_MODE, 0); // ANPASSEN AN MEJHRE TDAs
//
////TESTMODUL-ENDE---------------------------------------------------------------------------------------------------------------------------------------------------------

//function for general test purposes
//general_test();
	while (1) {

	}

}
