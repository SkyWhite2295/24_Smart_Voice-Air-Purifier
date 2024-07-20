/*
 * dht.c
 *
 *  Created on: 2024年6月1日
 *      Author: asus
 */

#include "dht.h"



void ShowWS(){
	OLED_Clear();


	int humidity_int=Xil_In32(XPAR_DHT11_S00_AXI_BASEADDR);
	int humidity_dec=Xil_In32(XPAR_DHT11_S00_AXI_BASEADDR+4);
	int temperature_int=Xil_In32(XPAR_DHT11_S00_AXI_BASEADDR+8);
	int temperature_dec=Xil_In32(XPAR_DHT11_S00_AXI_BASEADDR+12);


	////////////////////////////////////////////////////////////////////////
	OLED_ShowChinese(5,1,7,16);
	OLED_ShowChinese(25,1,8,16);
	OLED_ShowChar(45,1,':',16);
	OLED_ShowNum(60,1,temperature_int,2,16);
	OLED_ShowChar(80,1,'.',16);
	OLED_ShowNum(90,1,temperature_dec,2,16);

	OLED_ShowChinese(5,4,9,16);
	OLED_ShowChinese(25,4,10,16);
	OLED_ShowChar(45,4,':',16);
	OLED_ShowNum(60,4,humidity_int,2,16);
	OLED_ShowChar(80,4,'.',16);
	OLED_ShowNum(90,4,humidity_dec,2,16);

	u8 SendBuffer[] = "当前的温度为";
	Send_TTS(SendBuffer,sizeof SendBuffer);
	u8 shidu_zhengshu_shiwei=(u8)(humidity_int/10 + 48);
	u8 shidu_zhengshu_gewei=(u8)(humidity_int%10+ 48);

	u8 shidu_xiaoshu_shiwei=(u8)(humidity_dec/10+ 48);
	u8 shidu_xiaoshu_gewei=(u8)(humidity_dec%10+ 48);

	u8 wendu_zhengshu_shiwei=(u8)(temperature_int/10+ 48);
	u8 wendu_zhengshu_gewei=(u8)(temperature_int%10+ 48);

	u8 wendu_xiaoshu_shiwei=(u8)(temperature_dec/10+ 48);
	u8 wendu_xiaoshu_gewei=(u8)(temperature_dec%10+ 48);

	Send_TTS(&wendu_zhengshu_shiwei,sizeof wendu_zhengshu_shiwei);

	u8 SendBuffer2[] = "十";
	Send_TTS(SendBuffer2,sizeof SendBuffer2);

	Send_TTS(&wendu_zhengshu_gewei,sizeof wendu_zhengshu_gewei);
//
	u8 SendBuffer3[] = "点";
	Send_TTS(SendBuffer3,sizeof SendBuffer3);
//
	Send_TTS(&wendu_xiaoshu_shiwei,sizeof wendu_xiaoshu_shiwei);
	Send_TTS(&wendu_xiaoshu_gewei,sizeof wendu_xiaoshu_gewei);

	u8 SendBuffer4[] = "摄氏度";
	Send_TTS(SendBuffer4,sizeof SendBuffer4);

	u8 SendBuffer5[] = "当前的湿度为";
	Send_TTS(SendBuffer5,sizeof SendBuffer5);

	Send_TTS(&shidu_zhengshu_shiwei,sizeof shidu_zhengshu_shiwei);
	Send_TTS(SendBuffer2,sizeof SendBuffer2);
	Send_TTS(&shidu_zhengshu_gewei,sizeof shidu_zhengshu_gewei);
	Send_TTS(SendBuffer3,sizeof SendBuffer3);
	Send_TTS(&shidu_xiaoshu_shiwei,sizeof shidu_xiaoshu_shiwei);
	Send_TTS(&shidu_xiaoshu_gewei,sizeof shidu_xiaoshu_gewei);




}
