/*
 * asr.c
 *
 *  Created on: 2024年6月1日
 *      Author: asus
 */

#include "asr.h"


int front_status = -1;


void Handle_ASR(int status){
	if(status != front_status){
		front_status = status;
		if(status == 1){
			u8 SendBuffer[] = "我在";
			Send_TTS(SendBuffer,sizeof SendBuffer);
		}else if(status == 2){
			ShowWS();
		}else if(status == 3){
			ShowPM();
		}else if(status == 4){
			ShowJQ();
		}
	}

//	Xil_Out32(ASR_BASEADDR,0);
}
