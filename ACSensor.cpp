/*
Part of http://cutecare.ru project
Author: evgeny.savitsky@gmail.com
*/
#include "ACSensor.h";

ACSensor::ACSensor(float sensitivity, float noise) 
{
  _sensitivity = sensitivity;
  _noise = noise;
}

void ACSensor::calibrate()
{
  _zero = getVoltage();
}

float ACSensor::getVoltage()
{
  unsigned int maxValue = 0;
  unsigned long averageValue = 0;
  int samples = 5;
  
  for( int j = 0; j < samples; j++ ) {
    maxValue = 0;
    for( int i = 0; i < 20; i++ ) {
      unsigned int readValue = abs(analogRead(SENSOR_PIN) - 512.0);
      if ( readValue > maxValue ) {
        maxValue = readValue;
      }
      delay(2);
    }
    averageValue += maxValue;
  }

  return (float) (averageValue / (samples * 1024.0)) * 5000.0;
}

float ACSensor::getAmperes()
{
  float voltage = getVoltage();
  return (voltage <= _noise) ? 0.0 : (voltage * AC_RMS_COEFF / _sensitivity);
}

int ACSensor::getWatt(int voltage)
{
  return floor(getAmperes() * voltage);
}
