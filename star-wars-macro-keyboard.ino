#include "Keyboard.h"

// Key definitions
#define BUTTON_KEY_H1 KEY_PAGE_UP
#define BUTTON_KEY_H2 KEY_DELETE
#define BUTTON_KEY_H3 KEY_PAGE_DOWN
#define BUTTON_KEY_V1 KEY_F4
#define BUTTON_KEY_V2 KEY_F13
 
// Pin definitions
#define BUTTON_PIN_H1 4
#define BUTTON_PIN_H2 5
#define BUTTON_PIN_H3 6
#define BUTTON_PIN_V1 8
#define BUTTON_PIN_V2 7

#define ARMED_BUTTON_PIN 3
#define ARMED_LED_PIN 2

#define LED_PIN_V1 10
#define LED_PIN_V2 9

#define RX_LED_PIN 17
 
 
// Button helper class for handling press/release and debouncing
class Button {
  public:
  
  Button(uint8_t k, uint8_t p) : _key(k), _pin(p){}

  void setup() {
    pinMode(_pin, INPUT_PULLUP);
  }
 
  void update(){
    boolean isNowPressed = _isPressed();

    // Do nothing within the debounce time frame.
    if(isNowPressed == _isLastPressed || (millis() - _lastPressedTimeMsec <= _debounceTimeMsec)){
      return;
    }
 
    _lastPressedTimeMsec = millis();
 
    isNowPressed ? Keyboard.press(_key) : Keyboard.release(_key);    
    _isLastPressed = isNowPressed;
  }
 
  private:
  
  const char _key;
  const uint8_t _pin;  
  const long _debounceTimeMsec = 30;
  unsigned long _lastPressedTimeMsec;
  boolean _isLastPressed = 0;

  boolean _isPressed() {
    return digitalRead(_pin) == LOW;
  }  
} ;
 
// Assign keys to buttons.
Button buttons[] = {
  {BUTTON_KEY_H1, BUTTON_PIN_H1},
  {BUTTON_KEY_H2, BUTTON_PIN_H2},
  {BUTTON_KEY_H3, BUTTON_PIN_H3},
  {BUTTON_KEY_V1, BUTTON_PIN_V1},
  {BUTTON_KEY_V2, BUTTON_PIN_V2}
};
 
const uint8_t buttonCount = sizeof(buttons) / sizeof(Button);
 
void setup() { 
  // Turn RX LED off (active low).
  pinMode(RX_LED_PIN, OUTPUT);
  digitalWrite(RX_LED_PIN, HIGH);

  // Turn TX LED off. See: https://www.electronicsweekly.com/blogs/engineer-in-wonderland/arduino-micro-direct-access-board-leds-2017-08/
  TXLED0;

  // Initialize LEDs.
  pinMode(ARMED_LED_PIN, OUTPUT);
  turnLedOff(ARMED_LED_PIN);

  pinMode(LED_PIN_V1, OUTPUT);  
  pinMode(LED_PIN_V2, OUTPUT);

  playSetupAnimation();
  
  turnLedFadedOn(LED_PIN_V1);
  turnLedFadedOn(LED_PIN_V2);

  // Initialize buttons.
  pinMode(ARMED_BUTTON_PIN, INPUT_PULLUP);
 
  for(int i = 0; i < buttonCount; i++){
    buttons[i].setup();
  }
}
 
void loop() {
  // Safety check: don't do anything if the ARMED_BUTTON_PIN is not connected to GND.
  if(!isButtonPressed(ARMED_BUTTON_PIN)) {
    turnLedOff(ARMED_LED_PIN);
    return;
  }

  turnLedOn(ARMED_LED_PIN);
  
  for(int i = 0; i < buttonCount; i++){
    buttons[i].update();
  }
}

void playSetupAnimation() {
  unsigned long delayMsec = 500;
  
  turnLedFadedOn(LED_PIN_V1);
  delay(delayMsec);
  turnLedOff(LED_PIN_V1);
  delay(delayMsec);
  turnLedFadedOn(LED_PIN_V2);
  delay(delayMsec);
  turnLedOff(LED_PIN_V2);
  delay(delayMsec);  
}

void turnLedOn(uint8_t ledPin) {
  digitalWrite(ledPin, HIGH);
}

void turnLedOff(uint8_t ledPin) {
  digitalWrite(ledPin, LOW);
}

void turnLedFadedOn(uint8_t ledPin) {
  analogWrite(ledPin, 1);
}

boolean isButtonPressed(uint8_t buttonPin) {
  return digitalRead(buttonPin) == LOW;
}
