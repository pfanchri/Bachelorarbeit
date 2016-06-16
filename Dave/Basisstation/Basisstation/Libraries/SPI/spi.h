/*
 * spi.h
 *
 *  Created on: Oct 1, 2015
 *      Author: pflaum
 */

#ifndef SPI_H_
#define SPI_H_

// ----------------------------------------
// Enter all the settings here
// ----------------------------------------

#define USIC                    0      // USIC-Module
#define USIC_CHANNEL            0      // USIC-Channel

#define NUMBER_OF_SPI_SLAVES    6

#define SPI_TX_PORT             1      // Port of Tx-Pin (MOSI): Take the x from Px.y
#define SPI_TX_PIN              7      // Portpin of Tx-Pin (MOSI): Take the y from Px.y
#define SPI_RX_PORT             1      // Port of Rx-Pin (MISO): Take the x from Px.y
#define SPI_RX_PIN              5      // Portpin of Rx-Pin (MISO): Take the y from Px.y
#define SPI_CLCK_PORT           1      // Port of Clock-Pin (SELO): Take the x from Px.y
#define SPI_CLCK_PIN            6     // Portpin of Clock-Pin (SELO): Take the y from Px.y

#define SPI_SELO_PORT_0         1      // Port of Slave-Select-Pin (SELO): Take the x from Px.y
#define SPI_SELO_PIN_0          11     // Portpin of Slave-Select-Pin (SELO): Take the y from Px.y
#define SPI_SELO_LINE_0         0      // Which slave for the chosen channel is used (0 ... 5) --> Take the z from UxCy.SELOz in the Reference

#if (NUMBER_OF_SPI_SLAVES > 1)
 #define SPI_SELO_PORT_1        1      // Port of Slave-Select-Pin (SELO): Take the x from Px.y
 #define SPI_SELO_PIN_1         8      // Portpin of Slave-Select-Pin (SELO): Take the y from Px.y
 #define SPI_SELO_LINE_1        1      // Which slave for the chosen channel is used (0 ... 5) --> Take the z from UxCy.SELOz in the Reference
#endif

#if (NUMBER_OF_SPI_SLAVES > 2)
 #define SPI_SELO_PORT_2    4          // Port of Slave-Select-Pin (SELO): Take the x from Px.y
 #define SPI_SELO_PIN_2     6          // Portpin of Slave-Select-Pin (SELO): Take the y from Px.y
 #define SPI_SELO_LINE_2    2          // Which slave for the chosen channel is used (0 ... 5) --> Take the z from UxCy.SELOz in the Reference
#endif

#if (NUMBER_OF_SPI_SLAVES > 3)
 #define SPI_SELO_PORT_3    4          // Port of Slave-Select-Pin (SELO): Take the x from Px.y
 #define SPI_SELO_PIN_3     5          // Portpin of Slave-Select-Pin (SELO): Take the y from Px.y
 #define SPI_SELO_LINE_3    3          // Which slave for the chosen channel is used (0 ... 5) --> Take the z from UxCy.SELOz in the Reference
#endif

#if (NUMBER_OF_SPI_SLAVES > 4)
 #define SPI_SELO_PORT_4    4          // Port of Slave-Select-Pin (SELO): Take the x from Px.y
 #define SPI_SELO_PIN_4     4          // Portpin of Slave-Select-Pin (SELO): Take the y from Px.y
 #define SPI_SELO_LINE_4    4          // Which slave for the chosen channel is used (0 ... 5) --> Take the z from UxCy.SELOz in the Reference
#endif

#if (NUMBER_OF_SPI_SLAVES > 5)
 #define SPI_SELO_PORT_5        4      // Port of Slave-Select-Pin (SELO): Take the x from Px.y
 #define SPI_SELO_PIN_5         3      // Portpin of Slave-Select-Pin (SELO): Take the y from Px.y
 #define SPI_SELO_LINE_5        5      // Which slave for the chosen channel is used (0 ... 5) --> Take the z from UxCy.SELOz in the Reference
#endif

#define SPI_ALT_OUT_CHANNEL     2      // Which alternative output are Tx, Selo and Clock (1 ... 4)
#define SPI_SELO_ACTIVE_HIGH    0      // Set 0 if slave select is active low
#define SPI_RX_CH_NR            0      // Which receiver channel for the chosen USIC and channel is used? Take the z from UxCy.DXzi in the Reference

#define SPI_BAUDRATE            100000 // Set baudrate
#define SPI_WORDLENGTH          8      // Set wordlength, maximum is 16
#define SPI_MSB_FIRST           1      // Set LSB-First (0) or MSB-First (anything else)

#define SPI_CPOL                1      // Clock idle level 1 or 0
#define SPI_CPHA                1      // Clock phase setting

// ----------------------------------------
// Don't change anything below this line!
// ----------------------------------------


extern XMC_USIC_CH_t *spi_master_ch;


#if ((SPI_CPOL == 0) && (SPI_CPHA == 0))
 #define SPI_CLK_MODE    XMC_USIC_CH_BRG_SHIFT_CLOCK_PASSIVE_LEVEL_0_DELAY_DISABLED
