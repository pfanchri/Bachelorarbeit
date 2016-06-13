/*
 * portmakros.h
 *
 *  Created on: 25.04.2013
 *      Author: Felix
 */

#ifndef PORTMAKROS_H_
#define PORTMAKROS_H_

// Definitions for IO-Port-Makros
#define   CONCAT(x, y)                              x ## y
#define   CONCAT4(x, y, z, r)                       x ## y ## z ## r
#define   CONCAT10(a, b, c, d, e, f, g, h, i, j)    a ## b ## c ## d ## e ## f ## g ## h ## i ## j
#define   PORT(x)                                   CONCAT(XMC_GPIO_PORT, x)
#endif /* PORTMAKROS_H_ */
