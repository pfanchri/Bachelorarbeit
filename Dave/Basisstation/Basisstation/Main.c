/*
 * Main.c
 *
 *  Created on: Jun 13, 2016
 *      Author: Christof Pfannenmüller
 */
#include "Header_general.h" //including all Header files

int main(void) {

	init();
	USB_Init(); //for virt. COM Port

	spi_init(spi_master_ch);
	tda5340_gpio_init(TDA_ALL);

	delay(500);
	delay(500);

	led_on(LED_ALL);
	delay(4000000);
	led_off(LED_ALL);
	led_on(LED1);
	delay(4000000);
	led_off(LED_ALL);
	led_on(LED1);

	//set_TDA_status(TDA_ALL, 1);	delay(40000);

	set_TDA_status(TDA1, 1);
	delay(4000);
	set_TDA_status(TDA2, 1);
	delay(4000);

	set_TDA_status(TDA4, 1);
	delay(4000);
	set_TDA_status(TDA5, 1);
	delay(4000);
	set_TDA_status(TDA3, 1);
	delay(4000);
	set_TDA_status(TDA6, 1);
	delay(4000);
	delay(40000);
	tda5340_init(TDA1); //Verzögerung nach set Status muss groß genug sein bis SPI Kom möglich ist 		delay(45000); müsste das richtige sein







	//tda5340_set_mode_and_config(TDA1, RX_MODE, 0);





	COM_wait_for_transfer();

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

//function for general test purposes
//general_test();
	while (1) {

	}

}
