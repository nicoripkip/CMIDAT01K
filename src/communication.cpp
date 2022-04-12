#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include "headers/communication.hpp"


#define     JSON_BUFFER_SIZE        2048

#define     CODE_SUCCESS            200
#define     CODE_ERROR_NOT_FOUND    404
#define     CODE_ERROR_BAD_GATEWAY  500

#define     MAX_RETRIES             20



HTTPClient http;
uint8_t retries_counter;


/**
 * @brief Construct a new Communication:: Communication object 
 * 
 * @param host 
 * @param port 
 */
Communication::Communication(String host, uint16_t port)
{
    this->set_host(host);
    this->set_port(port);
}


/**
 * @brief Construct a new Communication::network_init object
 * 
 */
void Communication::network_init()
{
    WiFi.mode(WIFI_STA);
    WiFi.begin(SSID, PASSWORD);

    while (WiFi.status() != WL_CONNECTED) {
        Serial.print(".");
        retries_counter++;
        delay(500);

        if (retries_counter >= MAX_RETRIES) {
            Serial.print("[error]\t\tKan niet verbinden met netwerk: ");
            Serial.println(SSID);
            break;
        }
    }

    Serial.print("[success]\tWifi verbonden op: ");
    Serial.println(WiFi.localIP());
}


/**
 * @brief 
 * 
 * @param field 
 * @param value 
 */
void Communication::write_data(uint8_t field, uint32_t value)
{
    Serial.print("[info]\t\tSchrijf data naar: ");
    Serial.println(this->get_host());

    String url = "https://" + this->get_host() + "/update?api_key=" + API_WRITE_KEY + "&field" + field + "=" + value;
    
    http.begin(url);
    uint32_t status = http.GET();

    switch (status) 
    {
        case CODE_SUCCESS:
            Serial.println("[success]\tData succesvol weggeschreven!");
            return;
        break;
        case CODE_ERROR_NOT_FOUND:
            Serial.println("[error]\t\tAPI endpoint niet gevonden!");
            return;
        break;
        case CODE_ERROR_BAD_GATEWAY:
            Serial.println("[error]\t\tServer niet online!");
            return;
        break;
        default: 
            Serial.print("[error]\t\tJe moet deze code maar zelf opzoeken! code: ");
            Serial.println(status);
            return;
        break;
    }
}


/**
 * @brief 
 * 
 * @param channel 
 * @param field 
 * @param max_read_results 
 */
void Communication::read_data(uint32_t channel, uint8_t field, uint8_t max_read_results = 2)
{
    Serial.print("[info]\t\tLees data van: ");
    Serial.print(this->get_host());

    String url = "https://" + this->get_host() + "/channels/" + channel + "/fields/" + field + ".json?results=" + max_read_results;

    http.begin(url);
    uint16_t status = http.GET();

    if (status == CODE_SUCCESS) 
    {
        Serial.print("[success]\tData succesvol opgehaalt: " + status);

        String response = http.getString();
        DynamicJsonDocument json_buffer(JSON_BUFFER_SIZE);
        DeserializationError json_decode_error = deserializeJson(json_buffer, response);

        if (json_decode_error) {
            Serial.println("[error]\t\tJson kan niet worden omgezet!");
        }
    } else if (status == CODE_ERROR_NOT_FOUND) {
        Serial.println("[error]\t\tAPI endpoint niet gevonden!");
        return;
    } else if (status == CODE_ERROR_BAD_GATEWAY) {
        Serial.println("[error]\t\tServer niet online!");
        return;
    } else {
        Serial.print("[error]\t\tJe moet deze code maar zelf opzoeken! code: ");
        Serial.println(status);
        return;
    }
}


/**
 * @brie
 * Functie voor het zetten van de host
 * 
 * @param host 
 */
void Communication::set_host(String host)
{
    this->_host = host;
}


/**
 * @brief Functie voor het ophalen van de host
 * 
 * @return String 
 */
String Communication::get_host()
{
    return this->_host;
}


/**
 * @brief Functie voor het zetten van de port
 * 
 * @param port 
 */
void Communication::set_port(uint16_t port)
{
    this->_port = port;
}


/**
 * @brief Functie voor het ophalen van de port
 * 
 * @return uint16_t 
 */
uint16_t Communication::get_port()
{
    return this->_port;
}