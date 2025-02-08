/********************************************************
 * PID RelayOutput Example
 * Same as basic example, except that this time, the output
 * is going to a digital pin which (we presume) is controlling
 * a relay.  the pid is designed to Output an analog value,
 * but the relay can only be On/Off.
 *
 *   to connect them together we use "time proportioning
 * control"  it's essentially a really slow version of PWM.
 * first we decide on a window size (5000mS say.) we then
 * set the pid to adjust its output between 0 and that window
 * size.  lastly, we add some logic that translates the PID
 * output into "Relay On Time" with the remainder of the
 * window being "Relay Off Time"
 ********************************************************/

#include <PID_v1.h>
#define RELAY_PIN 10
//Define Variables we'll be connecting to
double Setpoint, Input, Output;
//Specify the links and initial tuning parameters
double Kp=1, Ki=1, Kd=1;
PID myPID(&Input, &Output, &Setpoint, Kp, Ki, Kd, DIRECT);

int WindowSize = 5000;
unsigned long windowStartTime;

#include <SPI.h>
#include <Adafruit_MAX31855.h>
#define MAXDO  12
#define MAXCS  4
#define MAXCLK 13
Adafruit_MAX31855 thermocouple(MAXCLK, MAXCS, MAXDO);

const int relayPin = 9;

void setup() 
{
  Serial.begin(9600);
  Serial.println("Temperature Logging Started");
  // wait for MAX chip to stabilize
  delay(500);

  windowStartTime = millis();

  //initialize the variables we're linked to
  Setpoint = 200;

  //tell the PID to range between 0 and the full window size
  myPID.SetOutputLimits(0, WindowSize);
  //turn the PID on
  myPID.SetMode(AUTOMATIC);
}


void loop() 
{
  double tempC = thermocouple.readCelsius();

  // readout test, print the current temp and target temp
  // can be plotted using Serial Plotter Tool
  Serial.print("Target value: ");
  Serial.print(Setpoint);
  Serial.print(",");
  Serial.print("Temperature (degreeC): "); 
  Serial.println(tempC);
  delay(5000);
  
  myPID.Compute();

  // turn the output pin on/off based on pid output
  if (millis() - windowStartTime > WindowSize)
  { //time to shift the Relay Window
    windowStartTime += WindowSize;
  }
  if (Output < millis() - windowStartTime) digitalWrite(RELAY_PIN, HIGH);
  else digitalWrite(RELAY_PIN, LOW);
}
