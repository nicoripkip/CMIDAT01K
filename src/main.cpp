#include <Arduino.h>
#include <heltec.h>


#define ENABLE_DISPLAY true
#define ENABLE_LORA true
#define ENABLE_SERIAL true
#define PABOOST true


/**
 * @brief 
 * 
 */
void setup() 
{
  // put your setup code here, to run once:
  Heltec.begin(ENABLE_DISPLAY, ENABLE_LORA, ENABLE_SERIAL, PABOOST);
}


/**
 * @brief 
 * 
 */
void loop() 
{
  // put your main code here, to run repeatedly:
}