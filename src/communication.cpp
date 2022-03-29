#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include "headers/communication.hpp"


HTTPClient http;


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
        delay(500);
    }

    Serial.print("[success]\tWifi verbonden op: ");
    Serial.println(WiFi.localIP());
}


/**
 * @brief 
 * 
 * @param value
 */
void Communication::write_data(uint32_t value)
{
    Serial.print("[info]\t\tSchrijf data naar: ");
    Serial.println(this->get_host());

    String url = "https://" + this->get_host() + "/update?api_key=" + API_WRITE_KEY + "&field1=" + value;
    
    http.begin(url);
    http.GET();

    Serial.print("[success]\tData succesvol weggeschreven!");
}


/**
 * @brief 
 * 
 */
void Communication::read_data()
{

}


/**
 * @brief Functie voor het zetten van de host
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