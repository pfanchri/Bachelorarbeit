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
#include "Libraries/SPI/spi.h"
#include "Libraries/SPI/portmakros.h"
#include "Libraries/TDA5340-C/tda5340.h"

#include <TDA.h>
#include <Led.h>


//TDA Macros

#define PORT_MOSI 	1
#define PIN_MOSI	7
#define PORT_MISO	1
#define PIN_MISO	5
#define PORT_SCK	1
#define PIN_SCK		6


#define PORT_NCS_TDA_1	1
#define PIN_NCS_TDA_1	11
#define PORT_NCS_TDA_2	1
#define PIN_NCS_TDA_2	8
#define PORT_NCS_TDA_3	4
#define PIN_NCS_TDA_3	6
#define PORT_NCS_TDA_4	4
#define PIN_NCS_TDA_4	5
#define PORT_NCS_TDA_5	4
#define PIN_NCS_TDA_5	4
#define PORT_NCS_TDA_6	4
#define PIN_NCS_TDA_6	3

#define PORT_P_ON_TDA_1	0
#define PIN_P_ON_TDA_1	2
#define PORT_P_ON_TDA_2	1
#define PIN_P_ON_TDA_2	8
#define PORT_P_ON_TDA_3	5
#define PIN_P_ON_TDA_3	5
#define PORT_P_ON_TDA_4	5
#define PIN_P_ON_TDA_4	4
#define PORT_P_ON_TDA_5	3
#define PIN_P_ON_TDA_5	7
#define PORT_P_ON_TDA_6	0
#define PIN_P_ON_TDA_6	9

#define PORT_PP0_TDA_1	0
#define PIN_PP0_TDA_1	5
#define PORT_PP0_TDA_2	1
#define PIN_PP0_TDA_2	2
#define PORT_PP0_TDA_3	5
#define PIN_PP0_TDA_3	7
#define PORT_PP0_TDA_4	5
#define PIN_PP0_TDA_4	1
#define PORT_PP0_TDA_5	3
#define PIN_PP0_TDA_5	10
#define PORT_PP0_TDA_6	0
#define PIN_PP0_TDA_6	1

#define PORT_PP1_TDA_1	0
#define PIN_PP1_TDA_1	4
#define PORT_PP1_TDA_2	1
#define PIN_PP1_TDA_2	1
#define PORT_PP1_TDA_3	5
#define PIN_PP1_TDA_3	6
#define PORT_PP1_TDA_4	5
#define PIN_PP1_TDA_4	2
#define PORT_PP1_TDA_5	3
#define PIN_PP1_TDA_5	9
#define PORT_PP1_TDA_6	0
#define PIN_PP1_TDA_6	0

#define PORT_PP2_TDA_1	0
#define PIN_PP2_TDA_1	3
#define PORT_PP2_TDA_2	1
#define PIN_PP2_TDA_2	0
#define PORT_PP2_TDA_3	2
#define PIN_PP2_TDA_3	6
#define PORT_PP2_TDA_4	2
#define PIN_PP2_TDA_4	1
#define PORT_PP2_TDA_5	3
#define PIN_PP2_TDA_5	2
#define PORT_PP2_TDA_6	0
#define PIN_PP2_TDA_6	10
//END of TDA Macros

//LED Macros
#define PORT_LED_1	6
#define PIN_LED_1	0
#define PORT_LED_2	6
#define PIN_LED_2	1
#define PORT_LED_3	6
#define PIN_LED_3	2
#define PORT_LED_4	6
#define PIN_LED_4	3
#define PORT_LED_5	6
#define PIN_LED_5	4
#define PORT_LED_6	6
#define PIN_LED_6	5
#define PORT_LED_7	6
#define PIN_LED_7	6


void delay ();
void init ();


#endif /* HEADER_GENERAL_H_ */
