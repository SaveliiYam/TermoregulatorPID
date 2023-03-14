#pragma once
#include <Arduino.h>

class thermometr{
    private:
        int8_t _sck, _cs, _so;
        uint8_t spiread(void);
    public:
        void getParameters(byte sck, byte cs, byte so);
        float readCelsius();
        float readKelvin();
        float readFahrenheit();
};