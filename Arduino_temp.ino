// Receive list of numbers as string and parse them into 3 numbers
const byte numChars = 120;
char  receivedChars[numChars];  // an array to store received data
char tempChars[numChars]; // temporary array for use when parsing

char title[numChars] = {0}; 

boolean newData = false;

void recvList()
{
  static boolean recvInProgress = false;
  static byte ndx = 0;
  char startMarker = '[';
  char endMarker = ']'; // let Arduino know full message is received
  char rc;

  while ((Serial.available() > 0) && (newData == false)) 
  {
    rc = Serial.read();

    if(recvInProgress == true)
    {
      if(rc != endMarker)
      {
        receivedChars[ndx] = rc;
        ndx++;
        if (ndx >= numChars)
        {
          ndx = numChars -1;
        }
      }
      else
      {
        /*we finished, the packet looks good*/
        receivedChars[ndx] = '\0'; // terminate string
        recvInProgress = false;
        ndx = 0;
        newData = true;
      }
    }
    else if (rc == startMarker)
    {
      recvInProgress = true;
    }
  }
}

void parseData() // split the data into its parts
{ 
  char * strtokIndx; // used by strtok() as an index

  strtokIndx = strtok(tempChars, ","); // first item in sent list is string to distinguish angles and points
  strcpy(title, strtokIndx);

  strtokIndx = strtok(NULL, ","); // get the first part
  rcvData.a_1 = atoi(strtokIndx); // convert this part into integer

  strtokIndx = strtok(NULL, ","); // this continues where the previous call left off
  rcvData.a_2 = atoi(strtokIndx);

  strtokIndx = strtok(NULL, ",");
  rcvData.a_3 = atoi(strtokIndx);
}

void showParsedData()
{
  if (newData == true)
  {
  }
}


//-----------------------------------------------------------------------------
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


//-----------------------------------------------------------------------------
void loop() 
{
  recvList();
  if (newData == true)
  {
    strcpy(tempChars, receivedChars); // this temporary copy is necessary to protect the original data, because strtok() used in parseData() replaces the commas with \0
    parseData();
    showParsedData();
    newData = false;
  }

  double tempC = thermocouple.readCelsius();
  // Send to python to store
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
