int gasPin = A0;
int tempPin = A1;

int redLED = 8;
int greenLED = 7;
int buzzer = 9;

void setup() {
  pinMode(redLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(buzzer, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int gasLevel = analogRead(gasPin);    // 0 to 1023
  int tempRaw = analogRead(tempPin);    // Raw value from LM36

  // Convert raw value to voltage (0 to 5V)
  float voltage = (tempRaw * 5.0) / 1024.0;

  // Adjust for LM36's 500mV offset and convert to Celsius
  float tempC = (voltage - 0.5) * 100.0;

  Serial.print("Gas: ");
  Serial.print(gasLevel);
  Serial.print(" | Temp: ");
  Serial.println(tempC);

  if (gasLevel > 400 || tempC > 50) { // Danger Range
    digitalWrite(redLED, HIGH);
    digitalWrite(greenLED, LOW);
    digitalWrite(buzzer, HIGH);
  } else {
    digitalWrite(redLED, LOW);
    digitalWrite(greenLED, HIGH);
    digitalWrite(buzzer, LOW);
  }

  delay(1000);
}
