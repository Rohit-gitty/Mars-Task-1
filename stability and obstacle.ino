const int trigPin = 8;
const int echoPin = 9;
const int tiltPin = 7;
const int forcePin = A0;

const int redLED = 5;
const int greenLED = 6;
const int buzzer = 4;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(tiltPin, INPUT);
  pinMode(redLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(buzzer, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // Distance reading
  digitalWrite(trigPin, LOW); delayMicroseconds(2);
  digitalWrite(trigPin, HIGH); delayMicroseconds(2);
  digitalWrite(trigPin, LOW);
  long duration = pulseIn(echoPin, HIGH);
  int distance = duration * 0.034 / 2;

  // Read tilt sensor
  int tiltState = digitalRead(tiltPin);

  // Read force sensor
  int rawForce = analogRead(forcePin);
  float maxForceN = 10.0;  // Assume 10 N is the max readable force
  float forceN = (rawForce / 1023.0) * maxForceN;

  // Debug print
  Serial.print("Distance: "); Serial.print(distance); Serial.print(" cm | ");
  Serial.print("Tilt: "); Serial.print(tiltState); Serial.print(" | ");
  Serial.print("Force: "); Serial.print(forceN);  Serial.println(" N  ");

  // Conditions for alert
  if (distance < 50|| tiltState == HIGH || forceN >2 ) {
    digitalWrite(redLED, HIGH);
    digitalWrite(greenLED, LOW);
    digitalWrite(buzzer, HIGH);
  } else {
    digitalWrite(redLED, LOW);
    digitalWrite(greenLED, HIGH);
    digitalWrite(buzzer, LOW);
  }

  delay(500);
}
