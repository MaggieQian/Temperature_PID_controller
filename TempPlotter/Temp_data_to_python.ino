#include <SPI.h>
#include <Adafruit_MAX31855.h>

#define MAXDO  12
#define MAXCLK 13

// Assigning Chip Select (CS) Pins
Adafruit_MAX31855 thermocouple1(MAXCLK, 4, MAXDO);
Adafruit_MAX31855 thermocouple2(MAXCLK, 5, MAXDO);
Adafruit_MAX31855 thermocouple3(MAXCLK, 7, MAXDO);

void setup() {
    Serial.begin(9600);
    Serial.println("Thermocouple1,Thermocouple2,Thermocouple3"); // CSV Header
    
    Serial.println("Initializing MAX31855 sensors...");

    if (!thermocouple1.begin()) {
        Serial.println("Error: Sensor 1 not found.");
    }
    if (!thermocouple2.begin()) {
        Serial.println("Error: Sensor 2 not found.");
    }
    if (!thermocouple3.begin()) {
        Serial.println("Error: Sensor 3 not found.");
    }
}

void loop() {
    double thermo1 = thermocouple1.readCelsius();
    double thermo2 = thermocouple2.readCelsius();
    double thermo3 = thermocouple3.readCelsius();

    Serial.print(thermo1);
    Serial.print(",");
    Serial.print(thermo2);
    Serial.print(",");
    Serial.println(thermo3); // Corrected CSV formatting

    delay(1000); // Read temperature every 1 second
}
