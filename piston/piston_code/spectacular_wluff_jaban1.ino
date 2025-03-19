#include <Servo.h>  

Servo myservo;  // create servo object to control a servo
int pos = 0;    // variable to store the servo position
unsigned long startMillis;  // stores the time when the motion starts
bool buttonState = false;  // button state (pressed or not pressed)
bool lastButtonState = false;  // previous button state

void setup() {
  myservo.attach(9);      // Attaches the servo to pin 9
  Serial.begin(9600);     // Starts serial communication at 9600 baud
  pinMode(6, INPUT);      // Set pin 6 as input for the button
}

void loop() {
  buttonState = digitalRead(6);  // Read the current state of the button

  // If the button is pressed and it wasn't pressed before, start moving the servo
  if (buttonState == HIGH && lastButtonState == LOW) {
    startMillis = millis();  // Record the start time when button is pressed
    while (buttonState == HIGH) {  // Continue while button is still pressed
      unsigned long currentMillis = millis();  // Get current time
      int elapsedTime = currentMillis - startMillis;  // Calculate elapsed time

      if (elapsedTime <= 250) {
        pos = map(elapsedTime, 0, 250, 0, 63);  // Map the time to servo position
        myservo.write(pos);  // Move the servo to the calculated position
      } else {
        break;  // Exit the loop after 250ms
      }
      buttonState = digitalRead(6);  // Check if button state has changed
    }
  }

  // If the button is not pressed, move the servo back to 0 degrees
  if (buttonState == LOW && lastButtonState == HIGH) {
    startMillis = millis();  // Record the start time when button is released
    while (buttonState == LOW) {  // Continue while button is still not pressed
      unsigned long currentMillis = millis();  // Get current time
      int elapsedTime = currentMillis - startMillis;  // Calculate elapsed time

      if (elapsedTime <= 250) {
        pos = map(elapsedTime, 0, 250, 63, 0);  // Map the time to servo position
        myservo.write(pos);  // Move the servo to the calculated position
      } else {
        break;  // Exit the loop after 250ms
      }
      buttonState = digitalRead(6);  // Check if button state has changed
    }
  }

  // Update lastButtonState to the current button state
  lastButtonState = buttonState;
}