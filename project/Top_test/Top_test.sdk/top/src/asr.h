/*
 * asr.h
 *
 *  Created on: 2024��6��1��
 *      Author: asus
 */

#ifndef ASR_H_
#define ASR_H_
#include "tts.h"
#include "xparameters.h"
#include "dht.h"
#include "pm.h"
#include "jq.h"
#define ASR_BASEADDR XPAR_ASR_S00_AXI_BASEADDR




void Handle_ASR(int status);


#endif /* ASR_H_ */
