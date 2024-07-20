/*
 * dht.h
 *
 *  Created on: 2024年6月1日
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

//#define BASE_TEMPERATURE_INT 26//温度整数数据
//#define BASE_HUMIDITY_INT 34//湿度整数数据
//#define BASE_TEMPERATURE_DEC 45//温度小数数据
//#define BASE_HUMIDITY_DEC 50//湿度小数数据
//#define RANGE 3//波动范围

void TH_read();
void ShowWS();

#endif /* DHT_H_ */
