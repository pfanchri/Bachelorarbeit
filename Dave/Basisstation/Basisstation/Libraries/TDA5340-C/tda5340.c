/*
 * TDA5340.c
 *
 *  Created on: 28.01.2015
 *      Author: pflaum
 *      adapt by Pfannenmüller
 */

#include "Header_general.h"

//TODO: crc16 orginal fehlt noch

/*
 * Initalises PON und PP2
 */
//TODO: auf mehrer TDAs anpassen
void tda5340_gpio_init(uint8_t device_number) {

	// Interrupt-Config an PP2 Pins
	//	Set Pins to Input (depending of device number
	//		for TDA1
	if (device_number == TDA_ALL || device_number == TDA1) {
		XMC_GPIO_EnableDigitalInput(PORT_PP2_TDA_1, PIN_PP2_TDA_1);
		XMC_GPIO_CONFIG_t TDA_PP2_CONFIG =
				{ .mode = XMC_GPIO_MODE_INPUT_PULL_UP };
		XMC_GPIO_Init(PORT_PP2_TDA_1, PIN_PP2_TDA_1, &TDA_PP2_CONFIG);
	}
	//		for TDA2
	if (device_number == TDA_ALL || device_number == TDA2) {
		XMC_GPIO_EnableDigitalInput(PORT_PP2_TDA_2, PIN_PP2_TDA_2);
		XMC_GPIO_CONFIG_t TDA_PP2_CONFIG =
				{ .mode = XMC_GPIO_MODE_INPUT_PULL_UP };
		XMC_GPIO_Init(PORT_PP2_TDA_2, PIN_PP2_TDA_2, &TDA_PP2_CONFIG);
	}
	//		for TDA3
	if (device_number == TDA_ALL || device_number == TDA3) {
		XMC_GPIO_EnableDigitalInput(PORT_PP2_TDA_3, PIN_PP2_TDA_3);
		XMC_GPIO_CONFIG_t TDA_PP2_CONFIG =
				{ .mode = XMC_GPIO_MODE_INPUT_PULL_UP };
		XMC_GPIO_Init(PORT_PP2_TDA_3, PIN_PP2_TDA_3, &TDA_PP2_CONFIG);
	}
	//		for TDA4
	if (device_number == TDA_ALL || device_number == TDA4) {
		XMC_GPIO_EnableDigitalInput(PORT_PP2_TDA_4, PIN_PP2_TDA_4);
		XMC_GPIO_CONFIG_t TDA_PP2_CONFIG =
				{ .mode = XMC_GPIO_MODE_INPUT_PULL_UP };
		XMC_GPIO_Init(PORT_PP2_TDA_4, PIN_PP2_TDA_4, &TDA_PP2_CONFIG);
	}
	//		for TDA5
	if (device_number == TDA_ALL || device_number == TDA5) {
		XMC_GPIO_EnableDigitalInput(PORT_PP2_TDA_5, PIN_PP2_TDA_5);
		XMC_GPIO_CONFIG_t TDA_PP2_CONFIG =
				{ .mode = XMC_GPIO_MODE_INPUT_PULL_UP };
		XMC_GPIO_Init(PORT_PP2_TDA_5, PIN_PP2_TDA_5, &TDA_PP2_CONFIG);
	}
	//		for TDA6
	if (device_number == TDA_ALL || device_number == TDA6) {
		XMC_GPIO_EnableDigitalInput(PORT_PP2_TDA_6, PIN_PP2_TDA_6);
		XMC_GPIO_CONFIG_t TDA_PP2_CONFIG =
				{ .mode = XMC_GPIO_MODE_INPUT_PULL_UP };
		XMC_GPIO_Init(PORT_PP2_TDA_6, PIN_PP2_TDA_6, &TDA_PP2_CONFIG);
	}




	//	configure Interrupts (depending of device number
	//		for TDA1
	if (device_number == TDA_ALL || device_number == TDA1) {



	}




		const XMC_ERU_ETL_CONFIG_t PP2_ETL_CONFIG = { .input_a =
				XMC_ERU_ETL_INPUT_A0, .source = XMC_ERU_ETL_SOURCE_A,
				.edge_detection = XMC_ERU_ETL_EDGE_DETECTION_FALLING,
				.status_flag_mode = XMC_ERU_ETL_STATUS_FLAG_MODE_HWCTRL,
				.enable_output_trigger = 1, .output_trigger_channel =
						XMC_ERU_ETL_OUTPUT_TRIGGER_CHANNEL0 /* OGU0 */
		};
		XMC_ERU_ETL_Init(ERU0_ETL3, &PP2_ETL_CONFIG);
		const XMC_ERU_OGU_CONFIG_t PP2_EVENT_DETECTION_CONFIG = {
				.service_request = XMC_ERU_OGU_SERVICE_REQUEST_ON_TRIGGER };
		XMC_ERU_OGU_Init(ERU0_OGU0, &PP2_EVENT_DETECTION_CONFIG);
		NVIC_SetPriority(ERU0_0_IRQn, 3U);
		NVIC_EnableIRQ(ERU0_0_IRQn);
	}

