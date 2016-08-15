/*
 * COMtransfer.c
 *
 *  Created on: Jul 7, 2016
 *      Author: student06
 */
#include "Header_general.h" //including all Header files

uint8_t COM_transfer_started = 0; //=0 when transfer started





/* Clock configuration */
XMC_SCU_CLOCK_CONFIG_t clock_config =
{
  .syspll_config.p_div = 2,
  .syspll_config.n_div = 80,
  .syspll_config.k_div = 4,
  .syspll_config.mode = XMC_SCU_CLOCK_SYSPLL_MODE_NORMAL,
  .syspll_config.clksrc = XMC_SCU_CLOCK_SYSPLLCLKSRC_OSCHP,
  .enable_oschp = true,
  .calibration_mode = XMC_SCU_CLOCK_FOFI_CALIBRATION_MODE_FACTORY,
  .fsys_clksrc = XMC_SCU_CLOCK_SYSCLKSRC_PLL,
  .fsys_clkdiv = 1,
  .fcpu_clkdiv = 1,
  .fccu_clkdiv = 1,
  .fperipheral_clkdiv = 1
};


void SystemCoreClockSetup(void)
{
  /* Setup settings for USB clock */
  XMC_SCU_CLOCK_Init(&clock_config);

  XMC_SCU_CLOCK_EnableUsbPll();
  XMC_SCU_CLOCK_StartUsbPll(2, 64);
  XMC_SCU_CLOCK_SetUsbClockDivider(4);
  XMC_SCU_CLOCK_SetUsbClockSource(XMC_SCU_CLOCK_USBCLKSRC_USBPLL);
  XMC_SCU_CLOCK_EnableClock(XMC_SCU_CLOCK_USB);

  SystemCoreClockUpdate();
}


void COM_wait_for_transfer(void) {
	if (COM_transfer_started == 1) {
		return;
	}
	uint16_t receivedBytes = 0;
	while (1) {
		led_on(LED1);
		receivedBytes = CDC_Device_BytesReceived(&VirtualSerial_CDC_Interface);
		CDC_Device_SendData(&VirtualSerial_CDC_Interface, "Press any Key to Start COM-Transfer\r\n", 36);
		CDC_Device_USBTask(&VirtualSerial_CDC_Interface);
		delay(2000000);
		led_off(LED1);
		delay(2000000);
		if (receivedBytes != 0) {
			CDC_Device_SendData(&VirtualSerial_CDC_Interface, "\r\n", 2);
			CDC_Device_USBTask(&VirtualSerial_CDC_Interface);
			COM_transfer_started = 1;
			return;
		}
	}

}

void COM_send_int_as_string(uint32_t data){
	//TODO: fertigstellen
if (COM_transfer_started==0) { //TODO: kann entfernt werden??
	COM_wait_for_transfer(); //wait till transfer started
}
	char str[11];

		   sprintf(str, "%u" , data);
		   CDC_Device_SendData(&VirtualSerial_CDC_Interface, str, strlen(str));
			CDC_Device_USBTask(&VirtualSerial_CDC_Interface); //TODO: hier notwendig?
}


void COM_send_string(const void* const string){
	CDC_Device_SendData(&VirtualSerial_CDC_Interface, string, strlen(string));
	CDC_Device_USBTask(&VirtualSerial_CDC_Interface); //TODO: hier notwendig? evtl zyklisch aufrufen

}

