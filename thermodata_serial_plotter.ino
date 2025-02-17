#include <SPI.h>
#include "Adafruit_MAX31855.h"

#define MAXDO  12
#define MAXCLK 13

Adafruit_MAX31855 thermocouple1(MAXCLK, , MAXDO); // add our CS pins here
Adafruit_MAX31855 thermocouple2(MAXCLK, , MAXDO);
Adafruit_MAX31855 thermocouple3(MAXCLK, , MAXDO);


void setup() {
  Serial.begin(9600);
  Serial.println("Thermocouple1,Thermocouple2,Thermocouple3"); // this will be our legend for our serial plotter.
  while (!Serial);

  Serial.println("Initialising MAX31855 sensors...");

  if (!thermocouple1.begin()) {
    Serial.println("Error with sensor 1");
  }
  if (!thermocouple2.begin()) {
    Serial.println("Error with sensor 2");
  }
  if (!thermocouple3.begin()) {
    Serial.println("Error with sensor 3");
  }

  
}

void loop() {
  // put your main code here, to run repeatedly:

  double thermo1 = thermocouple1.readCelsius();
  double thermo2 = thermocouple2.readCelsius();
  double thermo3 = thermocouple3.readCelsius();

  Serial.print(thermo1);
  Serial.print(",");
  Serial.print(thermo2);
  Serial.print(",");
  Serial.print(thermo3);
  Serial.print(",");
  Serial.println();

  delay(1000);
  
  

}
