/*
 * Arduino concepts introduced/documented in this lesson.
 * - analogWrite(): Used to control a PWM pin, giving a variable intensity
 * - Passing variables into functions
 *
 * Parts and electronics concepts introduced in this lesson.
 * - Common Cathode (single grounded pin) RGB LED.
 */
 
// Explicitly include Arduino.h
#include "Arduino.h"
 
/*
 * Each color in an RGB LED is controlled with a different pin on our HERO board.
 *
 * NOTE: Only pins 3, 5, 6, 9, 10 and 11 on the HERO board support PWM which is
 *       indicated on the board by preceding those pin numbers on the HERO board
 *       with a tilde ('~') character.  Only those pins support PWM and analogWrite().
 */

//  A normal digital output is binary: either 0 V or 5 V.
//  PWM rapidly alternates between 0 V and 5 V.
//  The fraction of time spent HIGH determines the effective analog level.
//  It is producing a fast binary waveform whose average value over time represents a range from 0 to 255.
//  effective average voltage ≈ 5V × (PWM value / 255)

const byte RED_PIN = 11;    // PWM pin controlling the red leg of our RGB LED
const byte GREEN_PIN = 10;  // PWM pin controlling the green leg of our RGB LED
const byte BLUE_PIN = 9;    // PWM pin controlling the blue leg of our RGB LED
const unsigned int DELAY = 500;
int i;

void setup() {
  // Set each of our PWM pins as OUTPUT pins
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);

  Serial.begin(9600);  // Initialize Serial Monitor to 9600 baud
}
 
// Each time through loop() we display some of the color variations available
// using an RGB LED.
void loop() {
  // First demonstrate our different PWM levels by slowly brightening our red LED

  displayColor(255, 0, 0);
  delay(2*DELAY);
  displayColor(0, 255, 0);
  delay(2*DELAY);
  displayColor(0, 0, 255);
  delay(2*DELAY);
  for (i = 0; i < 5; i++){
    displayColor(randomIntensity(), randomIntensity(), randomIntensity());
    delay(DELAY);
  }
  displayColor(0, 0, 0);  // OFF!
  delay(2*DELAY);
}
 
/*
 * displayColor() is a function that accepts three parameters representing the desired
 * intensity for each of the LEDs in the RGB LED.
 *
 * Each parameter passed must have a type (here we match what analogWrite() will use) and
 * a name to be used inside the function to refer to the parameter.  The parameters can all
 * be included on a single line like:
 * void displayColor( byte red_intensity, byte green_intensity, byte blue_intensity) {
 *
 * However, if we display each parameter on it's own line we can add a comment to each
 * for additional clarity.
 */
void displayColor(
  byte red_intensity,    // red LED intensity (0-255)
  byte green_intensity,  // green LED intensity (0-255)
  byte blue_intensity    // blue LED intensity (0-255)
) {
  Serial.print("R: ");
  Serial.print(red_intensity);
  Serial.print(" G: ");
  Serial.print(green_intensity);
  Serial.print(" B: ");
  Serial.println(blue_intensity);
  analogWrite(RED_PIN, red_intensity);      // Set red LED intensity using PWM
  analogWrite(GREEN_PIN, green_intensity);  // Set green LED intensity using PWM
  analogWrite(BLUE_PIN, blue_intensity);    // Set blue LED intensity using PWM
}

byte randomIntensity() {
  return (byte)random(256);
}