//TODO: auf mehrer TDAs anpassen
	uint8_t tda5340_transfer(uint8_t device_number, uint8_t instruction,
			uint8_t reg_address, uint16_t data) {
		uint16_t transferdata[3] = { instruction, reg_address, data };
		uint8_t data_rd;

		spi_transfer(spi_master_ch, device_number, transferdata, transferdata,
				3);
		data_rd = transferdata[2];
		return data_rd;
	}

//TODO: auf mehrer TDAs anpassen
	uint8_t tda5340_transmit(uint8_t device_number, uint8_t config,
			int8_t *data, uint8_t length) {
		tda5340_set_mode_and_config(device_number, SLEEP_MODE, 0);
		tda5340_fifo_rw(device_number, 1, data, &length);
		tda5340_set_mode_and_config(device_number, TRANSMIT_MODE, config);

		return 0;
	}

//TODO: auf mehrer TDAs anpassen
	uint8_t tda5340_receive(uint8_t device_number, int8_t *data,
			uint8_t *length) {
		uint8_t error = tda5340_fifo_rw(device_number, 0, data, length);
		data[*length] = 0;
		return error;
	}

//TODO: auf mehrer TDAs anpassen
	uint8_t tda5340_fifo_rw(uint8_t device_number, uint8_t wnr, int8_t *data,
			uint8_t *length) {
		uint8_t length_local = *length;
		uint16_t transferdata[66] = { 0 };
		uint16_t crc = 0x1D0F;
		uint8_t ctr = 0, index = 2, crc_rec;

		// Write to FIFO
		if (wnr) {
			if (length_local > 25)
				length_local = 25;

			transferdata[0] = 0x06;
			transferdata[1] = ((length_local + 8) * 8) - 1; // 3 Bytes Runin, 2 Bytes Wake-Up, 1 Byte Payload length, Payload, 2 Bytes CRC
			transferdata[2] = 0x00;
			transferdata[3] = 0x00;
			transferdata[4] = 0x00;
			transferdata[5] = 0x2D;
			transferdata[6] = 0xD4;
			transferdata[7] = length_local;
			crc = crc16(crc, length_local);

			for (uint8_t jj = 8; jj < length_local + 8; jj++) {
				transferdata[jj] = data[jj - 8];
				crc = crc16(crc, transferdata[jj]);
			}

			crc ^= 0xFFFF;
			transferdata[8 + length_local] = (crc >> 8);
			transferdata[9 + length_local] = (crc & 0xFF);
			spi_transfer(spi_master_ch, device_number, transferdata,
					transferdata, length_local + 10); // FIFO-Order + FIFO length + 2 Bytes Key + Payload length + Payload + 2 Bytes CRC
		}
		// Read from FIFO
		else {
			XMC_SPI_CH_EnableSlaveSelect(spi_master_ch,
					(XMC_SPI_CH_SLAVE_SELECT_0 << device_number));

			// Readout FIFO
			spi_byte(spi_master_ch, 0x04);

			// Evaluate first data frame
			length_local = spi_byte(spi_master_ch, 0xFF); // Get number of payload bytes
			crc = crc16(crc, length_local);

			if (length_local > 66)
				length_local = 66;

			*length = length_local;

			while (ctr < length_local) {
				data[ctr] = spi_byte(spi_master_ch, 0xFF);
				crc = crc16(crc, data[ctr]);

				ctr++;
				index++;

				if (index == 0x05) {
					spi_byte(spi_master_ch, 0xFF);
					spi_byte(spi_master_ch, 0x04);
					index = 1;
				}
			}

			crc ^= 0xFFFF;

			// 2 additional bytes (CRC16) need to be received
			crc_rec = spi_byte(spi_master_ch, 0xFF);
			crc = crc16(crc, crc_rec);

			index++;

			if (index == 0x05) {
				spi_byte(spi_master_ch, 0xFF);
				spi_byte(spi_master_ch, 0x04);
				index = 1;
			}

			// Receive last byte and signalize EOF
			USIC0_CH0->TCSR |= (1 << USIC_CH_TCSR_EOF_Pos);
			crc_rec = spi_byte(spi_master_ch, 0xFF);
			crc = crc16(crc, crc_rec);
			XMC_SPI_CH_DisableSlaveSelect(spi_master_ch);
		}

		return wnr ? 0 : (crc && 1);
	}

