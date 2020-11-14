#include <stdlib.h>
#include "LedControl.h"

const int SENSOR_ANALOG_PIN = A0;
const int SENSOR_DIGITAL_PIN = 3;
const int ROWS = 8;
int analogValue = 0;
double total = 0;
unsigned int count = 0;

float remap(float value, float start1, float stop1, float start2, float stop2){
  return (value - start1) / (stop1 - start1) * (stop2 - start2) + start2;
}

LedControl lc = LedControl(12, 10, 11, 1);

void setup() {
  Serial.begin(9600);
  pinMode(SENSOR_DIGITAL_PIN, INPUT);
  lc.shutdown(0, false);
  lc.setIntensity(0, 8);
  lc.clearDisplay(0);
}

void loop(){
  analogValue = analogRead(SENSOR_ANALOG_PIN);
  count = count + 1;
  total = total + analogValue;
  if(count == 100){
    count = 1;
    total = analogValue;
  }
  float average = (total / count) - 1;
  int allowance = 6;

  float level = remap(analogValue, average, average + allowance, 0, ROWS);
  level = ceil(abs(level));

  for(int i = 0; i < ROWS; i++){
    if(i < level){
      lc.setRow(0, i, B11111111);
    }else{
      lc.setRow(0, i, B00000000);
    }
  }

  Serial.println(level);
}
