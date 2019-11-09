#include <Servo.h>  //Servo library

// initialize servo objects for the connected servo motors
Servo servo1; 
Servo servo2; 
Servo servo3; 
Servo servo4; 

// angles of each servo
// note: these are subject to change frequently
int angleUp1 = 18;
int angleDown1 = 30;

int angleUp2 = 48;
int angleDown2 = 63;

int angleUp3 = 70;
int angleDown3 = 85;

int angleUp4 = 53;
int angleDown4 = 70;

unsigned long pm = 0; // used to count delay

int counter; // score counter 

int d; // the delay

void setup()
{
  // attaching signal pins of servo motors to pins of arduino
  servo1.attach(3);
  servo2.attach(5);
  servo3.attach(9);
  servo4.attach(11);
  
  // score counter
  counter = 0;

  // delay
  d = 90;

  // using the serial port for debuging
  Serial.begin(9600);
}

void loop()
{
  // used to count delay
  unsigned int cm = millis();

  if ((unsigned long)(cm - pm) >= d)
  {
    unsigned int s1 = 0;
    unsigned int s2 = 0;
    unsigned int s3 = 0;
    unsigned int s4 = 0;

    if (counter > 300)
    {
      d = 0;
    }
    else if (counter > 200)
    {
      d = 30;
    }
    else if (counter > 100)
    {
      d = 40;
    }

    // take 10 reads for better immunity to noise
    for (int i = 0; i < 10; i++) 
    {
      s1 += analogRead(A1);
      s2 += analogRead(A2);
      s3 += analogRead(A3);
      s4 += analogRead(A4);
    }

    s1 /= 10;
    s2 /= 10;
    s3 /= 10;
    s4 /= 10;

    // print to serial for debuging
    Serial.print(s1);
    Serial.print("\t");
    Serial.print(s2);
    Serial.print("\t");
    Serial.print(s3);
    Serial.print("\t");
    Serial.print(s4);
    Serial.print("\n");

    // first get all arms up 
    servo1.write(angleUp1);
    servo2.write(angleUp2);
    servo3.write(angleUp3);
    servo4.write(angleUp4);

    if (s1 > 985)
    {
      servo1.write(angleDown1);
      counter += 1;
    }
    else
    {
      servo1.write(angleUp1);
    }

    if (s2 > 985)
    {
      servo2.write(angleDown2);
      counter += 1;
    }
    else
    {
      servo2.write(angleUp2);
    }

    if (s3 > 960)
    {
      servo3.write(angleDown3);
      counter += 1;
    }
    else
    {
      servo3.write(angleUp3);
    }

    if (s4 > 950)
    {
      servo4.write(angleDown4);
      counter += 1;
    }
    else
    {
      servo4.write(angleUp4);
    }

    // used for delay
    pm = millis();
  }
}
