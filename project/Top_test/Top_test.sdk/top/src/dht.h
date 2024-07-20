/*
 * dht.h
 *
 *  Created on: 2024��6��1��
 *      Author: asus
 */

#ifndef DHT_H_
#define DHT_H_

#include "xparameters.h"
#include "DHT11_IP.h"
#include "xil_printf.h"
#include "xil_io.h"
#include "xuartps.h"
#include "stdlib.h"
#include "time.h"
#include "stdio.h"
#include "oled.h"
#include "tts.h"

//#define BASE_TEMPERATURE_INT 26//�¶���������
//#define BASE_HUMIDITY_INT 34//ʪ����������
//#define BASE_TEMPERATURE_DEC 45//�¶�С������
//#define BASE_HUMIDITY_DEC 50//ʪ��С������
//#define RANGE 3//������Χ

void TH_read();
void ShowWS();

#endif /* DHT_H_ */
