/*
 * num_string_conversion.c
 *
 *  Created on: Aug 20, 2015
 *      Author: pflaum
 */

#include "global.h"

/*
 * Evaluates the first two chars in an array as hexadecimals and calculates an 8-bit-value
 */
uint8_t string_to_8bit(uint8_t *input) {
	uint8_t uinp = 0;

	for (uint8_t i = 0; i < 2; i++) {
		input[i] |= 0x20;
		uinp    <<= 4;

		if (((input[i] >= 'a') && (input[i] <= 'f')) || ((input[i] >= '0') && (input[i] <= '9'))) {
			if (input[i] > '9') {
				uinp += input[i] - 'a' + 10;
			}
			else {
				uinp += input[i] - '0';
			}
		}
		else {
			return 0xFF;
		}
	}

	return uinp;
}

void uint8_to_hex_string(uint8_t input, char *output) {
	output[2] = 0;
	output[0] = (input >> 4);
	output[1] = (input & 0x0F);

	for (uint8_t i = 0; i < 2; i++) {
		if (output[i] < 10) {
			output[i] += '0';
		}
		else {
			output[i] += 'A' - 10;
		}
	}
}

void uint8_to_dec_string(uint8_t input, char *output) {
	uint8_t cntr = 1;

	if (input > 9) cntr = 2;

	if (input > 99) cntr = 3;

	output[cntr] = 0;

	for (uint8_t i = cntr; i; i--) {
		output[i - 1] = input % 10 + '0';
		input        /= 10;
	}
}

void int8_to_dec_string(int8_t input, char *output) {
	uint8_t cntr = 1;

	if (input < 0) {
		output[0] = '-';
		input     = -input;
		cntr     |= 0x80;
	}

	if (input > 9) cntr++;

	if (input > 99) cntr++;

	output[cntr & 0x7F]       = 0;
	output[(cntr & 0x7F) - 1] = 0;

	printf("\r\nCounterwert: %x\r\n\n\n", cntr);

	for (uint8_t i = (cntr & 0x7F) + ((cntr & 0x80) && 1); i > ((cntr & 0x80) && 1); i--) {
		output[i - 1] = input % 10 + '0';
		printf("%i: %c\n\r", i, output[i - 1]);
		input /= 10;
	}
}
