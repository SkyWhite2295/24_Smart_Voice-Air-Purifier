/*
 * tts.c
 *
 *  Created on: 2024年6月1日
 *      Author: asus
 */

#include "tts.h"
#include "xil_io.h"

void Send_TTS(u8 SendBuffer[], int size){
	int i;
	Xil_Out32(UART_TX_REG2,0);
	int status = 1;
	for(i=0;i<size;i++){
		Xil_Out32(UART_TX_REG2,0);
		while(!status){
			status = Xil_In32(UART_TX_REG1);
		}
		Xil_Out32(UART_TX_REG0,SendBuffer[i]);
		Xil_Out32(UART_TX_REG2,1);
		status = 0;
	}

	Xil_Out32(UART_TX_REG2,0);
	sleep(1);
}

void Init_TTS(){
	u8 SendBuffer[] = "你,你好,我是王逸远";
	Send_TTS(SendBuffer,sizeof SendBuffer);
}

