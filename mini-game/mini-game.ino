#include "pitches.h"
#include "LedControl.h"

LedControl lc = LedControl(8, 6, 7, 1);

const int BUZZER = 4;
const int BUTTON_PIN = 5;
const int LATCH_PIN = 11;
const int CLOCK_PIN = 10;
const int DATA_PIN = 12;
const int GREEN_LED = 7;

int score = 0;
int note;
byte current_led = 0;

const uint64_t IMAGES[] = {
  0xc3e77e3c3c7ee7c3,
  0x3c66666e76663c00,
  0x7e1818181c181800,
  0x7e060c3060663c00,
  0x3c66603860663c00,
  0x30307e3234383000,
  0x3c6660603e067e00,
  0x3c66663e06663c00,
  0x1818183030667e00,
  0x3c66663c66663c00,
  0x3c66607c66663c00,
};

const int IMAGES_LEN = sizeof(IMAGES)/8;

void displayImage(uint64_t image) {
  for (int i = 0; i < 8; i++) {
    byte row = (image >> i * 8) & 0xFF;
    for (int j = 0; j < 8; j++) {
      lc.setLed(0, i, j, bitRead(row, j));
    }
  }
}

void updateShiftRegister(){
  digitalWrite(LATCH_PIN, LOW);
  shiftOut(DATA_PIN, CLOCK_PIN, LSBFIRST, current_led);
  digitalWrite(LATCH_PIN, HIGH);
}

void resetBuzz(int note){
  tone(BUZZER, note, 100);
  delay(50);
  current_led = 0;
  updateShiftRegister();
}

void buzzOne(int i, int note){
  current_led = 0;
  bitSet(current_led, i);
  updateShiftRegister();
  resetBuzz(note);
}

void setup() {
  lc.shutdown(0, false);
  lc.setIntensity(0, 8);
  lc.clearDisplay(0);

  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(LATCH_PIN, OUTPUT);
  pinMode(CLOCK_PIN, OUTPUT);
  pinMode(DATA_PIN, OUTPUT);

  displayImage(IMAGES[1]);
}

void loop() {
  for(int i = 0; i < 8; i++){
    if(digitalRead(BUTTON_PIN) == LOW){
      if(i == GREEN_LED){
        score = score + 1;
        displayImage(IMAGES[score + 1]);
        for(int j = 0; j < 10; j++){
          buzzOne(i, NOTE_B0);
          delay(80);
        }
      }else{
        score = 0;
        displayImage(IMAGES[0]);
        for(int j = 0; j < 10; j++){
          buzzOne(i, NOTE_C7);
          delay(100);
        }
        delay(200);
        displayImage(IMAGES[1]);
      }
      break;
    }else{
      bitSet(current_led, i);
      updateShiftRegister();
      if(i == 0){
        delay(100);
      }
      delay(80 - score * 4);
    }
    current_led = 0;
    updateShiftRegister();
  }
  delay(500);
}
