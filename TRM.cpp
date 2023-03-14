#include "TRM.h"


TRM::TRM(byte sck, byte cs, byte so){
    _sck = sck;
    _cs = cs;
    _so = so;
    thermocouple.getParameters(_sck, _cs, _so);
    GyverPID regulator(koefficientsPID.P, koefficientsPID.I, koefficientsPID.D, 400);
}

float TRM::temperature(){
    if(millis() - _currentTimeTermoCouple >= 400){
        _temperature = thermocouple.readCelsius();
    }
    return _temperature;
}

void TRM::PIDRegulatorInitialization(){
    regulator.setDirection(NORMAL);
    regulator.setLimits(0, 255);
    regulator.setpoint = _temperatureNeed;
}

void TRM::getTemperature(float& temperature){
    _temperatureNeed = temperature;
}

void TRM::PIDTuneKoefficients(){
    PIDtuner tuner;
    tuner.setParameters(NORMAL, 130, 10, 2000, 1, 2000, 400); //надо исправить числа
    while(tuner.getAccuracy() <= 96){
        tuner.setInput(temperature());
        tuner.compute();
        heater(tuner.getOutput());
    }
    koefficientsPID.P = tuner.getPID_p();
    koefficientsPID.I = tuner.getPID_i();
    koefficientsPID.D = tuner.getPID_d();
}

void TRM::heater(int valueHeat){ //подача нагрева

}

