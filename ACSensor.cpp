/*
Part of http://cutecare.ru project
Author: evgeny.savitsky@gmail.com
*/
#include "ACSensor.h";

ACSensor::ACSensor(int pin, float sensitivity, float noise) 
{
  _pin = pin;
  _sensitivity = sensitivity;
  _noise = noise;
}

void ACSensor::calibrate()
{
  _zero = getVoltage();
}

float ACSensor::getVoltage()
{
  int maxValue, readValue;
  float averageValue = 0.0;
  int samples = 5;
  
  pinMode(_pin, INPUT);
  
  for( int j = 0; j < samples; j++ ) {
	maxValue = 0;
    for( int i = 0; i < 20; i++ ) {
	  readValue = analogRead(_pin) - 512; // bi-directional ACS
	  readValue = abs(readValue);
      if ( readValue > maxValue ) {
        maxValue = readValue;
      }
      delay(2);
    }
    averageValue += (float) maxValue;
  }
  return 5000.0 * averageValue / ((float) samples * 1024.0);
}

float ACSensor::getAmperes()
{
  float voltage = getVoltage() - _zero;
  voltage = abs(voltage);
  return (voltage <= _noise) ? 0.0 : (voltage * AC_RMS_COEFF / _sensitivity);
}

int ACSensor::getWatt(float voltage)
{
  return floor(getAmperes() * voltage);
}
