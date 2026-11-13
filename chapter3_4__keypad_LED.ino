// Explicitly include Arduino.h
#include "Arduino.h"
#include <Keypad.h>

const byte ROWS = 4;
const byte COLS = 4;
const byte BUZZER_SIGNAL_PIN = 12;
const byte ROW_PINS[ROWS] = { 5, 4, 3, 2 };
const byte COL_PINS[COLS] = { 6, 7, 8, 9 };
const byte LED_RED_PIN = 11;
const byte LED_BLUE_PIN = 10;

// This 2D array is the logical map of the keypad: it matches each row/column position
// to the character printed on the button. Using single quotes means a single character value.
const char BUTTONS[ROWS][COLS] = {
  { '1', '2', '3', 'A' },  // Row 0
  { '4', '5', '6', 'B' },  // Row 1
  { '7', '8', '9', 'C' },  // Row 2
  { '*', '0', '#', 'D' }   // Row 3
};

Keypad heroKeypad = Keypad(makeKeymap(BUTTONS), ROW_PINS, COL_PINS, ROWS, COLS);

const byte PIN_LENGTH = 4;
char current_pin[PIN_LENGTH] = { '0', '0', '0', '0' };
bool access_allowed;

////////////////////////////////////////////////////////////////////////////////////////////////////////
bool validatePIN() {
    Serial.println("Enter PIN to continue.");
    char candidate[PIN_LENGTH];
    for (int i = 0; i < PIN_LENGTH; i++) {
        char button_character = heroKeypad.waitForKey();
        tone(BUZZER_SIGNAL_PIN, 880, 100);
        Serial.print("*");
        candidate[i] = button_character;
    }
    Serial.println();
    if (memcmp(candidate, current_pin, PIN_LENGTH) == 0) { // Compare the entered PIN with the current PIN
        Serial.println("Device Successfully Unlocked!");
        return true;
    } else {
        Serial.println("Incorrect PIN.");
        return false;
    }
};

////////////////////////////////////////////////////////////////////////////////////////////////////////
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
void giveSuccessFeedback() {
    tone(BUZZER_SIGNAL_PIN, 1397, 200);
    displayColour(122, 122);  // Purple
    delay(1000);
    displayColour(0, 0);
}

void giveFailureFeedback() {
    tone(BUZZER_SIGNAL_PIN, 1397, 200);
    displayColour(255, 0);  // Red
    delay(1000);
    displayColour(0, 0);
}

void giveKeyFeedback(char key) {
    tone(BUZZER_SIGNAL_PIN, 880, 100);
    displayColour(0, 255);  // Blue
    delay(50);
    displayColour(0, 0);
}

void displayColour(byte red_intensity, byte blue_intensity) {
  analogWrite(LED_RED_PIN, red_intensity);
  analogWrite(LED_BLUE_PIN, blue_intensity);
}



////////////////////////////////////////////////////////////////////////////////////////////////////////
void setup() {
    Serial.begin(9600);  // Serial Monitor is used to watch the button value as it is read

    pinMode(BUZZER_SIGNAL_PIN, OUTPUT);  // The buzzer pin is driven as an output to send the tone signal
    pinMode(LED_RED_PIN, OUTPUT);
    pinMode(LED_BLUE_PIN, OUTPUT);

    access_allowed = false;
    
    delay(200);
    Serial.println("Press * to enter new PIN or # to access the system.");
}

void loop() {
    char button_character = heroKeypad.waitForKey();
    giveKeyFeedback(button_character);

    if (button_character == '#') {
        access_allowed = validatePIN();
        if (access_allowed) {
            giveSuccessFeedback();
            Serial.println("Welcome, authorized user. You may now begin using the system.");
        } else {
            giveFailureFeedback();
            Serial.println("Access Denied.");
            Serial.println("\nPress * to enter new PIN or # to access the system.");
        }
    }

    if (button_character == '*') {    
        if (access_allowed) {
            Serial.println("Welcome, authorized user. Please Enter a new PIN: ");
            
            for (int i = 0; i < PIN_LENGTH; i++) {
                button_character = heroKeypad.waitForKey();
                giveKeyFeedback(button_character);
                
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