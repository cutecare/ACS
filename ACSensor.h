/*
Part of http://cutecare.ru project
Author: evgeny.savitsky@gmail.com
*/

#ifndef ACSensor_h
#define ACSensor_h

#if (ARDUINO >= 100)
  #include <Arduino.h>
#else
  #include <WProgram.h>
#endif

// Coefficient to convert measured sinusoidal AC into effective AC
#define AC_RMS_COEFF 0.707 

class ACSensor {
  public:
    ACSensor(float sensitivity = 40.0, float noise = 10.0);
    void calibrate();
    float getVoltage();
    float getAmperes();
    int getWatt(int voltage = 220);

  private:
    float _sensitivity = 0;
    float _noise = 0;
    float _zero = 0;
};

#endif