#endif

#if ((SPI_CPOL == 0) && (SPI_CPHA == 1))
 #define SPI_CLK_MODE    XMC_USIC_CH_BRG_SHIFT_CLOCK_PASSIVE_LEVEL_0_DELAY_ENABLED
#endif

#if ((SPI_CPOL == 1) && (SPI_CPHA == 0))
 #define SPI_CLK_MODE    XMC_USIC_CH_BRG_SHIFT_CLOCK_PASSIVE_LEVEL_1_DELAY_ENABLED
#endif

#if ((SPI_CPOL == 1) && (SPI_CPHA == 1))
 #define SPI_CLK_MODE    XMC_USIC_CH_BRG_SHIFT_CLOCK_PASSIVE_LEVEL_1_DELAY_DISABLED
#endif

void spi_init(XMC_USIC_CH_t *const channel);
void spi_transfer(XMC_USIC_CH_t *const channel, uint8_t selo, uint16_t *data_in, uint16_t *data_out, uint8_t length);
uint8_t spi_byte(XMC_USIC_CH_t *const channel, uint16_t data);

#define SPI_CHA_HELP(x, y)             CONCAT4(XMC_SPI, x, _CH, y)
#define SPI_CHANNEL      SPI_CHA_HELP(USIC, USIC_CHANNEL)
#define SPI_CH_INPUT_HELP(x)           CONCAT(XMC_SPI_CH_INPUT_DIN, x)
#define SPI_CH_INPUT     SPI_CH_INPUT_HELP(SPI_RX_CH_NR)
#define USIC_IN_HELP(x, y, z, r, s)    CONCAT10(USIC, x, _C, y, _DX, z, _P, r, _, s)
#define USIC_IN          USIC_IN_HELP(USIC, USIC_CHANNEL, SPI_RX_CH_NR, SPI_RX_PORT, SPI_RX_PIN)
#define ALT_OUT_HELP(x)                CONCAT(XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT, x)
#define SPI_ALT_OUT      ALT_OUT_HELP(SPI_ALT_OUT_CHANNEL)

#define SPI_TX_P         PORT(SPI_TX_PORT)
#define SPI_RX_P         PORT(SPI_RX_PORT)
#define SPI_CLCK_P       PORT(SPI_CLCK_PORT)

#define SPI_SELO_P_0     PORT(SPI_SELO_PORT_0)
#define SELO_LINE_0_HELP(x)    CONCAT(XMC_SPI_CH_SLAVE_SELECT_, x)
#define SELO_LINE_0      SELO_LINE_HELP(SPI_SELO_LINE_0)

#if (NUMBER_OF_SPI_SLAVES > 1)
 #define SPI_SELO_P_1    PORT(SPI_SELO_PORT_1)
 #define SELO_LINE_1_HELP(x)    CONCAT(XMC_SPI_CH_SLAVE_SELECT_, x)
 #define SELO_LINE_1     SELO_LINE_HELP(SPI_SELO_LINE_1)
#endif
#if (NUMBER_OF_SPI_SLAVES > 2)
 #define SPI_SELO_P_2    PORT(SPI_SELO_PORT_2)
 #define SELO_LINE_2_HELP(x)    CONCAT(XMC_SPI_CH_SLAVE_SELECT_, x)
 #define SELO_LINE_2     SELO_LINE_HELP(SPI_SELO_LINE_2)
#endif
#if (NUMBER_OF_SPI_SLAVES > 3)
 #define SPI_SELO_P_3    PORT(SPI_SELO_PORT_3)
 #define SELO_LINE_3_HELP(x)    CONCAT(XMC_SPI_CH_SLAVE_SELECT_, x)
 #define SELO_LINE_3     SELO_LINE_HELP(SPI_SELO_LINE_3)
#endif
#if (NUMBER_OF_SPI_SLAVES > 4)
 #define SPI_SELO_P_4    PORT(SPI_SELO_PORT_4)
 #define SELO_LINE_4_HELP(x)    CONCAT(XMC_SPI_CH_SLAVE_SELECT_, x)
 #define SELO_LINE_4     SELO_LINE_HELP(SPI_SELO_LINE_4)
#endif
#if (NUMBER_OF_SPI_SLAVES > 5)
 #define SPI_SELO_P_5    PORT(SPI_SELO_PORT_5)
 #define SELO_LINE_5_HELP(x)    CONCAT(XMC_SPI_CH_SLAVE_SELECT_, x)
 #define SELO_LINE_5     SELO_LINE_HELP(SPI_SELO_LINE_5)
#endif

#if SPI_SELO_ACTIVE_HIGH
 #define SPI_SLAVE_SEL_POLARITY    XMC_SPI_CH_SLAVE_SEL_SAME_AS_MSLS
#else
 #define SPI_SLAVE_SEL_POLARITY    XMC_SPI_CH_SLAVE_SEL_INV_TO_MSLS
#endif
#endif /* SPI_H_ */
