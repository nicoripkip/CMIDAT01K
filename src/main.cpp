#define BLYNK_DEBUG
#define BLYNK_PRINT Serial
#define BLYNK_TEMPLATE_ID "TMPL20Nz6Wmh"
#define BLYNK_DEVICE_NAME "VentilatorOpNetwerk"
#define BLYNK_AUTH_TOKEN "KICaLY4BdlVoZFauetvplH9upv7-mBqX"


#include <heltec.h>
#include <Arduino.h>
#include <Wire.h>
#include <Blynk.h>
#include <BlynkSimpleEsp32.h>
#include "headers/communication.hpp"


#define 	ENABLE_DISPLAY 		true
#define 	ENABLE_LORA 		true
#define 	ENABLE_SERIAL 		true
#define 	PABOOST 			true

#define 	BAUD_RATE 			115200
#define 	DEVICE_ADDRESS		5
#define		SCL_ADDRESS			0xC
#define 	SDA_ADDRESS			0x0D

#define TC74_TEMPERATURE_SENSOR_ADDRESS 0x4A
#define RELAY_PIN						0x20



const uint32_t license[4] = { 0xA13202B6,0x8B58DCC0,0x4E7F3DFD,0x6F51BFA3 };
const char devideID[13] = "dc2014f7c630";
Communication wifi("api.thingspeak.com", 80);
int data;


int TC74_TEMPERATURE_get();


/**
 * @brief Functie voor het opzetten van het project
 * 
 */
void setup()
{
	Heltec.begin(ENABLE_DISPLAY, ENABLE_LORA, ENABLE_SERIAL, PABOOST);
	Serial.begin(BAUD_RATE);
	// wifi.network_init();

	pinMode(RELAY_PIN, OUTPUT);

	Blynk.begin(BLYNK_AUTH_TOKEN, SSID, PASSWORD);
	Wire.begin(SDA_ADDRESS, SCL_ADDRESS);
}


/**
 * @brief Functie voor het continue blijven loopen op de chip
 * 
 */
void loop()
{
	Blynk.run();

	digitalWrite(RELAY_PIN, HIGH);
	delay(500);
	digitalWrite(RELAY_PIN, LOW);
	delay(500);

	int temp = TC74_TEMPERATURE_get();
}


/**
 * @brief Functie voor het opzetten van de TC74 sensor
 * 
 */
int TC74_TEMPERATURE_get()
{
  Wire.beginTransmission(TC74_TEMPERATURE_SENSOR_ADDRESS);
  Wire.write(0x00);;

  Wire.requestFrom(TC74_TEMPERATURE_SENSOR_ADDRESS, 1);
  int temperature = Wire.read();

  Wire.endTransmission(true);

  Blynk.virtualWrite(V1, temperature);

  Serial.print("[info]\t\tDe temperatuur is: ");
  Serial.println(temperature);

  return temperature;
}