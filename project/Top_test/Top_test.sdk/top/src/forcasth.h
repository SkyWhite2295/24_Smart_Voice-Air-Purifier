/*
 * forcasth.h
 *
 *  Created on: 2024年6月6日
 *      Author: admin
 */

#ifndef FORCASTH_H_
#define FORCASTH_H_
#define NUM_SENSORS 5
#define NUM_DATA_POINTS 100
#define LEARNING_RATE 0.0001
#define NUM_ITERATIONS 10


#endif /* FORCASTH_H_ */
/*
 * forcast.c
 *
 *  Created on: 2024年6月6日
 *      Author: admin
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
    double humidity;
    double temperature;
    double pm25;
    double pm1;
    double pm10;
} Double_SensorData;


typedef struct {
    int humidity_int;
    int temperature_int;
    int pm25;
    int pm1;
    int pm10;
} SensorData;
// 浮点类型的传感器数据结构体

// 移动平均预测函数
void moving_average_predictions(SensorData *data, int size, SensorData *prediction);


void weighted_moving_average_prediction(SensorData *data, int size, SensorData *prediction) ;


void exponential_moving_average_prediction(SensorData *data, int size, SensorData *prediction);


// 生成随机测试数据
void generate_summer_indoor_data(SensorData *data, int size) ;

void convert_data_to_double(SensorData *raw_data, Double_SensorData *data, int size) ;



void initialize_network() ;
double predict(int index, Double_SensorData input) ;
void train_model(Double_SensorData *data, int target_index, int size) ;

void print_predictions(Double_SensorData input) ;

double my_round(double x);
double my_pow(double base, int exp) ;
double my_sqrt(double x);

Double_SensorData get_predictions(Double_SensorData input);
void convert_and_store_results(Double_SensorData predictions, SensorData *result);
double euclidean_distance(SensorData a, SensorData b);

