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
//	tda5340_gpio_init(TDA1);
//	tda5340_gpio_init(TDA2);
//	tda5340_gpio_init(TDA3);
//	tda5340_gpio_init(TDA4);
//	tda5340_gpio_init(TDA5);
//	tda5340_gpio_init(TDA6);
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
	set_TDA_status(TDA6, 1);
	delay(4000);
	set_TDA_status(TDA3, 1);
	delay(4000);
	delay(40000); //Verzögerung nach set Status muss groß genug sein bis SPI Kom möglich ist 		delay(45000); müsste das richtige sein

	tda5340_get_serial_number(TDA6);
	tda5340_get_serial_number(TDA6);

	tda5340_get_serial_number(TDA4);


	COM_send_int_as_string(11111);


	CDC_Device_SendData(&VirtualSerial_CDC_Interface, "Serial Number TDA1\r\n", 20);

	COM_send_int_as_string(tda5340_get_serial_number(TDA1));CDC_Device_SendData(&VirtualSerial_CDC_Interface, "\r\n", 2);
	CDC_Device_SendData(&VirtualSerial_CDC_Interface, "Serial Number TDA2\r\n", 20);

	COM_send_int_as_string(tda5340_get_serial_number(TDA2));CDC_Device_SendData(&VirtualSerial_CDC_Interface, "\r\n", 2);
	CDC_Device_SendData(&VirtualSerial_CDC_Interface, "Serial Number TDA3\r\n", 20);

	COM_send_int_as_string(tda5340_get_serial_number(TDA3));CDC_Device_SendData(&VirtualSerial_CDC_Interface, "\r\n", 2);
	CDC_Device_SendData(&VirtualSerial_CDC_Interface, "Serial Number TDA4\r\n", 20);

	COM_send_int_as_string(tda5340_get_serial_number(TDA4));CDC_Device_SendData(&VirtualSerial_CDC_Interface, "\r\n", 2);
	CDC_Device_SendData(&VirtualSerial_CDC_Interface, "Serial Number TDA5\r\n", 20);

	COM_send_int_as_string(tda5340_get_serial_number(TDA5));CDC_Device_SendData(&VirtualSerial_CDC_Interface, "\r\n", 2);
	CDC_Device_SendData(&VirtualSerial_CDC_Interface, "Serial Number TDA6\r\n", 20);

	COM_send_int_as_string(tda5340_get_serial_number(TDA6));CDC_Device_SendData(&VirtualSerial_CDC_Interface, "\r\n", 2);

	COM_send_int_as_string(99999);
	COM_send_int_as_string(99999);
	COM_send_int_as_string(99999);

	CDC_Device_SendData(&VirtualSerial_CDC_Interface, "Hello, World! TEST\n", 19);

	CDC_Device_SendData(&VirtualSerial_CDC_Interface, "TESTo, World! TEST\n", 19);



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
