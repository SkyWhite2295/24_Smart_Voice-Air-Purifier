/*
 * forcasth.h
 *
 *  Created on: 2024年6月6日
 *      Author: admin
 */

#ifndef FORCASTH_H_
#define FORCASTH_H_



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
#define NUM_SENSORS 5
#define NUM_DATA_POINTS 1000
#define LEARNING_RATE 0.0001
#define NUM_ITERATIONS 100
#include "forcasth.h"
// 浮点类型的传感器数据结构体
#include<math.h>
#include"math.h"
// 移动平均预测函数
void moving_average_predictions(SensorData *data, int size, SensorData *prediction) {
    int sum_humidity = 0;
    int sum_temperature = 0;
    int sum_pm25 = 0;
    int sum_pm1 = 0;
    int sum_pm10 = 0;
    int i;

    for (i = 0; i < size; ++i) {
        sum_humidity += data[i].humidity_int;
        sum_temperature += data[i].temperature_int;
        sum_pm25 += data[i].pm25;
        sum_pm1 += data[i].pm1;
        sum_pm10 += data[i].pm10;
    }

    // 计算平均值
    prediction->humidity_int = sum_humidity / size;
    prediction->temperature_int = sum_temperature / size;
    prediction->pm25 = sum_pm25 / size;
    prediction->pm1 = sum_pm1 / size;
    prediction->pm10 = sum_pm10 / size;
}

void weighted_moving_average_prediction(SensorData *data, int size, SensorData *prediction) {
    double total_weight = 0;
    double weights[size];
    int i;
    // 设置权重，例如线性增长的权重
    for ( i = 0; i < size; i++) {
        weights[i] = i + 1;
        total_weight += weights[i];
    }

    double sum_humidity = 0;
    double sum_temperature = 0;
    double sum_pm25 = 0;
    double sum_pm1 = 0;
    double sum_pm10 = 0;

    for ( i = 0; i < size; i++) {
        sum_humidity += data[i].humidity_int * weights[i];
        sum_temperature += data[i].temperature_int * weights[i];
        sum_pm25 += data[i].pm25 * weights[i];
        sum_pm1 += data[i].pm1 * weights[i];
        sum_pm10 += data[i].pm10 * weights[i];
    }

    // 计算加权平均
    prediction->humidity_int = (int)(sum_humidity / total_weight);
    prediction->temperature_int = (int)(sum_temperature / total_weight);
    prediction->pm25 = (int)(sum_pm25 / total_weight);
    prediction->pm1 = (int)(sum_pm1 / total_weight);
    prediction->pm10 = (int)(sum_pm10 / total_weight);
}

void exponential_moving_average_prediction(SensorData *data, int size, SensorData *prediction) {
    // 选择一个平滑系数alpha，一般取0.2或0.3
    double alpha = 0.2;

    int last_humidity = data[0].humidity_int;
    int last_temperature = data[0].temperature_int;
    int last_pm25 = data[0].pm25;
    int last_pm1 = data[0].pm1;
    int last_pm10 = data[0].pm10;
    int i;
    for ( i = 1; i < size; i++) {
        last_humidity = (int)(alpha * data[i].humidity_int + (1 - alpha) * last_humidity);
        last_temperature = (int)(alpha * data[i].temperature_int + (1 - alpha) * last_temperature);
        last_pm25 = (int)(alpha * data[i].pm25 + (1 - alpha) * last_pm25);
        last_pm1 = (int)(alpha * data[i].pm1 + (1 - alpha) * last_pm1);
        last_pm10 = (int)(alpha * data[i].pm10 + (1 - alpha) * last_pm10);
    }

    prediction->humidity_int = last_humidity;
    prediction->temperature_int = last_temperature;
    prediction->pm25 = last_pm25;
    prediction->pm1 = last_pm1;
    prediction->pm10 = last_pm10;
}


// 生成随机测试数据
void generate_summer_indoor_data(SensorData *data, int size) {
	int i;
    for ( i = 0; i < size; ++i) {
        data[i].humidity_int = rand() % 21 + 40;       // 湿度在40%到60%
        data[i].temperature_int = rand() % 5 + 22;     // 温度在22°C到26°C
        data[i].pm25 = rand() % 30 + 5;                // PM2.5在5到34微克/立方米
        data[i].pm1 = rand() % 25 + 1;                 // PM1在1到25微克/立方米
        data[i].pm10 = rand() % 30 + 5;                // PM10在5到34微克/立方米
    }
}

