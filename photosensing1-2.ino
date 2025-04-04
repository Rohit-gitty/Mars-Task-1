#include <Servo.h>         // Include the Servo library

Servo tellServo;          // Create an object for the library

const int leftSensor = A0; // Left light sensor(PR1) connected to analog read pin A0
const int rightSensor = A1; // Right light sensor(PR2) connected to analog read pin A1
const int servoPin = 9;    // Servo signal wire(ORANGE) connected to digital read pin 9

int degrees = 90;              // Initial position of servo (centered)

void setup() {
  tellServo.attach(servoPin); // Attach the servo to pin 9
  tellServo.write(degrees);       // Move servo to start position (90°)
  delay(1000);                 // Wait a bit for servo to halt due to inertia
}

void loop()
{
  int leftLight = analogRead(leftSensor);   // to measure light level from left sensor
  int rightLight = analogRead(rightSensor); // to measure light level from right sensor

  int diff = leftLight - rightLight;        // to Calculate difference between sensors



  // If the difference is noticable that is more than threshold, adjust the servo
  if (abs(diff) > 5) {                     // 5 is a sensitivity threshold
    if (diff > 0 && degrees >0 ) {
      degrees-=5;                                // Turn left
    } 
    else if (diff < 0 && degrees < 180 ) 
    {
      degrees+=5;                               // Turn right
    }
    tellServo.write(degrees);                  // Move servo to new position which has more light intensity
 }

  delay(1000);                                // Short delay before next iteration for smooth movement
}