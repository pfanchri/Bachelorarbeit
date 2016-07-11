/*
 * relax_kit.h
 *
 *  Created on: Nov 5, 2015
 *      Author: pflaum
 */

#ifndef RELAX_KIT_H_
#define RELAX_KIT_H_

#define LED1_PORT       XMC_GPIO_PORT1
#define LED1_PIN        1
#define LED2_PORT       XMC_GPIO_PORT1
#define LED2_PIN        0
#define BUTTON1_PORT    XMC_GPIO_PORT1
#define BUTTON1_PIN     14
#define BUTTON2_PORT    XMC_GPIO_PORT1
#define BUTTON2_PIN     15

// Leave everything as it is from here on!

/* Initialise button pins as inputs with active pull-ups
 * interrupt != 0 activates pin change interrupt on ERU1_OGU0
 */
void button_init(uint8_t interrupt);

/* Initialise LEDs
 * Initialise LED-ports as push-pull-outputs in low-state
 */
void led_init(void);

/* Change LED-status simultaneously
 * Only the lower nibble of pattern matters
 * Bit 0: Turn on LED1
 * Bit 1: Turn off LED1
 * Bit 2: Turn on LED2
 * Bit 3: Turn off LED2
 *
 * Setting both for any LED bits means toggling its state
 * */
void led_change(uint8_t pattern);

#define LED1       LED1_PORT, LED1_PIN
#define LED2       LED2_PORT, LED2_PIN
#define BUTTON1    BUTTON1_PORT, BUTTON1_PIN
#define BUTTON2    BUTTON2_PORT, BUTTON2_PIN
#endif /* RELAX_KIT_H_ */
