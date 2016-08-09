/*
 * Header_general.h
 *
 *  Created on: Jun 13, 2016
 *      Author: Christof Pfannenmüller
 */

#ifndef HEADER_GENERAL_H_
#define HEADER_GENERAL_H_


//including all available Header files

#include <XMC4500.h>
#include <xmc_gpio.h>
#include <xmc_usic.h>
#include <xmc_spi.h>
#include <xmc_eru.h>
#include "Libraries/SPI/spi.h"
#include "Libraries/SPI/portmakros.h"
#include "Libraries/TDA5340-C/tda5340.h"
#include "Libraries/CRC/crcchk.h"
#include "Libraries/VirtualCOMPort/VirtualSerial.h"
#include "Libraries/VirtualCOMPort/COMtransfer.h"



#include <TDA.h>
#include <Led.h>


//TDA Macros

#define TDA_ALL		10
#define TDA1		0
#define TDA2		1
#define TDA3		2
#define TDA4		3
#define TDA5		4
#define TDA6		5

#define IRQ_PRIORITY_TDA1	5
#define IRQ_PRIORITY_TDA2	6
#define IRQ_PRIORITY_TDA3	7
#define IRQ_PRIORITY_TDA4	8
#define IRQ_PRIORITY_TDA5	9
#define IRQ_PRIORITY_TDA6	10


#define PORT_MOSI 	1
#define PIN_MOSI	7
#define PORT_MISO	1
#define PIN_MISO	5
#define PORT_SCK	1
#define PIN_SCK		6


#define PORT_NCS_TDA_1	XMC_GPIO_PORT1
#define PIN_NCS_TDA_1	11
#define PORT_NCS_TDA_2	XMC_GPIO_PORT1
#define PIN_NCS_TDA_2	8
#define PORT_NCS_TDA_3	XMC_GPIO_PORT4
#define PIN_NCS_TDA_3	6
#define PORT_NCS_TDA_4	XMC_GPIO_PORT4
#define PIN_NCS_TDA_4	5
#define PORT_NCS_TDA_5	XMC_GPIO_PORT4
#define PIN_NCS_TDA_5	4
#define PORT_NCS_TDA_6	XMC_GPIO_PORT4
#define PIN_NCS_TDA_6	3

#define PORT_P_ON_TDA_1	XMC_GPIO_PORT0
#define PIN_P_ON_TDA_1	2
#define PORT_P_ON_TDA_2	XMC_GPIO_PORT1
#define PIN_P_ON_TDA_2	9
#define PORT_P_ON_TDA_3	XMC_GPIO_PORT5
#define PIN_P_ON_TDA_3	5
#define PORT_P_ON_TDA_4	XMC_GPIO_PORT5
#define PIN_P_ON_TDA_4	4
#define PORT_P_ON_TDA_5	XMC_GPIO_PORT3
#define PIN_P_ON_TDA_5	7
#define PORT_P_ON_TDA_6	XMC_GPIO_PORT0
#define PIN_P_ON_TDA_6	9

#define PORT_PP0_TDA_1	XMC_GPIO_PORT0
#define PIN_PP0_TDA_1	5
#define PORT_PP0_TDA_2	XMC_GPIO_PORT1
#define PIN_PP0_TDA_2	2
#define PORT_PP0_TDA_3	XMC_GPIO_PORT5
#define PIN_PP0_TDA_3	7
#define PORT_PP0_TDA_4	XMC_GPIO_PORT5
#define PIN_PP0_TDA_4	1
#define PORT_PP0_TDA_5	XMC_GPIO_PORT3
#define PIN_PP0_TDA_5	10
#define PORT_PP0_TDA_6	XMC_GPIO_PORT0
#define PIN_PP0_TDA_6	1

#define PORT_PP1_TDA_1	XMC_GPIO_PORT0
#define PIN_PP1_TDA_1	4
#define PORT_PP1_TDA_2	XMC_GPIO_PORT1
#define PIN_PP1_TDA_2	1
#define PORT_PP1_TDA_3	XMC_GPIO_PORT5
#define PIN_PP1_TDA_3	6
#define PORT_PP1_TDA_4	XMC_GPIO_PORT5
#define PIN_PP1_TDA_4	2
#define PORT_PP1_TDA_5	XMC_GPIO_PORT3
#define PIN_PP1_TDA_5	9
#define PORT_PP1_TDA_6	XMC_GPIO_PORT0
#define PIN_PP1_TDA_6	0

#define PORT_PP2_TDA_1	XMC_GPIO_PORT0
#define PIN_PP2_TDA_1	3
#define PORT_PP2_TDA_2	XMC_GPIO_PORT1
#define PIN_PP2_TDA_2	0
#define PORT_PP2_TDA_3	XMC_GPIO_PORT2
#define PIN_PP2_TDA_3	6
#define PORT_PP2_TDA_4	XMC_GPIO_PORT2
#define PIN_PP2_TDA_4	1
#define PORT_PP2_TDA_5	XMC_GPIO_PORT3
#define PIN_PP2_TDA_5	2
#define PORT_PP2_TDA_6	XMC_GPIO_PORT0
#define PIN_PP2_TDA_6	10
//END of TDA Macros

//LED Macros

#define LED_ALL 0
#define LED1	1
#define LED2	2
#define LED3	3
#define LED4	4
#define LED5	5
#define LED6	6
#define LED7	7


#define PORT_LED_1	XMC_GPIO_PORT6
#define PIN_LED_1	0
#define PORT_LED_2	XMC_GPIO_PORT6
#define PIN_LED_2	1
#define PORT_LED_3	XMC_GPIO_PORT6
#define PIN_LED_3	2
#define PORT_LED_4	XMC_GPIO_PORT6
#define PIN_LED_4	3
#define PORT_LED_5	XMC_GPIO_PORT6
#define PIN_LED_5	4
#define PORT_LED_6	XMC_GPIO_PORT6
#define PIN_LED_6	5
#define PORT_LED_7	XMC_GPIO_PORT6
#define PIN_LED_7	6


void delay (unsigned long delay);
void init (void);
void general_test(void);
void send_serialnumber_to_com(void);

//global variables
extern uint8_t query_interruptTDA1_flag;
extern uint8_t query_interruptTDA2_flag;
extern uint8_t query_interruptTDA3_flag;
extern uint8_t query_interruptTDA4_flag;
extern uint8_t query_interruptTDA5_flag;
extern uint8_t query_interruptTDA6_flag;


#endif /* HEADER_GENERAL_H_ */