//TODO: auf mehrer TDAs anpassen
	uint8_t tda5340_datavalid(uint8_t device_number, uint8_t reg_address,
			uint8_t data) {
		uint8_t reg = tda5340_transfer(device_number, READ_FROM_CHIP, 0xDF,
				0xFF);
		uint8_t value = tda5340_transfer(device_number, READ_FROM_CHIP, 0xE0,
				reg);
		uint8_t chk = tda5340_transfer(device_number, READ_FROM_CHIP, 0xE1,
				value);

		return !(reg_address == reg) && (data == value)
				&& (chk == (reg ^ value));
	}

//TODO: auf mehrer TDAs anpassen
	uint8_t tda5340_command(uint8_t device_number, uint8_t instruction,
			uint8_t reg_address, uint8_t data) {
		uint8_t invalid = 1, ctr = 5;

		while (invalid && ctr--) {
			tda5340_transfer(device_number, instruction, reg_address, data);
			invalid = tda5340_datavalid(device_number, reg_address, data);
		}

		return invalid; // Return 0 for valid, 1 for invalid data
	}

//TODO: auf mehrer TDAs anpassen
	void tda5340_set_page(uint8_t device_number, uint8_t page) {
		if (page < 4) {
			tda5340_transfer(device_number, WRITE_TO_CHIP, SFRPAGE, page);
		}
	}

//TODO: auf mehrer TDAs anpassen
	void tda5340_set_channels(uint8_t device_number, uint8_t noc, uint8_t mod) {
		uint8_t nocmod;
		nocmod = 0x10 | ((noc & 0x03) << 2) | (mod & 0x03);

		tda5340_transfer(device_number, WRITE_TO_CHIP, A_CHCFG, nocmod);
	}

//TODO: auf mehrer TDAs anpassen
	void tda5340_set_mode_and_config(uint8_t device_number, uint8_t mode,
			uint8_t config) {
		uint8_t transferbit = 0;

		if (mode < 5) {
			transferbit = (mode & 0x03);
		}

		// Transmit mode config
		if (config < 4) {
			transferbit |= (config << 2); // Set Config
		}

		if (mode == DEEP_SLEEP_MODE) {
			tda5340_transfer(device_number, WRITE_TO_CHIP, CMC,
					0x30 | transferbit);
			// Set Pins for deep-sleep-mode
			XMC_GPIO_SetOutputLow(TDA5340_PON_PORT, TDA5340_PON_PIN);
		} else {
			tda5340_transfer(device_number, WRITE_TO_CHIP, CMC,
					0x10 | transferbit);
			XMC_GPIO_SetOutputHigh(TDA5340_PON_PORT, TDA5340_PON_PIN);
		}
	}

//TODO: auf mehrer TDAs anpassen
	uint32_t tda5340_interrupt_readout(uint8_t device_number) {
		uint32_t interrupts = 0;
		interrupts |= tda5340_transfer(device_number, READ_FROM_CHIP, IS2, 0xFF)
				<< 16;
		interrupts |= tda5340_transfer(device_number, READ_FROM_CHIP, IS1, 0xFF)
				<< 8;
		interrupts |= tda5340_transfer(device_number, READ_FROM_CHIP, IS0,
				0xFF);
		return interrupts;
	}

//TODO: auf mehrer TDAs anpassen
	uint32_t tda5340_get_serial_number(uint8_t device_number) {
		uint32_t sn = 0;

		for (uint8_t i = 0; i < 4; i++) {
			sn <<= 8;
			sn |= tda5340_transfer(device_number, READ_FROM_CHIP, SN0 + i,
					sn >> 8);
		}

		return sn;
	}

