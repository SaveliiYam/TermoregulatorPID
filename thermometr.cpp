#include "thermometr.h"

void thermometr::getParameters(byte sck, byte cs, byte so) {
  _sck = sck;
  _cs = cs;
  _so = so;
  pinMode(_cs, OUTPUT);
  pinMode(_sck, OUTPUT);
  pinMode(_so, INPUT);
  digitalWrite(_cs, HIGH);
}

float thermometr::readCelsius() {
  uint16_t v;
  digitalWrite(_cs, LOW);
  delayMicroseconds(10);
  v = spiread();
  v <<= 8;
  v |= spiread();
  digitalWrite(_cs, HIGH);
  if (v & 0x4) {
    return NAN;
  }
  v >>= 3;
  return v * 0.25;
}

float thermometr::readFahrenheit(){return readCelsius() * 9.0 / 5.0 + 32; }

float thermometr::readKelvin(){return readCelsius() + 273.15;}

byte thermometr::spiread(void) {
  int i;
  byte d = 0;
  for (i = 7; i >= 0; i--) {
    digitalWrite(_sck, LOW);
    delayMicroseconds(10);
    if (digitalRead(_so)) {
      d |= (1 << i);
    }
    digitalWrite(_sck, HIGH);
    delayMicroseconds(10);
  }
  return d;
}