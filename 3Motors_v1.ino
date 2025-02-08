#include <Servo.h>
Servo myservo_1;
Servo myservo_2;
int servoPin_1 = 9;
int servoPin_2 = 10;
int servoPin_2 = 11;
int pos = 0;
unsigned long time;

void setup() {
  myservo_1.attach(servoPin_1); // set pin for servo control
  myservo_2.attach(servoPin_2);
  myservo_2.attach(servoPin_3);
}

void loop() {
  time = millis();
  for (pos = 0; pos <= 100; pos += 1) { // goes from 0 degrees to 90 degrees
    // in steps of 1 degree
    // open valve
    myservo_1.write(pos);              // tell servo to go to position in variable 'pos'
    myservo_2.write(pos);
    myservo_3.write(pos);
    delay(15);                       // waits 15ms for the servo to reach the position
  }
  delay(10000); // stay there for 10s
  
  for (pos = 100; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo_1.write(pos);  
    myservo_2.write(pos);   
    myservo_3.write(pos);         
    delay(15);                       
    // close valve
  }
  while(millis() < time+30000); // repeat the above every 30s
}

