/*
 * relax_kit.c
 *
 *  Created on: Nov 5, 2015
 *      Author: pflaum
 */

#include "global.h"

static void button2_interrupt_init(void) {
	const XMC_ERU_ETL_CONFIG_t p1_15_etl_config = {
		.input_a                = XMC_ERU_ETL_INPUT_A0,
		.source                 = XMC_ERU_ETL_SOURCE_A,
		.edge_detection         = XMC_ERU_ETL_EDGE_DETECTION_FALLING,
		.status_flag_mode       = XMC_ERU_ETL_STATUS_FLAG_MODE_HWCTRL,
		.enable_output_trigger  =                                   1,
		.output_trigger_channel = XMC_ERU_ETL_OUTPUT_TRIGGER_CHANNEL0 /* OGU0 */
	};
	XMC_ERU_ETL_Init(ERU1_ETL1, &p1_15_etl_config);

	const XMC_ERU_OGU_CONFIG_t p1_15_event_detection_config =
	{ .service_request = XMC_ERU_OGU_SERVICE_REQUEST_ON_TRIGGER };
	XMC_ERU_OGU_Init(ERU1_OGU0, &p1_15_event_detection_config);

	NVIC_SetPriority(ERU1_0_IRQn, 3U);
	NVIC_EnableIRQ(ERU1_0_IRQn);
}

void button_init(uint8_t interrupt) {
	// Button 1
	XMC_GPIO_CONFIG_t BUTTON1_CONFIG = { .mode = XMC_GPIO_MODE_INPUT_PULL_UP };
	XMC_GPIO_Init(BUTTON1, &BUTTON1_CONFIG);

	// Button 2
	XMC_GPIO_CONFIG_t BUTTON2_CONFIG = { .mode = XMC_GPIO_MODE_INPUT_PULL_UP };
	XMC_GPIO_Init(BUTTON2, &BUTTON2_CONFIG);

	if (interrupt) button2_interrupt_init(); }

void led_init(void) {
	// LED-Configurations
	XMC_GPIO_CONFIG_t LED1_CONFIG = { .mode = XMC_GPIO_MODE_OUTPUT_PUSH_PULL, .output_level = 0 };
	XMC_GPIO_Init(LED1, &LED1_CONFIG);
	XMC_GPIO_CONFIG_t LED2_CONFIG = { .mode = XMC_GPIO_MODE_OUTPUT_PUSH_PULL, .output_level = 0 };
	XMC_GPIO_Init(LED2, &LED2_CONFIG);
}

void led_change(uint8_t pattern) {
	LED1_PORT->OMR =
	   ((1 &&
	     (pattern & 1)) << LED1_PIN) |
	   ((1 &&
	     (pattern & 2)) << (LED1_PIN + 16)) |
	   ((1 && (pattern & 4)) << LED2_PIN) | ((1 && (pattern & 8)) << (LED2_PIN + 16));
}
