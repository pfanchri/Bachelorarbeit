/*
 * TDA.h
 *
 *  Created on: Jun 22, 2016
 *      Author: christofpfannenmulle
 */

#ifndef TDA_H_
#define TDA_H_



/**
 * sets TDA(s) in give mode
 * Param TDA: 	0 -> all TDAs
 * 				1 -> TDA1
 * 				2 -> TDA2  ...
 * Param status:0 -> Power down mode
 * 				1 -> Sleep mode
 */
void set_TDA_status(uint8_t TDA, uint8_t status);




#endif /* TDA_H_ */
