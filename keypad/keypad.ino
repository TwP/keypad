/*
TonerPad

Have you run out of printer toner? Do you remember the exact model number of
toner cartidge for your printer? With this sketch you don't have to! Each button
will take you to the product page for a particular toner color. A long press
will take you to the high-yield toner page. Just plug the TonerPad into your mac
computer and never worry about remembering those pesky product details again.
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

struct LedState {
  byte blinks;
  boolean state;
  unsigned long changedAt;
};

struct LedState Led = {0, LOW, 0};

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

  handleBlinks();
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

  // a longpress will take us to the high yeild toner catridges
  switch(button->pin) {
    case BUTTON1 :
      if (duration < LONGPRESS) openUrl("https://www.brother-usa.com/products/tn221c");
      else                      openUrl("https://www.brother-usa.com/products/tn225c");
      break;
    case BUTTON2 :
      if (duration < LONGPRESS) openUrl("https://www.brother-usa.com/products/tn221m");
      else                      openUrl("https://www.brother-usa.com/products/tn225m");
      break;
    case BUTTON3 :
      if (duration < LONGPRESS) openUrl("https://www.brother-usa.com/products/tn221y");
      else                      openUrl("https://www.brother-usa.com/products/tn225y");
      break;
    case BUTTON4 :
      // Brother doesn't produce a high yield black toner cartidge
      openUrl("https://www.brother-usa.com/products/tn221bk");
      break;
  }

  if (DEBUG) {
    debugButton(button);
    Serial.print("Duration: ");
    Serial.print(duration);  Serial.print("\n");
  }
}

void openUrl(String url) {
  Keyboard.press(KEY_LEFT_GUI);
  Keyboard.write(' ');
  Keyboard.releaseAll();
  
  for (int i = 0; i < url.length(); i++) {
    Keyboard.write(url[i]);
  }

  Keyboard.write(KEY_RETURN);
}

void handleBlinks() {
  if (Led.blinks > 0) {
    // Figure out how long the LED has been in its current state taking into account `millis()` rollover.
    unsigned long now = millis();
    unsigned long duration = 0;
    if (now >= Led.changedAt) {
      duration = now - Led.changedAt;
    } else {
      duration = now + (MAX_UINT32 - Led.changedAt);
    }
    
    // when the LED is off, we will turn it on
    if (Led.state == LOW) {
      // but only if it has been off for at least 100ms
      if (duration >= 100) {
        Led.state = HIGH;
        Led.changedAt = now;
        pinMode(17, OUTPUT);
      }

    // otherwise we will turn the LED off
    } else {
      // but only if it has been on for at least 150ms
      if (duration >= 150) {
        Led.blinks--;  // we decrement our blinks counter when turning off
        Led.state = LOW;
        Led.changedAt = now;
        pinMode(17, INPUT);
      }
    }
  }
}

void debugButton(struct ButtonState *button) {
  Serial.print("Button: ");
  Serial.print(button->pin);            Serial.print(", ");
  Serial.print(button->previousState);  Serial.print(", ");
  Serial.print(button->pressedAt);      Serial.print(", ");
  Serial.print(button->releasedAt);     Serial.print("\n");
}