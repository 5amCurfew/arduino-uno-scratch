#include "Arduino.h" 

const byte GREEN_LED_INPUT_PIN = 2;
const byte AMBER_LED_INPUT_PIN = 3;
const byte RED_LED_INPUT_PIN = 4;

const byte GREEN_LED_OUTPUT_PIN = 10;
const byte AMBER_LED_OUTPUT_PIN = 11;
const byte RED_LED_OUTPUT_PIN = 12;

// Arrays to store input and output pins
const int inputPins[] = { GREEN_LED_INPUT_PIN, AMBER_LED_INPUT_PIN, RED_LED_INPUT_PIN };
const int outputPins[] = { GREEN_LED_OUTPUT_PIN, AMBER_LED_OUTPUT_PIN, RED_LED_OUTPUT_PIN };

void setup() {
  // Loop through all input pins and set them as INPUT
  for (int i = 0; i < 3; i++) {
    pinMode(inputPins[i], INPUT);
  }

  // Loop through all output pins and set them as OUTPUT
  for (int i = 0; i < 3; i++) {
    pinMode(outputPins[i], OUTPUT);
  }
}

void loop() {
  // Loop through all input-output pin pairs and control the LEDs
  for (int i = 0; i < 3; i++) {
    int state = digitalRead(inputPins[i]);
    digitalWrite(outputPins[i], state);
  }ddd
}
