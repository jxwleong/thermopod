#include "VoltageSensor.h"

VoltageSensor::VoltageSensor(uint8_t _pin) {
	pin = _pin;
}

int VoltageSensor::calibrate() {
	uint16_t acc = 0;
	for (int i = 0; i < 10; i++) {
		acc += analogRead(pin);
	}
	zero = acc / 10;
	return zero;
}

void VoltageSensor::setZeroPoint(int _zero) {
	zero = _zero;
}

void VoltageSensor::setVoltageReference(float volts){
  voltageReference = volts;
}

void VoltageSensor::setAdcResolution(float adcResolution){
  adcScale = adcResolution;
}

void VoltageSensor::setR1Resistance(float resistance){
  r1 = resistance;
}

void VoltageSensor::setR2Resistance(float resistance){
  r2 = resistance;
}

// https://how2electronics.com/interfacing-0-25v-dc-voltage-sensor-with-arduino/
float VoltageSensor::getVoltage(){
  float adcVoltage = 0.0;
  float voltage = 0.0;
	int16_t acc = 0;
	for (int i = 0; i < 10; i++) {
		acc += analogRead(pin) - zero;
	}  
  adcVoltage  = (acc/10 * voltageReference) / adcScale; 
   // Calculate voltage at divider input
	voltage = adcVoltage / (r2/(r1+r2)); 
	return voltage;
}