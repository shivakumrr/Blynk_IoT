/******************************************************************
Room Temperature Over Internet With BLYNK
-----------------------------------------------------

* Description:
-------------
Blynk is an IoT Platform to control Arduino, Raspberry Pi, NodeMCU and other microcontrollers over the Internet.

* Purpose of this expriment:
--------------------------
  Display the sensor readings from DHT11

@version 1.0
@date July, 2021
@author tru-iot workgroup, Entuple Technologies

******************************************************************/
/* -The first thing you have to do is include the required libraries.
   -Now define your DHT pin, here I am using GPIO 4 so I will include pin 4.
   -Enter your Authentication token and your network credentials inside double inverted commas.
   -In void setup() function, we will initialize the baud rate.
   -*/
#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <DHT.h>

#define DHTPIN 4          // What digital pin we're connected to
// Uncomment whatever type you're using!
#define DHTTYPE DHT11     // DHT 11


DHT dht(DHTPIN, DHTTYPE);
// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).

char auth[] = " ";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = " ";
char pass[] = " ";

BlynkTimer timer;

void setup()
{
  // Debug console
  Serial.begin(9600);

  Blynk.begin(auth, ssid, pass);
  // You can also specify server:
  //Blynk.begin(auth, ssid, pass, "blynk-cloud.com", 80);
  //Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8080);
  
  dht.begin();
  
  // Setup a function to be called every second
  timer.setInterval(1000L, sendSensor);
}
/*-Loop function executes repeatedly
-In the loop function include Blynk.run() command.*/
void loop()
{
  Blynk.run();
  timer.run();
}
/*function to read the sensor readings from DHT11
 * read humudity and temperature readings
 * if no value is received print failed to read
 * vitualwrite the data to pin v5 and v6
 */
void sendSensor()
{
  float h = dht.readHumidity();
  float t = dht.readTemperature(); // or dht.readTemperature(true) for Fahrenheit
  
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(V5, h);
  Blynk.virtualWrite(V6, t);
}