//TODO: auf mehrer TDAs anpassen
	void tda5340_init(uint8_t device_number) {
		uint8_t invalid = 0;

		// Read interrupt registers to force NINT high
		tda5340_interrupt_readout(device_number);

		// Set chip controls (device_number, Enable brownout detector, go to sleep mode, only use config A)
		tda5340_command(device_number, WRITE_TO_CHIP, CMC, (1 << 4));

		// Set common registers
		// Clock output 100 kHz but not enabled
		invalid += tda5340_command(device_number, WRITE_TO_CHIP, CLKOUT0, 0x6E); //Clock Divider Register 0
		invalid += tda5340_command(device_number, WRITE_TO_CHIP, CLKOUT2, 0x00); //Clock Divider Register 2

		/* General configuration register set */
		invalid += tda5340_command(device_number, WRITE_TO_CHIP, PPCFG0, 0xFF); /**< Pin configuration */
		invalid += tda5340_command(device_number, WRITE_TO_CHIP, PPCFG1, 0xF2); /**< Pin configuration */
		invalid += tda5340_command(device_number, WRITE_TO_CHIP, PPCFG2, 0x40); /**< Pin configuration */
		invalid += tda5340_command(device_number, WRITE_TO_CHIP, RSSICFG, 0x11); /**< RSSI Configuration register */
		invalid += tda5340_command(device_number, WRITE_TO_CHIP, RSSIOFFS,
				RSSI_OFFSET_VALUE); /**< RSSI offset register */
		invalid += tda5340_command(device_number, WRITE_TO_CHIP, RSSISLOPE,
				RSSI_SLOPE_VALUE); /**< RSSI slope register */
		invalid += tda5340_command(device_number, WRITE_TO_CHIP, ADCINSEL,
				0x00); /**< ADC Input Selection Register */
		invalid += tda5340_command(device_number, WRITE_TO_CHIP, IM0, 0xF0); /**< Interruption enable mask */
		invalid += tda5340_command(device_number, WRITE_TO_CHIP, IM1, 0xFF); /**< Interruption enable mask */
		invalid += tda5340_command(device_number, WRITE_TO_CHIP, IM2, 0xB8); /**< Interruption enable mask */
		invalid += tda5340_command(device_number, WRITE_TO_CHIP, RXC, 0x84); /**< RX control register */
		invalid += tda5340_command(device_number, WRITE_TO_CHIP, TXC, 0x27); /**< TX control register */
		invalid += tda5340_command(device_number, WRITE_TO_CHIP, TXFIFOAEL,
				0x20);

#if (RX_MODE == SELF_POLLING_MODE)
		// Self Polling Mode configuration
		invalid += tda5340_command(device_number, WRITE_TO_CHIP, SPMC, 0x09);// SPM control register
		invalid += tda5340_command(device_number, WRITE_TO_CHIP, SPMRT, 0x0A);
		invalid += tda5340_command(device_number, WRITE_TO_CHIP, SPMOFFT0, 0x2C);
		invalid += tda5340_command(device_number, WRITE_TO_CHIP, SPMOFFT1, 0x01);
		invalid += tda5340_command(device_number, WRITE_TO_CHIP, SPMONTA0, 0x1D);
		invalid += tda5340_command(device_number, WRITE_TO_CHIP, SPMONTA1, 0x00);
#endif

		// Config A for RX
		tda5340_set_page(device_number, 0);
		tda5340_command(device_number, WRITE_TO_CHIP, A_IF1, 0xA7); //IF1 Register
		tda5340_command(device_number, WRITE_TO_CHIP, A_AGCSFCFG, 0x51);
		tda5340_command(device_number, WRITE_TO_CHIP, A_AGCCFG0, 0x03);
		tda5340_command(device_number, WRITE_TO_CHIP, A_AGCCFG1, 0x2E);
		tda5340_command(device_number, WRITE_TO_CHIP, A_AGCTHR, 0x08);

		// Rx-Bitrate-relevant settings
		tda5340_command(device_number, WRITE_TO_CHIP, A_AFCKCFG0, 0xC0); // AFC Integrators Gain Coefficients Register 0
		tda5340_command(device_number, WRITE_TO_CHIP, A_AFCKCFG1, 0x00); // AFC Integrators Gain Coefficients Register 1
		tda5340_command(device_number, WRITE_TO_CHIP, A_PMFUDSF, 0x42); // Peak Memory Filter Up-Down Factor Register
		tda5340_command(device_number, WRITE_TO_CHIP, A_PDFMFC, 0x97); // PD Filter and Matched Filter Configuration Register
		tda5340_command(device_number, WRITE_TO_CHIP, A_PDECF, 0x02); // Pre Decimation Factor Register
		tda5340_command(device_number, WRITE_TO_CHIP, A_PDECSCFSK, 0x0E); // Pre Decimation Scaling Register FSK Mode
		tda5340_command(device_number, WRITE_TO_CHIP, A_SRC, 0x31); // Sample Rate Converter

		tda5340_command(device_number, WRITE_TO_CHIP, A_EXTSLC0, 0x00); //External Data Slicer Configuration Register 0
		tda5340_command(device_number, WRITE_TO_CHIP, A_CDRCFG0, 0x8C); //CDR Configuration Register 0
		tda5340_command(device_number, WRITE_TO_CHIP, A_SLCCFG, 0x94); //Slicer Configuration Register
		tda5340_command(device_number, WRITE_TO_CHIP, A_TSILENA, 0x10); //TSI Length Register A
		tda5340_command(device_number, WRITE_TO_CHIP, A_TSILENB, 0x10); //TSI Length Register B
		tda5340_command(device_number, WRITE_TO_CHIP, A_TSIPTA0, 0x65); //TSI Pattern Data Reference A Register 0
		tda5340_command(device_number, WRITE_TO_CHIP, A_TSIPTA1, 0xA6); //TSI Pattern Data Reference A Register 1
		tda5340_command(device_number, WRITE_TO_CHIP, A_TSIPTB0, 0xA6); //TSI Pattern Data Reference B Register 0
		tda5340_command(device_number, WRITE_TO_CHIP, A_TSIPTB1, 0x59); //TSI Pattern Data Reference B Register 1
		tda5340_command(device_number, WRITE_TO_CHIP, A_EOMC, 0x07); //End Of Message Control Register
		tda5340_command(device_number, WRITE_TO_CHIP, A_PKBITPOS, 0x08); //RSSI Peak Detector Bit Position Register
		tda5340_command(device_number, WRITE_TO_CHIP, A_CHCFG, 0x11); //Channel Configuration Register

		// Setting RX-frequency to 867.0000 MHz (with IF-frequency 274 kHz low side LO-injection)
		tda5340_command(device_number, WRITE_TO_CHIP, A_PLLINTC1, 0x67); //PLL MMD Integer Value Register Channel 1
		tda5340_command(device_number, WRITE_TO_CHIP, A_PLLFRAC0C1, 0xFA); //PLL Fractional Division Ratio Register 0 Channel 1
		tda5340_command(device_number, WRITE_TO_CHIP, A_PLLFRAC1C1, 0x0C); //PLL Fractional Division Ratio Register 1 Channel 1
		tda5340_command(device_number, WRITE_TO_CHIP, A_PLLFRAC2C1, 0x11); //PLL Fractional Division Ratio Register 2 Channel 1

		// Wake up control
		invalid += tda5340_command(device_number, WRITE_TO_CHIP, A_WURSSITH1,
				0x80);

		// Config B for TX
		tda5340_set_page(device_number, 1);
		invalid += tda5340_command(device_number, WRITE_TO_CHIP, TXCHNL, 0x00); /**< TX channel selection */
		invalid += tda5340_command(device_number, WRITE_TO_CHIP, A_TXRF, 0x00); /**< Duty cycle control selection */
		invalid += tda5340_command(device_number, WRITE_TO_CHIP, A_TXCFG, 0x40); /**< TX configuration register */
		invalid += tda5340_command(device_number, WRITE_TO_CHIP, A_TXBDRDIV0,
				0x76); /**< TX baudrate divider register 0. Fsys = 21948KHz */
		invalid += tda5340_command(device_number, WRITE_TO_CHIP, A_TXBDRDIV1,
				0x04); /**< TX baudrate divider register 1. Fsys = 21948KHz */
		invalid += tda5340_command(device_number, WRITE_TO_CHIP, A_TXCHOFFS0,
				0x00); /**< TX Channel Offset Register 0 */
		invalid += tda5340_command(device_number, WRITE_TO_CHIP, A_TXCHOFFS1,
				0x00); /**< TX Channel Offset Register 1 */
		invalid += tda5340_command(device_number, WRITE_TO_CHIP, A_TXDSHCFG0,
				0x00); /**< TX data shaping configuration register 0. ASK sloping division */
		invalid += tda5340_command(device_number, WRITE_TO_CHIP, A_TXDSHCFG1,
				0x00); /**< TX data shaping configuration register 1. Gaussian filter division */
		invalid += tda5340_command(device_number, WRITE_TO_CHIP, A_TXDSHCFG2,
				0x00); /**< TX data shaping configuration register 2. Gaussian filter division. ASK sloping division */
		invalid += tda5340_command(device_number, WRITE_TO_CHIP, A_TXPOWER0,
				0x00); /**< TX power configuration register 0 */
		invalid += tda5340_command(device_number, WRITE_TO_CHIP, A_TXPOWER1,
				0x1F); /**< TX power configuration register 1 */
		invalid += tda5340_command(device_number, WRITE_TO_CHIP, A_TXFDEV,
				0xD7); /**< TX frequency deviation register */

		// Setting TX-frequency to 868.0 MHz
		invalid += tda5340_command(device_number, WRITE_TO_CHIP, A_PLLINTC1,
				0x67); /**< PLL multi modulus divider integer value channel 1 */
		invalid += tda5340_command(device_number, WRITE_TO_CHIP, A_PLLFRAC0C1,
				0x95); /**< PLL fractional division ratio channel 1 */
		invalid += tda5340_command(device_number, WRITE_TO_CHIP, A_PLLFRAC1C1,
				0x09); /**< PLL fractional division ratio channel 1 */
		invalid += tda5340_command(device_number, WRITE_TO_CHIP, A_PLLFRAC2C1,
				0x10); /**< PLL fractional division ratio channel 1 */

		// Config C for TX
		tda5340_set_page(device_number, 2);
		invalid += tda5340_command(device_number, WRITE_TO_CHIP, TXCHNL, 0x00); /**< TX channel selection */
		invalid += tda5340_command(device_number, WRITE_TO_CHIP, A_TXRF, 0x00); /**< Duty cycle control selection */
		invalid += tda5340_command(device_number, WRITE_TO_CHIP, A_TXCFG, 0x40); /**< TX configuration register */
		invalid += tda5340_command(device_number, WRITE_TO_CHIP, A_TXBDRDIV0,
				0x76); /**< TX baudrate divider register 0. Fsys = 21948KHz */
		invalid += tda5340_command(device_number, WRITE_TO_CHIP, A_TXBDRDIV1,
				0x04); /**< TX baudrate divider register 1. Fsys = 21948KHz */
		invalid += tda5340_command(device_number, WRITE_TO_CHIP, A_TXCHOFFS0,
				0x00); /**< TX Channel Offset Register 0 */
		invalid += tda5340_command(device_number, WRITE_TO_CHIP, A_TXCHOFFS1,
				0x00); /**< TX Channel Offset Register 1 */
		invalid += tda5340_command(device_number, WRITE_TO_CHIP, A_TXDSHCFG0,
				0x00); /**< TX data shaping configuration register 0. ASK sloping division */
		invalid += tda5340_command(device_number, WRITE_TO_CHIP, A_TXDSHCFG1,
				0x00); /**< TX data shaping configuration register 1. Gaussian filter division */
		invalid += tda5340_command(device_number, WRITE_TO_CHIP, A_TXDSHCFG2,
				0x00); /**< TX data shaping configuration register 2. Gaussian filter division. ASK sloping division */
		invalid += tda5340_command(device_number, WRITE_TO_CHIP, A_TXPOWER0,
				0x00); /**< TX power configuration register 0 */
		invalid += tda5340_command(device_number, WRITE_TO_CHIP, A_TXPOWER1,
				0x1F); /**< TX power configuration register 1 */
		invalid += tda5340_command(device_number, WRITE_TO_CHIP, A_TXFDEV,
				0xD7); /**< TX frequency deviation register */

		// Setting TX-frequency to 868.0 MHz
		invalid += tda5340_command(device_number, WRITE_TO_CHIP, A_PLLINTC1,
				0x67); /**< PLL multi modulus divider integer value channel 1 */
		invalid += tda5340_command(device_number, WRITE_TO_CHIP, A_PLLFRAC0C1,
				0x95); /**< PLL fractional division ratio channel 1 */
		invalid += tda5340_command(device_number, WRITE_TO_CHIP, A_PLLFRAC1C1,
				0x09); /**< PLL fractional division ratio channel 1 */
		invalid += tda5340_command(device_number, WRITE_TO_CHIP, A_PLLFRAC2C1,
				0x10); /**< PLL fractional division ratio channel 1 */

		tda5340_interrupt_readout(device_number);
	}
