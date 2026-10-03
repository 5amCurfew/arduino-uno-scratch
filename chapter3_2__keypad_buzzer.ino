// Explicitly include Arduino.h
#include "Arduino.h"
#include <Keypad.h>

const byte ROWS = 4;
const byte COLS = 4;

// The keypad is a matrix: each row and each column is a separate electrical line.
// When a key is pressed, it connects one row line to one column line and completes a circuit.
// The Keypad library scans these row/column connections and decides which key was pressed.
const byte ROW_PINS[ROWS] = { 5, 4, 3, 2 };
const byte COL_PINS[COLS] = { 6, 7, 8, 9 };

// This 2D array is the logical map of the keypad: it matches each row/column position
// to the character printed on the button. Using single quotes means a single character value.
const char BUTTONS[ROWS][COLS] = {
  { '1', '2', '3', 'A' },  // Row 0
  { '4', '5', '6', 'B' },  // Row 1
  { '7', '8', '9', 'C' },  // Row 2
  { '*', '0', '#', 'D' }   // Row 3
};

// Each button has a matching tone frequency. This gives us a 1:1 mapping between the
// pressed key and the beep we want to generate on the buzzer output pin.
const unsigned int TONES[ROWS][COLS] = {
  // a frequency tone for each button
  { 31, 93, 147, 208 },     // Row 1: Low bass notes
  { 247, 311, 370, 440 },   // Row 2: Low to mid tones
  { 523, 587, 698, 880 },   // Row 3: Higher tones
  { 1397, 2637, 3729, 0 }   // Row 4: High notes, 0 = silence
};

unsigned int tone_frequency = 0;  // Default to silence until a valid key press is found
const byte BUZZER_SIGNAL_PIN = 11;

// The Keypad object is told which pins are the row and column lines, and which character map
// to use. Internally, the library does a scan: it sets the row pins as inputs with pull-ups,
// drives one column pin low at a time, and checks which row pin drops low. If no key is pressed,
// the row stays high because there is no completed path. When a key is pressed, that row and
// column are connected, the row voltage is pulled low, and the library identifies which key
// was pressed. The resulting character is then used to decide what sound to play.
Keypad heroKeypad = Keypad(makeKeymap(BUTTONS), ROW_PINS, COL_PINS, ROWS, COLS);

void setup() {
  Serial.begin(9600);  // Serial Monitor is used to watch the button value as it is read
  pinMode(BUZZER_SIGNAL_PIN, OUTPUT);  // The buzzer pin is driven as an output to send the tone signal
}

void loop() {
  // waitForKey() blocks until a row/column circuit is detected, then returns the matching char.
  // That means the signal path is: button press -> row/column connection -> keypad scan -> character read
  char button_character = heroKeypad.waitForKey();
  Serial.println(button_character);  // Print the detected key so we can confirm which button was pressed

  // Search the button map to find the row and column position of the pressed key.
  // Once found, we copy the matching frequency value from the tones array into tone_frequency.
  for (byte i = 0; i < ROWS; i++) {
    for (byte j = 0; j < COLS; j++) {
      if (button_character == BUTTONS[i][j]) {
        tone_frequency = TONES[i][j];
      }
    }
  }

  // If the key maps to a tone value, send that frequency to the buzzer pin.
  // The Arduino tone() function drives the output pin with a square wave at that frequency,
  // which is what the piezo buzzer uses to create sound.
  if (tone_frequency) {
    tone(BUZZER_SIGNAL_PIN, tone_frequency);  // Output square-wave signal to the buzzer pin
    delay(100);  // Keep the buzzer active briefly so we hear the note
    noTone(BUZZER_SIGNAL_PIN);  // Stop the signal, turning the buzzer off
  }
};
