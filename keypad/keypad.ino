/*
Root Ventures Keypad

This is a basic sketch for capturing keypress events and blinking some leds on
the board. It is intended as a starting point for building your own projects.
This sketch ignores the jumpers on the back of the PCB.

Good reference for the codes for various keys:
https://www.arduino.cc/reference/en/language/functions/usb/keyboard/keyboardmodifiers/

Full list of defined keycodes:
https://github.com/arduino-libraries/Keyboard/blob/master/src/Keyboard.h
*/

#include <Keyboard.h>

#define DEBUG false
#define MAX_UINT32 4294967295
#define LONGPRESS 450

#define BUTTON1 6
#define BUTTON2 7
#define BUTTON3 8
#define BUTTON4 9

struct ButtonState {
  const byte pin;
  boolean previousState;
  unsigned long pressedAt;
  unsigned long releasedAt;
};

struct ButtonState Buttons[4] = {
  {BUTTON1, LOW, 0, 0},
  {BUTTON2, LOW, 0, 0},
  {BUTTON3, LOW, 0, 0},
  {BUTTON4, LOW, 0, 0}
};

void setup() {
  if (DEBUG) {
    Serial.begin(9600);
    while (!Serial) {} // wait for the serial port to connect for debug messages
  }

  // These inputs don't have pull up resistors on them, so they *must* use the internal pull up mode
  pinMode(BUTTON1, INPUT_PULLUP);
  pinMode(BUTTON2, INPUT_PULLUP);
  pinMode(BUTTON3, INPUT_PULLUP);
  pinMode(BUTTON4, INPUT_PULLUP);

  // functionally disables the onboard RX/TX LEDs so they're not blinking blinding light all the time
  pinMode(17, INPUT);
  pinMode(30, INPUT);

  // initialize control over the keyboard
  Keyboard.begin();
}

void loop() {
  for (int i = 0; i < 4; i++) {
    // the buttons are pulled up so they will read 0 when the button is pressed
    // we invert on read to get a HIGH when pressed
    boolean currentState = digitalRead(Buttons[i].pin) ? LOW : HIGH;

    // the button is newly pressed - mark the time when this occurred
    if (currentState && !Buttons[i].previousState) {
      Buttons[i].pressedAt = millis();
      
    // the button is newly released - mark the time when this occurred
    } else if (!currentState && Buttons[i].previousState) {
      Buttons[i].releasedAt = millis();
      handleButtonRelease(&Buttons[i]);      
    }

    // remember to move the current state to the previous button state
    Buttons[i].previousState = currentState;
  }

  delay(25);
}

void handleButtonRelease(struct ButtonState *button) {
  // Figure out how long the button was pressed. With 32 bit unsigned integer
  // storage, the `millis()` call will rollover after 50 days of runtime.
  unsigned long duration = 0;
  if (button->pressedAt <= button->releasedAt) {
    duration = button->releasedAt - button->pressedAt;
  } else {
    duration = button->pressedAt + (MAX_UINT32 - button->releasedAt);
  }

  switch(button->pin) {
    case BUTTON1 :
      debugButton(button);
      break;
    case BUTTON2 :
      debugButton(button);
      break;
    case BUTTON3 :
      debugButton(button);
      break;
    case BUTTON4 :
      debugButton(button);
      break;
  }
}

void debugButton(struct ButtonState *button) {
  if (DEBUG) {
    Serial.print("Button: ");
    Serial.print(button->pin);            Serial.print(", ");
    Serial.print(button->previousState);  Serial.print(", ");
    Serial.print(button->pressedAt);      Serial.print(", ");
    Serial.print(button->releasedAt);     Serial.print("\n");
  }
}