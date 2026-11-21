#include "Arduino.h"
#include <U8g2lib.h> 

U8G2_SH1106_128X64_NONAME_F_HW_I2C lander_display(U8G2_R0, /* reset=*/U8X8_PIN_NONE);

////////////////////////////////////////////////////////////////////////////////////////////////////////
void drawCenteredString(byte y, char *string) {
  byte centered_x = (lander_display.getDisplayWidth() - lander_display.getStrWidth(string)) / 2;
  lander_display.drawStr(centered_x, y, string);
}

// Arduino UNO I2C pins
//  A4 - SDA
//  A5 - SCL

////////////////////////////////////////////////////////////////////////////////////////////////////////
void setup() {
    Serial.begin(9600);
    delay(1000);
    lander_display.begin();
    
    lander_display.setFont(u8g2_font_ncenB08_tr);
}

void loop() {
    // Save the number of vertical pixels required for the tallest character
    // in the current font.  This is used later to properly position text on
    // our display.
    byte font_height = lander_display.getMaxCharHeight();

    lander_display.clearBuffer();  // clear the internal memory
    lander_display.setFontPosTop();

    // Title line for our display
    drawCenteredString(0, "Exploration Lander");

    // Display our "Hello World!" message on line 2 (moving down "font_height" bits)
    drawCenteredString(font_height, "Hello World!");
    lander_display.sendBuffer();
    delay(500);
    drawCenteredString(font_height*2, "I am 5am");
    lander_display.sendBuffer();
    delay(500);
}