void convert_data_to_double(SensorData *raw_data, Double_SensorData *data, int size) {
	int i;
    for ( i = 0; i < size; i++) {
        data[i].humidity = (double)raw_data[i].humidity_int;
        data[i].temperature = (double)raw_data[i].temperature_int;
        data[i].pm25 = (double)raw_data[i].pm25;
        data[i].pm1 = (double)raw_data[i].pm1;
        data[i].pm10 = (double)raw_data[i].pm10;
    }
}

double weights[NUM_SENSORS][NUM_SENSORS]; // 每个指标一个权重向量
double biases[NUM_SENSORS]; // 每个指标一个偏置

void initialize_network() {
	int i,j;
    for ( i = 0; i < NUM_SENSORS; i++) {
        biases[i] = (double)rand() / RAND_MAX * 2.0 - 1.0;
        for ( j = 0; j < NUM_SENSORS; j++) {
            weights[i][j] = (double)rand() / RAND_MAX * 2.0 - 1.0;
        }
    }
}

double predict(int index, Double_SensorData input) {
    return biases[index]
        + input.humidity * weights[index][0]
        + input.temperature * weights[index][1]
        + input.pm25 * weights[index][2]
        + input.pm1 * weights[index][3]
        + input.pm10 * weights[index][4];
}

void train_model(Double_SensorData *data, int target_index, int size) {
	int iter,i,j;
    for ( iter = 0; iter < NUM_ITERATIONS; iter++) {
        for ( i = 0; i < size; i++) {
            double predicted = predict(target_index, data[i]);
            double actual = ((double *)&data[i])[target_index]; // Using pointer arithmetic to access array
            double error = actual - predicted;

            biases[target_index] += LEARNING_RATE * error;
            for ( j = 0; j < NUM_SENSORS; j++) {
                weights[target_index][j] += LEARNING_RATE * error * ((double *)&data[i])[j];
            }
        }
    }
}

void print_predictions(Double_SensorData input) {
    printf("Predictions: Humidity %.2f, Temperature %.2f, PM2.5 %.2f, PM1 %.2f, PM10 %.2f\n",
           predict(0, input), predict(1, input), predict(2, input), predict(3, input), predict(4, input));
}
Double_SensorData get_predictions(Double_SensorData input) {
    Double_SensorData result;
    result.humidity = predict(0, input);
    result.temperature = predict(1, input);
    result.pm25 = predict(2, input);
    result.pm1 = predict(3, input);
    result.pm10 = predict(4, input);
    return result;
}
double my_round(double x) {
    if (x < 0.0)
        return (double)((int)(x - 0.5));
    else
        return (double)((int)(x + 0.5));
}

double my_pow(double base, int exp) {
    double result = 1.0;
    int i;
    for ( i = 0; i < abs(exp); i++) {
        result *= base;
    }
    if (exp < 0) {
        result = 1.0 / result;
    }
    return result;
}

double my_sqrt(double x) {
    if (x <= 0) return 0;
    double last = 0.0;
    double res = 1.0;
    while (res != last) {
        last = res;
        res = (res + x / res) / 2;
    }
    return res;
}
void convert_and_store_results(Double_SensorData predictions, SensorData *result) {
    result->humidity_int = (int)my_round(predictions.humidity);
    result->temperature_int = (int)my_round(predictions.temperature);
    result->pm25 = (int)my_round(predictions.pm25);
    result->pm1 = (int)my_round(predictions.pm1);
    result->pm10 = (int)my_round(predictions.pm10);
}

double euclidean_distance(SensorData a, SensorData b) {
    return my_sqrt(my_pow(a.humidity_int - b.humidity_int, 2) +
                my_pow(a.temperature_int - b.temperature_int, 2) +
                my_pow(a.pm25 - b.pm25, 2) +
                my_pow(a.pm1 - b.pm1, 2) +
                my_pow(a.pm10 - b.pm10, 2));
}
