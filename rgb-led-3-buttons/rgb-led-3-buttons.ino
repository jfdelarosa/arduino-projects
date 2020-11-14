const int BUZZER_PIN = 12;

const int RED_BUTTON_PIN = 10;
const int GREEN_BUTTON_PIN = 9;
const int BLUE_BUTTON_PIN = 8;

const int RED_LED_PIN = 7;
const int GREEN_LED_PIN = 6;
const int BLUE_LED_PIN = 5;

int redLedState = LOW;
int lastRedButtonState;
int currentRedButtonState;

int greenLedState = LOW;
int lastGreenButtonState;
int currentGreenButtonState;

int blueLedState = LOW;
int lastBlueButtonState;
int currentBlueButtonState;

byte leds = 0;

void setup(){

  pinMode(BUZZER_PIN, OUTPUT);

  pinMode(RED_LED_PIN, OUTPUT);
  pinMode(GREEN_LED_PIN, OUTPUT);
  pinMode(BLUE_LED_PIN, OUTPUT);
  
  pinMode(RED_BUTTON_PIN, INPUT_PULLUP);  
  pinMode(GREEN_BUTTON_PIN, INPUT_PULLUP);  
  pinMode(BLUE_BUTTON_PIN, INPUT_PULLUP);  

  currentRedButtonState = digitalRead(RED_BUTTON_PIN);
  currentGreenButtonState = digitalRead(GREEN_BUTTON_PIN);
  currentBlueButtonState = digitalRead(BLUE_BUTTON_PIN);
}

void loop() {
  lastRedButtonState = currentRedButtonState;
  lastGreenButtonState = currentGreenButtonState;
  lastBlueButtonState = currentBlueButtonState;
  
  currentRedButtonState = digitalRead(RED_BUTTON_PIN);
  currentGreenButtonState = digitalRead(GREEN_BUTTON_PIN);
  currentBlueButtonState = digitalRead(BLUE_BUTTON_PIN);

  if(currentRedButtonState == LOW || currentGreenButtonState == LOW || currentBlueButtonState == LOW){
    digitalWrite(BUZZER_PIN, HIGH);
    delay(100);
    digitalWrite(BUZZER_PIN, LOW);
  }

  if (lastRedButtonState == HIGH && currentRedButtonState == LOW){
    redLedState = !redLedState;
    digitalWrite(RED_LED_PIN, redLedState);
  }

  if (lastGreenButtonState == HIGH && currentGreenButtonState == LOW){
    greenLedState = !greenLedState;
    digitalWrite(GREEN_LED_PIN, greenLedState);
  }

  if (lastBlueButtonState == HIGH && currentBlueButtonState == LOW){
    blueLedState = !blueLedState;
    digitalWrite(BLUE_LED_PIN, blueLedState);
  }
}