/*
 * num_string_conversion.h
 *
 *  Created on: Aug 20, 2015
 *      Author: pflaum
 */

#ifndef NUM_STRING_CONVERSION_H_
#define NUM_STRING_CONVERSION_H_

uint8_t string_to_8bit(uint8_t *input);
void uint8_to_hex_string(uint8_t input, char *output);
void uint8_to_dec_string(uint8_t input, char *output);
void int8_to_dec_string(int8_t input, char *output);
#endif /* NUM_STRING_CONVERSION_H_ */
