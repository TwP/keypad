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

#define BUTTON1 6
#define BUTTON2 7
#define BUTTON3 8
#define BUTTON4 9


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
  // put your main code here, to run repeatedly:

}
