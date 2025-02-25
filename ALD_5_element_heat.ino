#include <Adafruit_CircuitPlayground.h>
#include <Adafruit_Circuit_Playground.h>

int writeHi = 255;
int writeLo = 0;
int cycTime = 5000;   // Number of miliseconds in each PWM set.
float heat1Frac = 0.240;//0.240;    // Main chamber small heater duty cycle                          Target 280 C
float heat2Frac = 0.045;//0.050;      // Precursor 1 chamber duty cycle                 Target 160 C
float heat3Frac = 0.150;//0.150;      // Main chamber big heater                        Target 160 C
float heat4Frac = 0.043;//0.050      // Reactor sample chamber: 0.050                              Target 350 C
float heat5Frac = 0.045;  // New heaitng element

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(5, OUTPUT);  // Main chamber heater
  pinMode(6, OUTPUT);  // Main precursor heater
  pinMode(9, OUTPUT);  // Secondary precursor heater
  pinMode(3, OUTPUT);  // Exit chamber heater
  pinMode( , OUTPUT); // new heaitng element - add the CS
}

void loop() {
  analogWrite(5,writeHi);
  analogWrite(3,writeHi);
  analogWrite( , writeHi);  // add the CS for 5th element
  for (int i = 0; i <= cycTime; i++) {
    if(i==round(cycTime*heat1Frac)){
      analogWrite(5,writeLo);
      analogWrite( , writeLo);   // add the CS for the 5th element
      analogWrite(6,writeHi);
    }
    if(i==round(cycTime*heat4Frac)){
      analogWrite(3,writeLo);
    }
    if(i==round(cycTime*(heat1Frac+heat2Frac))) {
      analogWrite(6,writeLo);
      analogWrite(9,writeHi);
    }
    if(i==round(cycTime*(heat1Frac+heat2Frac+heat3Frac))) {
      analogWrite(9,writeLo);
    }
    delay(1);
    }
}
