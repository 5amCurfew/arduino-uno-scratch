// Explicitly include Arduino.h
#include "Arduino.h"
#include <Keypad.h>

const byte ROWS = 4;
const byte COLS = 4;
const byte BUZZER_SIGNAL_PIN = 11;
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

Keypad heroKeypad = Keypad(makeKeymap(BUTTONS), ROW_PINS, COL_PINS, ROWS, COLS);

const byte PIN_LENGTH = 4;
char current_pin[PIN_LENGTH] = { '0', '0', '0', '0' };
bool access_allowed;

bool validatePIN() {
    Serial.println("Enter PIN to continue.");
    
    for (int i = 0; i < PIN_LENGTH; i++) {
        char button_character = heroKeypad.waitForKey();
        tone(BUZZER_SIGNAL_PIN, 880, 100);
        
        if (current_pin[i] != button_character) {
            Serial.println();
            Serial.print("WRONG PIN DIGIT: ");
            Serial.println(button_character);
            return false;
        }
        Serial.print("*");
    }
    
    Serial.println();
    Serial.println("Device Successfully Unlocked!");
    return true;
};

bool enterNewPIN() {
    if (!access_allowed) {
        Serial.println("Access Denied. You must unlock the device first.");
        return false;
    }
    Serial.println("Enter new PIN to continue.");
  
    for (int i = 0; i < PIN_LENGTH; i++) {
        char button_character = heroKeypad.waitForKey();
        tone(BUZZER_SIGNAL_PIN, 880, 100);
    
        current_pin[i] = button_character;
        Serial.print("*");
    }

    Serial.println();
    Serial.println("New PIN Successfully Set!");
    return true;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////

void setup() {
    Serial.begin(9600);  // Serial Monitor is used to watch the button value as it is read
    pinMode(BUZZER_SIGNAL_PIN, OUTPUT);  // The buzzer pin is driven as an output to send the tone signal
    access_allowed = false;
    
    delay(200);
    Serial.println("Press * to enter new PIN or # to access the system.");
}

void loop() {
    char button_character = heroKeypad.waitForKey();
    tone(BUZZER_SIGNAL_PIN, 880, 100);

    if (button_character == '#') {
        access_allowed = validatePIN();
        if (access_allowed) {
            Serial.println("Welcome, authorized user. You may now begin using the system.");
        } else {
            Serial.println("Access Denied.");
            Serial.println("\nPress * to enter new PIN or # to access the system.");
        }
    }

    if (button_character == '*') {    
        if (access_allowed) {
            Serial.println("Welcome, authorized user. Please Enter a new PIN: ");
            
            for (int i = 0; i < PIN_LENGTH; i++) {
                button_character = heroKeypad.waitForKey();
                tone(BUZZER_SIGNAL_PIN, 880, 100);
                
                current_pin[i] = button_character;
                Serial.print("*");
        }
        
            Serial.println();
            access_allowed = false;
            Serial.println("PIN Successfully Changed!");
        } else {
            Serial.println("Access Denied. Cannot change PIN without being authorised");
            Serial.println("\nPress * to enter new PIN or # to access the system.");
        }
  }
}