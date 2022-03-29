#include <heltec.h>
#include <Arduino.h>
#include <Wire.h>
#include "headers/communication.hpp"


#define 	ENABLE_DISPLAY 		true
#define 	ENABLE_LORA 		true
#define 	ENABLE_SERIAL 		true
#define 	PABOOST 			true

#define 	BAUD_RATE 			115200


const uint32_t license[4] = { 0xA13202B6,0x8B58DCC0,0x4E7F3DFD,0x6F51BFA3 };
const char devideID[13] = "dc2014f7c630";

Communication wifi("api.thingspeak.com", 80);

/**
 * @brief Functie voor het opzetten van het project
 * 
 */
void setup()
{
	Heltec.begin(ENABLE_DISPLAY, ENABLE_LORA, ENABLE_SERIAL, PABOOST);
	Serial.begin(BAUD_RATE);
	wifi.network_init();
}


/**
 * @brief Functie voor het continue blijven loopen op de chip
 * 
 */
void loop()
{
	// int t[20] = {23, 24, 253, 76, 43, 57, 24 ,3 ,4,53,35,2 ,3,4,53,3,3};

	// for (int i = 0;i < 20;i++) {
	// 	wifi.write_data(t[i]);
	// }
}