// Explicitly include Arduino.h
#include "Arduino.h"
#include <Keypad.h>

const byte ROWS = 4;
const byte COLS = 4;

// on a button press, a circuit between one row pin and one column pin is comlpeted. 
// The keypad library detects this connection pattern in microseconds.
const byte ROW_PINS[ROWS] = { 5, 4, 3, 2 };
const byte COL_PINS[COLS] = { 6, 7, 8, 9 };

// For a single character we need to use single quotes to indicate that there
// is just ONE character ('A')
const char BUTTONS[ROWS][COLS] = {
  { '1', '2', '3', 'A' },  // Row 0
  { '4', '5', '6', 'B' },  // Row 1
  { '7', '8', '9', 'C' },  // Row 2
  { '*', '0', '#', 'D' }   // Row 3
};

// Here it sets the pin pinMode, digitalWrite(_pin, 1)
// for reference, see the library
Keypad heroKeypad = Keypad(makeKeymap(BUTTONS), ROW_PINS, COL_PINS, ROWS, COLS);

void setup() {
  Serial.begin(9600);  // Initialise Serial Monitor to 9600 baud
}

void loop() {
  char pressedButton = heroKeypad.waitForKey();
  Serial.println(pressedButton);
}
