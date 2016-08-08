/*
 * COMtransfer.h
 *
 *  Created on: Jul 7, 2016
 *      Author: student06
 */

#ifndef LIBRARIES_VIRTUALCOMPORT_COMTRANSFER_H_
#define LIBRARIES_VIRTUALCOMPORT_COMTRANSFER_H_

void COM_wait_for_transfer(void);
void COM_send_int_as_string(uint32_t data);
void COM_send_string(const void* const string);

#endif /* LIBRARIES_VIRTUALCOMPORT_COMTRANSFER_H_ */
