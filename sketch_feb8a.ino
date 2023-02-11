#include "VoltageSensor.h"

#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
// https://how2electronics.com/interfacing-0-25v-dc-voltage-sensor-with-arduino/
// Define analog input
// MUX model: CD74HC4051E
#define ANALOG_IN_PIN A0
 
#define OLED_WIDTH 128
#define OLED_HEIGHT 64
#define OLED_ADDR   0x3C

VoltageSensor vSensor(ANALOG_IN_PIN);
Adafruit_SSD1306 display(OLED_WIDTH, OLED_HEIGHT);

bool INIT_CODE_RUN = false;

void oled_init(Adafruit_SSD1306 &oled_display) {

  oled_display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR);
  oled_display.clearDisplay();

  oled_display.setTextSize(2);
  oled_display.setTextColor(WHITE);
  oled_display.setCursor(0, 0);
  oled_display.println("Welcome");

  oled_display.setTextSize(2);
  oled_display.setTextColor(WHITE);
  oled_display.setCursor(0, 17);
  oled_display.println("To");
  oled_display.println("THERMOPOD!");

  oled_display.display();

  delay(3000);

  oled_display.clearDisplay();
  oled_display.setTextSize(0);
  oled_display.setCursor(0, 0);
  oled_display.setTextColor(WHITE);
  oled_display.println("Calibrating Sensor...");
  //oled_display.println("");
  //oled_display.println("Make sure it's not connected to power source!");
  oled_display.display();
  delay(2000);
}

/*
The function uses the stringstream class and the fixed, setprecision, and setw manipulators to format the floating point number and add the desired padding. The fixed manipulator sets the floating point output format to fixed-point notation, setprecision(2) sets the number of digits to be displayed after the decimal point, and setw(7) sets the width of the output to 7 characters, including the decimal point and the trailing " V".
*/
char* getVoltageMessage(float voltage) {
    std::stringstream ss;
    ss << "Voltage: " << std::fixed << std::setprecision(2) << std::setw(7) << voltage << " V";
    std::string str = ss.str();
    char* result = new char[str.length() + 1];
    std::strcpy(result, str.c_str());
    return result;
}

char* getCurrentMessage(float current) {
    std::stringstream ss;
    ss << "Current: " << std::fixed << std::setprecision(2) << std::setw(7) << current << " A";
    std::string str = ss.str();
    char* result = new char[str.length() + 1];
    std::strcpy(result, str.c_str());
    return result;
}

char* getPowerMessage(float power) {
    std::stringstream ss;
    ss << "Power  : " << std::fixed << std::setprecision(2) << std::setw(7) << power << " W";
    std::string str = ss.str();
    char* result = new char[str.length() + 1];
    std::strcpy(result, str.c_str());
    return result;
}

void oled_multimeter_print(Adafruit_SSD1306 &oled_display, float voltage, float current, float power){
  oled_display.clearDisplay();

  oled_display.setTextSize(2);
  oled_display.setTextColor(WHITE);
  oled_display.setCursor(0, 0);
  oled_display.println("MULTIMETER");

  oled_display.setTextSize(1);
  oled_display.setTextColor(WHITE);
  oled_display.setCursor(0, 17);

  oled_display.println("");
  oled_display.println(getVoltageMessage(voltage));
  oled_display.println("");
  oled_display.println(getCurrentMessage(current));
  oled_display.println("");
  oled_display.println(getPowerMessage(power));

  oled_display.display();
}


void setup()
{
  // Setup Serial Monitor
  Serial.begin(115200);


  oled_init(display);
  vSensor.setVoltageReference(3.3);


}
 
void loop(){

   // Print results to Serial Monitor to 2 decimal places
  //Serial.print("Input Voltage = ");
  //Serial.println(vSensor.getVoltage(), 2);
  
  // Short delay
  delay(500);
  //Serial.println("AWAKE!");
  // Sleep mode: https://www.electronicshub.org/esp8266-deep-sleep-mode/
  //Serial.println("Sleeping for 5 seconds!");
  //delay(1000);
  //ESP.deepSleep(5e6); /* Sleep for 5 seconds */
  //oled_multimeter_print(display, 1.25, 0.5, 1.25*0.5);
  Serial.println(analogRead(A0));


}
