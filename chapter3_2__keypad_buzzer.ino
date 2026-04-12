// Explicitly include Arduino.h
#include "Arduino.h"
#include <Keypad.h>

const byte ROWS = 4;
const byte COLS = 4;

// on a button press, a circuit between one row pin and one column pin is completed. 
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

const unsigned int TONES[ROWS][COLS] = {
  // a frequency tone for each button
  { 31, 93, 147, 208 },     // Row 1: Low bass notes
  { 247, 311, 370, 440 },   // Row 2: Low to mid tones
  { 523, 587, 698, 880 },   // Row 3: Higher tones
  { 1397, 2637, 3729, 0 }   // Row 4: High notes, 0 = silence
};

unsigned int tone_frequency = 0;  // Default to silence
const byte BUZZER_INPUT_PIN = 11;

// Here it sets the pin pinMode, digitalWrite(_pin, 1)
// for reference, see the library
Keypad heroKeypad = Keypad(makeKeymap(BUTTONS), ROW_PINS, COL_PINS, ROWS, COLS);

void setup() {
  Serial.begin(9600);  // Initialise Serial Monitor to 9600 baud
  pinMode(BUZZER_INPUT_PIN, OUTPUT);  // Set buzzer pin as output
}

void loop() {
  char button_character = heroKeypad.waitForKey();
  Serial.println(button_character);

  // Map back to keypad position to then map to tone
  for (byte i = 0; i < ROWS; i++) {       // Search through each row
      for (byte j = 0; j < COLS; j++) {   // Search through each column
          if (button_character == BUTTONS[i][j]) {  // Found a match!
              tone_frequency = TONES[i][j];         // Get corresponding tone
          }
      }
  }

  // If a button is pressed, activate the buzzer
  if (tone_frequency) {
    tone(BUZZER_INPUT_PIN, tone_frequency);  // Turn on the buzzer
    delay(100);  // Keep the buzzer on for 100 milliseconds
    noTone(BUZZER_INPUT_PIN);  // Turn off the buzzer
  }
};
