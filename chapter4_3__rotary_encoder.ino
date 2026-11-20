// Chapter 4.3: Rotary encoder driving a 4-digit 7-segment display
//
// CIRCUIT OVERVIEW
// ----------------
// Rotary encoder:
//   - The encoder is a mechanical part containing two simple switches. 
//     The Arduino works out what happened by repeatedly reading the state of those switches.
//   - The two switches are called A (CLK) and B (DT).
//   - Inside, a notched disc turns with the knob. As it turns, switch A and
//     switch B each connect to / disconnect from the common pin (GND). The
//     contacts are offset, so the switches change one after the other, not
//     at the same time (a "90 degrees out of phase" pattern).

//   With the pull-ups, a closed switch reads 0 (LOW), an open one reads 1
//   (HIGH). Turning the knob steps A and B through this sequence:
//
//        A  B
//        1  1   <- rest
//        0  1
//        0  0
//        1  0
//        1  1   <- back at rest = one click
//
//   Turning one way runs the sequence forwards; turning the other way runs it
//   backwards. Whether A or B changes first therefore gives the direction.
//   One click of the knob = one full cycle of 4 steps, which the library
//   counts as +1 or -1.
//
//   encoder.service() reads A and B and compares them with the previous
//   reading. If they differ, the library works out the direction and adds
//   or subtracts one step. loop() must therefore run fast and never block
//   (e.g. with delay()), or steps will be missed.
//
//   Encoder pin   Arduino pin   Notes
//   -----------   -----------   ----------------------------------------
//   CLK (A)       D2            Switch A
//   DT  (B)       D3            Switch B
//   GND / C       GND           Common pin of both switches
//
// TM1637 display module:
//   - A 4-digit 7-segment display with a driver chip on the back.
//   - It uses a 2-wire serial-like protocol (not I2C, but similar), so the
//     Arduino drives 4 digits / 28 segments using only two signal pins.
//
//   Display pin   Arduino pin   Notes
//   -----------   -----------   ----------------------------------------
//   CLK           D11           Clock line: Arduino -> display
//   DIO           D10           Bidirectional data line
//   VCC           5V            Power
//   GND           GND           Ground

#include "Arduino.h"
#include <TM1637Display.h>
#include <BasicEncoder.h>

// Pin connections for the TM1637 display
const byte CLK_PIN = 11;
const byte DIO_PIN = 10;

// Pin connections for the rotary encoder (A and B switches)
const byte ENCODER_CLK_PIN = 2;
const byte ENCODER_DT_PIN = 3;

// Decodes the A/B switch pattern into a running step count.
// The constructor also sets both pins to INPUT_PULLUP.
BasicEncoder encoder(ENCODER_CLK_PIN, ENCODER_DT_PIN);

// Sends digits to the TM1637 over its two-wire interface
TM1637Display display(CLK_PIN, DIO_PIN);

void setup() {
  display.setBrightness(7);  // 0 (dim) to 7 (brightest)
  display.showNumberDec(0);  // Start at 0 until the knob is turned
}

void loop() {
  // Reads the A and B pins and compares them with the last reading. If they
  // changed, the direction is worked out and the internal count is moved by
  // +1 or -1. Must be called often so that no transitions are missed.
  encoder.service();

  // get_change() does not read the pins. It returns the number of whole
  // clicks since the last call (0 if the knob has not moved a full click).
  // Redrawing only then avoids needless traffic on the display's bus.
  if (encoder.get_change()) {
    // get_count() is the running total of clicks since start-up. One
    // direction increases it, the other decreases it (it can go negative).
    display.showNumberDec(encoder.get_count());
  }
}
