/*
 * Led.h
 *
 *  Created on: Jun 22, 2016
 *      Author: christofpfannenmulle
 */

#ifndef LED_H_
#define LED_H_

/**
 * aktivates a specific led;
 * Param led: 	0 -> all leds
 * 1 -> first led(top of the bord)
 * ...
 * 7 -> last led
 */
void led_on(uint8_t led);


/**
 * deactivates a specific led;
 * Param led: 	0 -> all leds
 * 1 -> first led(top of the bord)
 * ...
 * 7 -> last led
 */
void led_off(uint8_t led);


#endif /* LED_H_ */
