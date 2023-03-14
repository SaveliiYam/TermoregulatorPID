#pragma once
#include <Arduino.h>
#include <GyverPID.h> 
#include <PIDtuner.h>
#include "thermometr.h"


struct Koefficients{
  float P = 0;
  float I = 0;
  float D = 0;
};

class TRM{
    private:
        byte _sck, _cs, _so;
        unsigned long _currentTimeTermoCouple;
        float _temperature;
        Koefficients koefficientsPID;
        float _temperatureNeed;
        GyverPID regulator;
        thermometr thermocouple;

    public:
        TRM(byte sck, byte cs, byte so); 
        float temperature();
        void PIDRegulatorInitialization();
        void getTemperature(float& temperature);
        void PIDTuneKoefficients();
        void heater(int valueHeat);
};





