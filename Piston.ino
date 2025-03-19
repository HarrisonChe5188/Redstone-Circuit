#include <Servo.h>

Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

int pos = 0;    // variable to store the servo position


void setup(){
myservo.attach(9);
Serial.begin(9600);
pinMode(6, INPUT);
pinMode(7, OUTPUT);
myservo.write(pos);
}

void loop() {

float volts;
volts = digitalRead(6); // returns bit (0= 0 volts, 1024=5.0 volts)

// wanna see what it is?
Serial.println(volts);

// now do your test
  if (volts == HIGH){
digitalWrite(7, HIGH);
pos = 180;
  }
else {
digitalWrite(7, LOW);
pos = 0;
}
myservo.write(pos);
}