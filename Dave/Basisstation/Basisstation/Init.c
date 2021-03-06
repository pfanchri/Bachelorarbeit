/*
 * Init.c
 *
 *  Created on: Jun 16, 2016
 *      Author Christof Pfannenmüller (student06)
 */
#include "Header_general.h" //including all Header files

//aditional functions
void delay(unsigned long delay) {
	while (delay--) {
		__NOP();
	}
}

//init

void init(void) {

	//sets LED Pins as Outputs
	XMC_GPIO_SetMode(PORT_LED_1, PIN_LED_1, XMC_GPIO_MODE_OUTPUT_PUSH_PULL); //LED1
	XMC_GPIO_SetMode(PORT_LED_2, PIN_LED_2, XMC_GPIO_MODE_OUTPUT_PUSH_PULL);
	XMC_GPIO_SetMode(PORT_LED_3, PIN_LED_3, XMC_GPIO_MODE_OUTPUT_PUSH_PULL);
	XMC_GPIO_SetMode(PORT_LED_4, PIN_LED_4, XMC_GPIO_MODE_OUTPUT_PUSH_PULL);
	XMC_GPIO_SetMode(PORT_LED_5, PIN_LED_5, XMC_GPIO_MODE_OUTPUT_PUSH_PULL);
	XMC_GPIO_SetMode(PORT_LED_6, PIN_LED_6, XMC_GPIO_MODE_OUTPUT_PUSH_PULL);
	XMC_GPIO_SetMode(PORT_LED_7, PIN_LED_7, XMC_GPIO_MODE_OUTPUT_PUSH_PULL); //LED7
	//set  LED Pins high (active low);
	XMC_GPIO_SetOutputHigh(PORT_LED_1, PIN_LED_1);
	XMC_GPIO_SetOutputHigh(PORT_LED_2, PIN_LED_2);
	XMC_GPIO_SetOutputHigh(PORT_LED_3, PIN_LED_3);
	XMC_GPIO_SetOutputHigh(PORT_LED_4, PIN_LED_4);
	XMC_GPIO_SetOutputHigh(PORT_LED_5, PIN_LED_5);
	XMC_GPIO_SetOutputHigh(PORT_LED_6, PIN_LED_6);
	XMC_GPIO_SetOutputHigh(PORT_LED_7, PIN_LED_7);

	//set P_ON Pins as Output
	XMC_GPIO_SetMode(PORT_P_ON_TDA_1, PIN_P_ON_TDA_1, XMC_GPIO_MODE_OUTPUT_PUSH_PULL); //TDA1
	XMC_GPIO_SetMode(PORT_P_ON_TDA_2, PIN_P_ON_TDA_2, XMC_GPIO_MODE_OUTPUT_PUSH_PULL);
	XMC_GPIO_SetMode(PORT_P_ON_TDA_3, PIN_P_ON_TDA_3, XMC_GPIO_MODE_OUTPUT_PUSH_PULL);
	XMC_GPIO_SetMode(PORT_P_ON_TDA_4, PIN_P_ON_TDA_4, XMC_GPIO_MODE_OUTPUT_PUSH_PULL);
	XMC_GPIO_SetMode(PORT_P_ON_TDA_5, PIN_P_ON_TDA_5, XMC_GPIO_MODE_OUTPUT_PUSH_PULL);
	XMC_GPIO_SetMode(PORT_P_ON_TDA_6, PIN_P_ON_TDA_6, XMC_GPIO_MODE_OUTPUT_PUSH_PULL); //TDA6
//P_PON low -> TDAs off state
	XMC_GPIO_SetOutputLow(PORT_P_ON_TDA_1, PIN_P_ON_TDA_1);
	XMC_GPIO_SetOutputLow(PORT_P_ON_TDA_2, PIN_P_ON_TDA_2);
	XMC_GPIO_SetOutputLow(PORT_P_ON_TDA_3, PIN_P_ON_TDA_3);
	XMC_GPIO_SetOutputLow(PORT_P_ON_TDA_4, PIN_P_ON_TDA_4);
	XMC_GPIO_SetOutputLow(PORT_P_ON_TDA_5, PIN_P_ON_TDA_5);
	XMC_GPIO_SetOutputLow(PORT_P_ON_TDA_6, PIN_P_ON_TDA_6);

}
void send_serialnumber_to_com(void) {
	CDC_Device_SendData(&VirtualSerial_CDC_Interface, "\r\n", 2);
	CDC_Device_SendData(&VirtualSerial_CDC_Interface, "Serial Number TDA1\r\n", 20);
	COM_send_int_as_string(tda5340_get_serial_number(TDA1));
	CDC_Device_SendData(&VirtualSerial_CDC_Interface, "\r\n", 2);
	CDC_Device_SendData(&VirtualSerial_CDC_Interface, "Serial Number TDA2\r\n", 20);
	COM_send_int_as_string(tda5340_get_serial_number(TDA2));
	CDC_Device_SendData(&VirtualSerial_CDC_Interface, "\r\n", 2);
	CDC_Device_SendData(&VirtualSerial_CDC_Interface, "Serial Number TDA3\r\n", 20);
	COM_send_int_as_string(tda5340_get_serial_number(TDA3));
	CDC_Device_SendData(&VirtualSerial_CDC_Interface, "\r\n", 2);
	CDC_Device_SendData(&VirtualSerial_CDC_Interface, "Serial Number TDA4\r\n", 20);
	COM_send_int_as_string(tda5340_get_serial_number(TDA4));
	CDC_Device_SendData(&VirtualSerial_CDC_Interface, "\r\n", 2);
	CDC_Device_SendData(&VirtualSerial_CDC_Interface, "Serial Number TDA5\r\n", 20);
	COM_send_int_as_string(tda5340_get_serial_number(TDA5));
	CDC_Device_SendData(&VirtualSerial_CDC_Interface, "\r\n", 2);
	CDC_Device_SendData(&VirtualSerial_CDC_Interface, "Serial Number TDA6\r\n", 20);
	COM_send_int_as_string(tda5340_get_serial_number(TDA6));
	CDC_Device_SendData(&VirtualSerial_CDC_Interface, "\r\n", 2);
}
void general_test(void) {
	//uint8_t i = 0;
	//i=tda5340_transfer(0, 0x05, 0xD0 , 0);
	//
	//if(i==0){
	//	led_on(i);i=0;
	//}
	//test für TDA Lib von Felix

	//tda5340_gpio_init(0);
	//tda5340_init(0);
	//uint32_t serialnumber = tda5340_get_serial_number(0);

	//serialnumber -> LEDs
	//for (int var = 0; var < 32; var++) {
	//		if (serialnumber & (1 << var)) {
	//			led_on(5);
	//		}
	//		led_on(6);
	//		delay(4000000);
	//		led_off(5);
	//		led_off(6);
	//}

	set_TDA_status(0, 1);
	delay(40000);

	spi_init(spi_master_ch);
	delay(40000);

	tda5340_transfer(5, READ_FROM_CHIP, IS2, 0xFF);
	delay(40000);
	tda5340_transfer(5, READ_FROM_CHIP, 0xDB, 0);

	tda5340_transfer(5, READ_FROM_CHIP, IS2, 0xFF);
	delay(40000);
	tda5340_transfer(5, READ_FROM_CHIP, 0xDB, 0);

//
//
//
//		uint16_t spi_array_tx[20] = { 0 };
//		spi_array_tx[0] =0x05;
//		spi_array_tx[1] =0xD3;
//		uint16_t spi_array_rx[20] = { 0 };
//		led_on(2);
//
//
//		set_TDA_status(0,1);
//
//
//	led_on(6);
//	led_on(7);
//
//				if (spi_array_rx[0]  ==  0 &&spi_array_rx[1]  ==  0&&spi_array_rx[2]  ==  0&&spi_array_rx[3]  ==  0&&spi_array_rx[4]  ==  0&&spi_array_rx[5]  ==  0
//						&& spi_array_rx[6]  ==  0 &&spi_array_rx[7]  ==  0&&spi_array_rx[7]  ==  0&&spi_array_rx[8]  ==  0&&spi_array_rx[9]  ==  0	) {
//					led_off(6);
//				}
//
//
//	spi_init(spi_master_ch);
//		spi_transfer(spi_master_ch, 4, spi_array_tx, spi_array_rx, 20);
//
//
//
//		for (int var = 0; var < 20; var++) {
//			if (spi_array_rx[var]  !=  0) {
//				led_on(5);
//			}
//		}





	//	CDC_Device_SendData(&VirtualSerial_CDC_Interface, "Start Reading FIFO TDA 3\r\n", 26);
	//
	//	int8_t data_send[10] = { 1, 3, 5, 7, 9, 2, 4, 6, 8, 10 };
	//	int8_t data_rec[10];
	//	uint8_t lenght = 10;
	//	tda5340_fifo_rw(TDA3, 1, data_send, &lenght);
	//	tda5340_fifo_rw(TDA3, 0, data_rec, &lenght);
	//	COM_send_int_as_string(data_rec[0]);
	//	CDC_Device_SendData(&VirtualSerial_CDC_Interface, "\r\n", 2);
	//
	//	COM_send_int_as_string(data_rec[1]);
	//	CDC_Device_SendData(&VirtualSerial_CDC_Interface, "\r\n", 2);
	//
	//	COM_send_int_as_string(data_rec[2]);
	//	CDC_Device_SendData(&VirtualSerial_CDC_Interface, "\r\n", 2);
	//
	//	COM_send_int_as_string(data_rec[3]);
	//	CDC_Device_SendData(&VirtualSerial_CDC_Interface, "\r\n", 2);
	//
	//	COM_send_int_as_string(data_rec[4]);
	//	CDC_Device_SendData(&VirtualSerial_CDC_Interface, "\r\n", 2);
	//
	//	COM_send_int_as_string(data_rec[5]);
	//	CDC_Device_SendData(&VirtualSerial_CDC_Interface, "\r\n", 2);
	//
	//	COM_send_int_as_string(data_rec[6]);
	//	CDC_Device_SendData(&VirtualSerial_CDC_Interface, "\r\n", 2);
	//
	//	COM_send_int_as_string(data_rec[7]);
	//	CDC_Device_SendData(&VirtualSerial_CDC_Interface, "\r\n", 2);
	//
	//	COM_send_int_as_string(data_rec[8]);
	//	CDC_Device_SendData(&VirtualSerial_CDC_Interface, "\r\n", 2);
	//
	//	COM_send_int_as_string(data_rec[9]);
	//	CDC_Device_SendData(&VirtualSerial_CDC_Interface, "\r\n", 2);
	//
	//	COM_send_int_as_string(data_rec[10]);
	//	CDC_Device_SendData(&VirtualSerial_CDC_Interface, "\r\n", 2);
	//
	//	CDC_Device_SendData(&VirtualSerial_CDC_Interface, "\r\n", 2);

		CDC_Device_USBTask(&VirtualSerial_CDC_Interface);

	//	set_TDA_status(TDA_ALL, 0);
	//	set_TDA_status(TDA_ALL, 1);
	//
	//	set_TDA_status(TDA_ALL, 0);
	//	set_TDA_status(TDA_ALL, 1);
	//	set_TDA_status(TDA_ALL, 0);
	//	set_TDA_status(TDA_ALL, 1);




}
