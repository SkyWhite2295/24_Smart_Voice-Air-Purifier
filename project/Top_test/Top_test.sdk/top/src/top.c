/*
 * top.c
 *
 *  Created on: 2024��6��1��
 *      Author: asus
 */

#include <stdio.h>
#include <stdbool.h>
#include "oled.h"
#include "xil_io.h"
#include "xil_printf.h"
#include "xparameters.h"
#include "tts.h"
#include <time.h>
#include "asr.h"
#include "dht.h"
#include <stdlib.h>
#include "sleep.h"
#include "xil_types.h"
#include "xgpio.h"
#include "xgpiops.h"
#include "forcasth.h"
#define ARRAY_SIZE 12  // ���������������Ĵ�С���������Ϊ12
#define DATA_COUNT 10  // �洢10�����ݺ���д���

//������ֵ
#define THRESHOLD_H 10	//humidity_int
#define THRESHOLD_T 10	//temperature_int
#define THRESHOLD_25 10	//pm25
#define THRESHOLD_1 10	//pm1
#define THRESHOLD_10 8	//pm10
//
//typedef struct {
//    int humidity_int;
//    int temperature_int;
//    int pm25;
//    int pm1;
//    int pm10;
//} SensorData;

 SensorData sensor_data_array[ARRAY_SIZE];
 int store_count = 0;//��¼�洢�Ĵ���
int model_data=0;
// �洢���������ݵĺ���
void store_sensor_data() {
    if (store_count < ARRAY_SIZE) {
        sensor_data_array[store_count] = (SensorData){
            .humidity_int = Xil_In32(XPAR_DHT11_OUTDOOR_S00_AXI_BASEADDR),
            .temperature_int = Xil_In32(XPAR_DHT11_OUTDOOR_S00_AXI_BASEADDR + 8),
            .pm25 = Xil_In32(XPAR_PM_OUTDOOR_S00_AXI_BASEADDR),
            .pm1 = Xil_In32(XPAR_PM_OUTDOOR_S00_AXI_BASEADDR + 4),
            .pm10 = Xil_In32(XPAR_PM_OUTDOOR_S00_AXI_BASEADDR + 8)
        };
        store_count++;
    }
}


// ���Ԥ��ֵ�Ƿ����Ԥ����ֵ
int check_exceedance(SensorData prediction) {
	int humidity_int=Xil_In32(XPAR_DHT11_S00_AXI_BASEADDR);
	int temperature_int=Xil_In32(XPAR_DHT11_S00_AXI_BASEADDR+8);
	int pm25 = Xil_In32(XPAR_PM_OUTDOOR_S00_AXI_BASEADDR);//XPAR_PM_OUTDOOR_S00_AXI_BASEADDR // XPAR_PM_S00_AXI_BASEADDR
	int pm1  = Xil_In32(XPAR_PM_OUTDOOR_S00_AXI_BASEADDR+4);
	int pm10 = Xil_In32(XPAR_PM_OUTDOOR_S00_AXI_BASEADDR+8);
	//��OLED��ʾԤ��ֵ
	OLED_Clear();
		//ʵ��ֵ
		OLED_ShowNum(0,0,humidity_int,3,16);
		OLED_ShowNum(0,2,temperature_int,3,16);
	    OLED_ShowNum(30,0,pm1,3,16);
	    OLED_ShowNum(30,2,pm10,3,16);
	    OLED_ShowNum(30,4,pm25,3,16);

	    //Ԥ��ֵ
	    OLED_ShowNum(60,0,prediction.humidity_int,3,16);
	    OLED_ShowNum(60,2,prediction.temperature_int,3,16);
	    OLED_ShowNum(90,0,prediction.pm1,3,16);
	    OLED_ShowNum(90,2,prediction.pm10,3,16);
	    OLED_ShowNum(90,4,prediction.pm25,3,16);
	    sleep(20);

	    //�������ֵΪ1����ʾ������һ��Ԥ��ֵ��������ֵ
	    if(prediction.humidity_int > THRESHOLD_H){
	    	return 1;
	    }
	    if(prediction.temperature_int > THRESHOLD_T){
	    	return 1;
	    }
	    if(prediction.pm25 > THRESHOLD_25){
	    	return 1;
	    }
	    if(prediction.pm1 > THRESHOLD_1){
	    	return 1;
	    }
	    if(prediction.pm10 > THRESHOLD_10){
	    	return 1;
	    }
	    return 0;

}

