#ifndef VoltageSensor_h
#define VoltageSensor_h

#include <Arduino.h>



class VoltageSensor {
public:
	VoltageSensor(uint8_t _pin);
	int calibrate();
	void setZeroPoint(int _zero);
  void setVoltageReference(float volts);
  void setAdcResolution(float adcResolution);
  void setR1Resistance(float resistance);
  void setR2Resistance(float resistance);
  float getVoltage();


private:
	int zero = 20;  // Average of adc value 20 with open circuit (tested manually)
	float sensitivity;
	uint8_t pin;
  float voltageReference = 5;      // Vcc of the MCU
  float adcScale = 1024.0;         // ADC resolution
	float r1 = 30000.0;
	float r2 = 7500.0;

};

#endif