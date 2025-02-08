#include <Servo.h>
Servo myservo_1;
Servo myservo_2;
Servo myservo_3;
int servoPin_1 = 9;
int servoPin_2 = 10;
int servoPin_3 = 11;

// Function to rotate the servo motor thus open valve
void openValve(Servo &servoMotor, int Start_angle, int End_Angle) 
{
  for (int pos = Start_angle; pos <= End_Angle; pos += 1) 
  { 
    // in steps of 1 degree 
    servoMotor.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
}

// Function to rotate the servo motor thus close valve
void closeValve(Servo &servoMotor, int Start_angle, int End_Angle) 
{
  for (int pos = End_Angle; pos >= Start_angle; pos -= 1) 
  { 
    // in steps of 1 degree 
    servoMotor.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
}

void setup() 
{
  myservo_1.attach(servoPin_1); // set pin for servo control
  myservo_2.attach(servoPin_2);
  myservo_3.attach(servoPin_3);
}

void loop() 
{
  openValve(myservo_1, 0, 180);
  openValve(myservo_2, 0, 180);
  openValve(myservo_3, 0, 180);
  delay(5000);
  closeValve(myservo_1, 0, 180);
  closeValve(myservo_2, 0, 180);
  closeValve(myservo_3, 0, 180);
  delay(10000);
}

