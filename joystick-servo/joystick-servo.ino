#include <Servo.h>

Servo myservo;

const int SW_PIN = 2;
const int X_PIN = 0;
const int Y_PIN = 1;
float lastNumber;

float remap(float value, float start1, float stop1, float start2, float stop2){
  return start2 + (stop2 - start2) * ((value - start1) / (stop1 - start1));
}

void setup(){
  myservo.attach(9);
  pinMode(SW_PIN, INPUT);
  digitalWrite(SW_PIN, HIGH);
  Serial.begin(9600);
  myservo.write(90);
}

void loop(){
  float x_pos = analogRead(X_PIN);
  float newNumber = remap(x_pos, 0, 1024, 180, 0);

  if(lastNumber != newNumber){
    Serial.print(newNumber);
    Serial.print("\n");
  }
  lastNumber = newNumber;
  myservo.write(newNumber);
}