// process_data����
int process_data() {
	int result;
    SensorData prediction1,prediction2,prediction3,prediction4,prediction;

    //����Ԥ�⺯������Ԥ��
    moving_average_predictions(sensor_data_array, ARRAY_SIZE, &prediction1);
    weighted_moving_average_prediction(sensor_data_array, ARRAY_SIZE, &prediction2);
    exponential_moving_average_prediction(sensor_data_array, ARRAY_SIZE, &prediction3);

    //model train
    SensorData raw_data[NUM_DATA_POINTS];
       Double_SensorData data[NUM_DATA_POINTS];

    	   generate_summer_indoor_data(raw_data, NUM_DATA_POINTS);


       convert_data_to_double(raw_data, data, NUM_DATA_POINTS);

       initialize_network();
       int i;
       // Training each model
       for ( i = 0; i < NUM_SENSORS; i++) {
           train_model(data, i, NUM_DATA_POINTS);
       }

       // Using the model to predict
       //typedef struct {
       //    int humidity_int;
       //    int temperature_int;
       //    int pm25;
       //    int pm1;
       //    int pm10;
       //} SensorData;
       Double_SensorData sample_input = {sensor_data_array[8].humidity_int, sensor_data_array[8].temperature_int, sensor_data_array[8].pm25, sensor_data_array[8].pm1, sensor_data_array[8].pm10}; //���սṹ��˳������
       Double_SensorData predictions = get_predictions(sample_input);

          // Convert double predictions to int and store them in result1
       convert_and_store_results(predictions, &prediction4);
       double distance1 = euclidean_distance(prediction4, prediction1);
           double distance2 = euclidean_distance(prediction4, prediction2);
           double distance3 = euclidean_distance(prediction4, prediction3);

           // �ҵ���С�ľ��벢ѡ����Ӧ�Ľ��
           double min_distance = distance1;
           prediction = prediction1;  // Ĭ��result1����ӽ���

           if (distance2 < min_distance) {
               min_distance = distance2;
               prediction = prediction2;
           }

           if (distance3 < min_distance) {
               min_distance = distance3;
               prediction = prediction3;
           }






    int c=check_exceedance(prediction4);
    if (c==1) {
        printf("Warning: Predicted values exceed expected thresholds.\n");
        result = 1;
    } else {
        printf("Info: Predicted values are within expected thresholds.\n");
        result = 0;
    }

    // ���ô洢������׼����һ�������ռ�
    store_count = 0;
    return result;
}


int main()
{
	Init_OLED();
	Init_TTS();

	static XGpio motor_Ptr;
    int XStatus;
    int count = 1;// ��ʼ��������Ϊ0

    XStatus = XGpio_Initialize(&motor_Ptr,XPAR_GPIO_0_DEVICE_ID);
    if(XST_SUCCESS != XStatus)
        print("GPIO INIT FAILED\n\r");
    XGpio_SetDataDirection(&motor_Ptr,1,0x00);

    XGpio_DiscreteWrite(&motor_Ptr,1,0);

    while (1) {
           // ÿ10���Ӵ洢һ�δ���������
//           if (count % DATA_COUNT == 0) {
    		if (count % 4 == 0) {
               store_sensor_data();
           }

           // ����洢��������10�����ݣ��������ݲ����ü�����������
           if (store_count >= DATA_COUNT) {
        	   int p=process_data();
        	   if(p == 1){
        		   OLED_Clear();
        		   OLED_ShowString(15,2,"warning",16);
        		   XGpio_DiscreteWrite(&motor_Ptr, 1, 1);
        		   sleep(10);
        	   }
        	   else if(p == 0){
        		   OLED_Clear();
        		   OLED_ShowString(15,2,"safe",16);
        		   XGpio_DiscreteWrite(&motor_Ptr, 1, 0);
        		   sleep(10);
        	   }else{XGpio_DiscreteWrite(&motor_Ptr, 1, 0);}
               count = 0; // ���ü������Ա��ٴο�ʼ�洢����
           }

           // ÿ1����ִ��һ��GPIO���ƺ�ASR����
           int status = Xil_In32(ASR_BASEADDR);
           Handle_ASR(status);

           count++; // ��ÿ��ѭ������ʱ����������
           sleep(1); // ÿ1��ִ��һ��ѭ��
       }

	return 0;
}