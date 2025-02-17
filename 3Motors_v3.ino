#include <Servo.h>
Servo myservo_1;
Servo myservo_2;
Servo myservo_3;
int servoPin_1 = 9;
int servoPin_2 = 10;
int servoPin_3 = 11;

// Function to rotate the servo motor thus open valve
void addAngles(Servo &servoMotor, int Start_angle, int End_Angle) 
{
  for (int pos = Start_angle; pos <= End_Angle; pos += 1) 
  { 
    // in steps of 1 degree 
    servoMotor.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
}

// Function to rotate the servo motor thus close valve
void minusAngles(Servo &servoMotor, int Start_angle, int End_Angle) 
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

  // show calibrated angles
  myservo_1.write(90); // horizontal
  myservo_2.write(60); // extra 2 seconds delay
  myservo_3.write(80);
  delay(3000);
  myservo_1.write(159); // start with vertical
  myservo_2.write(140);
  myservo_3.write(150);
  delay(3000);
}

void loop() 
{
  myservo_2.write(60); // close valve 2 
  delay(1000);
  myservo_1.write(90); // open valve 1
  delay(5*60000);
  myservo_1.write(159);
  delay(1000);
  myservo_2.write(140); // valve 2 open
  delay(5*61000);
  myservo_2.write(60); // valve 2 close
  delay(1000);
  myservo_3.write(80);
  delay(5*60000);
  myservo_3.write(150); // valve 3 close
  delay(1000);
  myservo_2.write(140); // valve 2 open
  delay(5*61000);
}

