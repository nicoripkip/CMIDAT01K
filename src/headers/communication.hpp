#ifndef __COMMUNICATION__API__
#define __COMMUNICATION__API__


#include <Arduino.h>
#include <WiFi.h>
#include <ArduinoJson.h>


//#define     SSID                "Tesla IoT"  
//#define     PASSWORD            "fsL6HgjN"
#define     SSID                "H369A432F1F" 
#define     PASSWORD            "3D6269C97CEA"
#define     API_WRITE_KEY       "PGDFE2DFL4O2V5NZ"
#define     API_READ_KEY        "C89CPM9HLSULP44W"


/**
 * @brief 
 * 
 */
class Communication
{
    private:
        String _host;
        uint16_t _port;

    public:
        Communication(String, uint16_t);
        void network_init();
        void write_data(uint8_t, uint32_t);
        void read_data(uint32_t, uint8_t, uint8_t);

        void set_host(String);
        String get_host();
        void set_port(uint16_t);
        uint16_t get_port();
};


#endif