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


#define 	ENABLE_DISPLAY 						true
#define 	ENABLE_LORA 						true
#define 	ENABLE_SERIAL 						true
#define 	PABOOST 							true

#define 	BAUD_RATE 							115200
#define 	DEVICE_ADDRESS						0x05
#define		SCL_ADDRESS							0x0C
#define 	SDA_ADDRESS							0x0D

#define 	TC74_TEMPERATURE_SENSOR_ADDRESS 	0x4A
#define 	RELAY_PIN							0x20
#define 	LCD_SCREEN_ADDRESS 					0x27



const uint32_t license[4] = { 0xA13202B6,0x8B58DCC0,0x4E7F3DFD,0x6F51BFA3 };
const char devideID[13] = "dc2014f7c630";

bool state = false;
bool take_over_state = false;
int temperature_detected[10];
int temp_counter;
int toggle_flag = 0;


int TC74_TEMPERATURE_get();
void switch_fan_state();
int get_temp_average();


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

	int temp = TC74_TEMPERATURE_get();
	temperature_detected[temp_counter] = temp;
  	temp_counter++;

	if (temp_counter > 9) 
	{
		temp_counter = 0;
	}

	int temp_comp = get_temp_average();
	if (temp_comp > 26) 
	{
		toggle_flag = 1;
	} else if (temp_comp <= 25) 
	{
		toggle_flag = 0;
	}

	if (take_over_state == 1) 
	{
		switch_fan_state();
	}
	else 
	{
		digitalWrite(RELAY_PIN, state);
	}
}


/**
 * @brief Construct a new blynk write object
 * 
 */
BLYNK_WRITE(V0)
{
	state = !state;
}


/**
 * @brief Construct a new blynk write object
 * 
 */
BLYNK_WRITE(V2)
{
	take_over_state = !take_over_state;
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


/**
 * @brief Functie voor het toggelen van de ventilator
 * 
 */
void switch_fan_state()
{
  switch (toggle_flag) 
  {
    case 0: digitalWrite(RELAY_PIN, LOW); break;
    case 1: digitalWrite(RELAY_PIN, HIGH); break;
  }

  Serial.print("[info]\t\tStaat van de fan: ");
  Serial.println(toggle_flag);
}


/**
 * @brief Functie voor het verkrijgen van het gemiddelde van de temperatuur
 * 
 */
int get_temp_average()
{
  int i, t = 0;

  for (i = 0; i < 10; i++)
  {
    t += temperature_detected[i];
  }

  return t / 10;
}