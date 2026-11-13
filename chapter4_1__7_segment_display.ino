#include "Arduino.h"
#include <TM1637Display.h> 

// Pin connections for the TM1637 display
const byte CLK_PIN = 11;
const byte DIO_PIN = 10;

// Create display object
TM1637Display lander_display = TM1637Display(CLK_PIN, DIO_PIN);

const byte all_on[] = { 
    0b11111111,
    0b11111111,
    0b11111111,
    0b11111111 
};

////////////////////////////////////////////////////////////////////////////////////////////////////////
void setup() {
    Serial.begin(9600);  // Initialize serial communication for debugging
    lander_display.setBrightness(7);  // Set brightness (0-7)
}

void loop() {
    // Clear the display (all segments off)
    lander_display.clear();
    delay(1000);

    // Light up all segments of the display  
    lander_display.setSegments(all_on);
    delay(1000);

    // Clear the display (all segments off)
    lander_display.clear();
    delay(1000);

    for (int i = 0; i < 4; i++) {
        lander_display.showNumberDecEx(1200, 0b01000000);
        delay(500);
        lander_display.clear();
        delay(500);
  }

  // Show counter including negative numbers
  for (int i = -100; i <= 100; i++) {
    lander_display.showNumberDec(i);
    delay(50);
  }
  delay(1000);
}