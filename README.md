# 24_Smart_Voice-Air-Purifier
Hardware Comprehensive Course Design
# Home Smart Voice Air Purifier
This project is a comprehensive course design for a Home Smart Voice Air Purifier. The system aims to improve indoor air quality by detecting and purifying harmful substances such as formaldehyde, smoke, and dust.

## Overview
In modern life, people spend more time indoors, especially in closed spaces like bedrooms. However, indoor air pollution poses a threat to human health. To address this issue, we designed a smart voice-controlled air purifier that enhances air quality in enclosed spaces.

## Features
Voice Assistant: The device communicates with users through voice commands, such as "formaldehyde," "air," "humidity," etc., and provides voice feedback of sensor readings.
OLED Display: Real-time display of indoor air quality data collected by sensors.
Air Pollution Prediction Model: An internal control program with a neural network model predicts air pollution levels for the next unit of time based on historical data of temperature, humidity, and pollution. The air purifier is activated in advance when pollution is predicted to reach a threshold.
Automatic Control: The device automatically turns on or off the air purification function based on the predicted air quality.
Filter System: Built-in activated carbon filters and a fan to purify the air.

## Platform and Modules
Zynq Board: APduino development board kit.
PM2.5, PM1.0, PM10 Smoke Sensor: ZH03.
Formaldehyde Sensor Module: ZE08-CH2O.
Temperature and Humidity Sensor Module: DHT11.
2.42-inch OLED Display Module: 12864.
Air Outlet Motor.
TTS Text-to-Speech Module: CN-TTS.
Voice Recognition Module: LD3320.
