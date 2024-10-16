# Blynk_IoT
# Room Temperature Monitoring Over Internet with Blynk

This project allows you to monitor room temperature and humidity over the internet using the Blynk platform and an ESP32 microcontroller. The data is captured by a DHT11 sensor and displayed on the Blynk app in real time.

## Table of Contents
- [Introduction](#introduction)
- [Components Required](#components-required)
- [Circuit Diagram](#circuit-diagram)
- [Blynk App Setup](#blynk-app-setup)
- [Code](#code)
- [How It Works](#how-it-works)

## Introduction
Blynk is an IoT platform that controls microcontrollers like Arduino, ESP32, Raspberry Pi, and more over the internet. It allows for simple drag-and-drop creation of dashboards to display sensor data or control devices.

This project uses an ESP32 connected to a DHT11 temperature and humidity sensor to read and send data over Wi-Fi. The Blynk app, configured on your smartphone, displays the readings in real-time using gauges.

## Components Required
1. ESP32 Dev Board  
2. DHT11 Temperature & Humidity Sensor  
3. 10k Ohm Resistor  
4. Breadboard  
5. Jumper Wires

## Circuit Diagram
Refer to the following diagram for wiring:
- **DHT11 Sensor**:
  - VCC -> 3.3V (ESP32)
  - GND -> GND
  - Data -> GPIO (Pin 5 on ESP32)
- **Resistor**: Connect between Data and VCC

## Blynk App Setup

1. Download the Blynk app from the [Google Play Store](https://play.google.com) or [Apple Store](https://www.apple.com/app-store/).
2. Create an account in the Blynk app or use an existing Gmail account.
3. Start a **New Project** and name it according to your preference.
   - Select **ESP32 Dev Board** as the device.
   - Choose **Wi-Fi** as the connection type and click **Create**.
4. You will receive an **Authentication Token** via email, which will be used in the code later.
5. Add two gauge widgets in the app to display **Humidity** and **Temperature**:
   - For Humidity:
     - Pin: V5
     - Max Value: 100
   - For Temperature:
     - Pin: V6
     - Label: °C

## Code
Here is an example code to set up the ESP32 for reading temperature and humidity values and sending them to the Blynk app:

```cpp
#define BLYNK_PRINT Serial
#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <DHT.h>

char auth[] = "YourAuthToken";
char ssid[] = "YourWiFiSSID";
char pass[] = "YourWiFiPassword";

#define DHTPIN 5 // Pin where the DHT sensor is connected
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

BlynkTimer timer;

void sendSensorData() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  Blynk.virtualWrite(V5, h);
  Blynk.virtualWrite(V6, t);
}

void setup() {
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);
  dht.begin();
  timer.setInterval(2000L, sendSensorData);
}

void loop() {
  Blynk.run();
  timer.run();
}

