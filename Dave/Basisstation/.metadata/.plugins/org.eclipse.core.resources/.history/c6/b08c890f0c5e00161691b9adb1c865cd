/*
 * Main.c
 *
 *  Created on: Jun 13, 2016
 *      Author: Christof Pfannenmüller
 */
#include "Header_general.h" //including all Header files


// Global variables
volatile uint8_t query_interruptTDA1_flag = 0;
volatile uint8_t query_interruptTDA2_flag = 0;
volatile uint8_t query_interruptTDA3_flag = 0;
volatile uint8_t query_interruptTDA4_flag = 0;
volatile uint8_t query_interruptTDA5_flag = 0;
volatile uint8_t query_interruptTDA6_flag = 0;

int main(void) {

	init();
	USB_Init(); //for virt. COM Port

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


	COM_wait_for_transfer();
	//set_TDA_status(TDA_ALL, 1);	delay(40000);

	set_TDA_status(TDA1, 1);
	delay(4000);
	set_TDA_status(TDA2, 1);
	delay(4000);
	set_TDA_status(TDA3, 1);
	delay(4000000);
	set_TDA_status(TDA4, 1);
	delay(4000);
	set_TDA_status(TDA5, 1);
	delay(4000000);
	set_TDA_status(TDA6, 1);
	delay(4000);

	delay(40000);
	tda5340_init(TDA1); //Verzögerung nach set Status muss groß genug sein bis SPI Kom möglich ist 		delay(45000); müsste das richtige sein

	tda5340_set_mode_and_config(TDA1, RX_MODE, 0);

//TESTMODUL-START-------------------------------------------------------------------------------------------------------------------------------------------------------
	char tx_data[36] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
		char rx_data[36] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
		COM_send_string("CHAR   TX RX  DATA\r\n");
		uint8_t length = 0;

		struct {
			uint8_t pmf;
			uint8_t prx;
			uint8_t rx;
			uint8_t ppl;
			uint8_t agc;
		} rssi = { .pmf = 0, .prx = 0, .rx  = 0, .ppl = 0, .agc = 0 };

		uint32_t istate = 0, led1_ctr = 0, led2_ctr = 0;

			COM_send_string("Beginn while loop \r\n");

	// Main loop
led_off(LED_ALL );
query_interruptTDA1_flag=0;//damit keine Auswirkungen von Iterruots beim Einschalten

		while (1) {			//COM_send_string(".");

			// NINT Interrupt handling


			if (query_interruptTDA1_flag) {
				query_interruptTDA1_flag = 0;
				istate               = tda5340_interrupt_readout(TDA1);
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
				tda5340_set_mode_and_config(TDA1, RX_MODE,0); //TODO: was is
				istate &= ~(1 << 18);
				COM_send_string("Switch  to Rx-Mode\r\n");
			}

			// -----------------------------------------------------------------------------------------------------------

			// Frame sync - Config A
			if (istate & (1 << 1)) {
				rssi.pmf = tda5340_transfer(TDA1, READ_FROM_CHIP, RSSIPMF, 0xFF);
				rssi.rx  = tda5340_transfer(TDA1, READ_FROM_CHIP, RSSIRX, 0xFF);
				rssi.agc = (tda5340_transfer(TDA1, READ_FROM_CHIP, AGCADRR, 0xFF) & 0x06) >> 1;
				istate  &= ~(1 << 1);
				COM_send_string("Frame sync - Config A\r\n");
			}

			// End of message - Config A
			if (istate & (1 << 3)) {
				// delay(5000);
				rssi.prx = tda5340_transfer(TDA1, READ_FROM_CHIP, RSSIPRX, 0xFF);
				rssi.ppl = tda5340_transfer(TDA1, READ_FROM_CHIP, RSSIPPL, 0xFF);

				tda5340_set_mode_and_config(TDA1,SLEEP_MODE,0);
				COM_send_string("sleep-Mode\r\n");
				if (!tda5340_receive(TDA1, rx_data, &length)) {
					led_on(LED2);
					COM_send_string("set led high\r\n");
					if (length > 32) length = 32;

					led2_ctr = 100000;
				}

				tda5340_set_mode_and_config(TDA1,RX_MODE,0);
				istate &= ~(1 << 3);
			}

			// -----------------------------------------------------------------------------------------------------------

			// LED-Timeout-Turnoff
			if (led1_ctr) {
				led1_ctr--;

				if (!led1_ctr) led_off(LED1);
			}

			if (led2_ctr) {
				led2_ctr--;

				if (!led2_ctr) led_off(LED2);
			}

			// -----------------------------------------------------------------------------------------------------------
		}
//TESTMODUL-ENDE---------------------------------------------------------------------------------------------------------------------------------------------------------


	tda5340_set_mode_and_config(TDA1, RX_MODE, 0);// ANPASSEN AN MEJHRE TDAs









//function for general test purposes
//general_test();
	while (1) {

	}

}
