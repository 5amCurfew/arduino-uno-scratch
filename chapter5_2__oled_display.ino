#include "Arduino.h"
#include "Wire.h"  // I2C (two-wire) library used to talk to the OLED

#include <U8g2lib.h>  // Graphics library for monochrome displays

// Construct our display object:
//   SH1106      - display controller chip (SSD1306 modules need a different class)
//   128X64      - resolution in pixels
//   F           - full-buffer mode: the whole frame is drawn in RAM (1 KB), then sent at once
//   HW_I2C      - use the Uno's hardware I2C pins
//   U8G2_R0     - no rotation
//   reset       - this module has no reset pin wired up, so none is used
U8G2_SH1106_128X64_NONAME_F_HW_I2C lander_display(U8G2_R0, /* reset=*/U8X8_PIN_NONE);

// Vertical position of the lander on screen (0 = top edge). Never changed, so the
// lander only moves horizontally.
static byte y_offset = 0;

////////////////////////////////////////////////////////////////////////////////////////////////////////
// Draws a string horizontally centered on the display, with its top at row y.
// (Currently unused by the animation below.)
void drawCenteredString(byte y, char *string) {
  // Free space left over after the text, split evenly on both sides
  byte centered_x = (lander_display.getDisplayWidth() - lander_display.getStrWidth(string)) / 2;
  lander_display.drawStr(centered_x, y, string);
}

// Arduino UNO I2C pins
//  A4 - SDA
//  A5 - SCL

// Draws the lander ship from simple shapes. (x_location, y_location) is the top-left
// corner of its bounding box; the ship is about 20 px wide and 25 px tall.
// Shapes are drawn into the buffer only; sendBuffer() is needed to show them.
void display_lander(byte x_location, byte y_location) {
  lander_display.drawFrame(x_location + 7, y_location, 6, 5);        // ship top
  lander_display.drawFrame(x_location + 5, y_location + 4, 10, 20);  // ship center
  lander_display.drawFrame(x_location, y_location + 6, 6, 16);       // left pod
  lander_display.drawFrame(x_location + 14, y_location + 6, 6, 16);  // right pod
  lander_display.drawTriangle(x_location + 2, y_location + 21,
                              x_location, y_location + 25,
                              x_location + 4, y_location + 25);      // left nozzle
  lander_display.drawTriangle(x_location + 18, y_location + 21,
                              x_location + 15, y_location + 25,
                              x_location + 20, y_location + 25);     // right nozzle
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
void setup() {
    Serial.begin(9600);
    lander_display.begin();  // Initialize I2C and the display controller
    lander_display.setFont(u8g2_font_ncenB08_tr);
}

void loop(void) {
  // Run 52 * 8 = 416 animation frames, then loop() restarts and repeats
  const byte TEST_PAGE_COUNT = 52;
  for (unsigned int display_frame = 0; display_frame < (TEST_PAGE_COUNT * 8); display_frame++) {
    lander_display.clearBuffer();  // clear the internal memory
    
    // Font configuration for consistent text rendering (no text is drawn at the moment)
    lander_display.setFont(u8g_font_6x10);
    lander_display.setFontRefHeightExtendedText();
    lander_display.setFontPosTop();


    // display_frame & 0b111 keeps only the low 3 bits, so x cycles 0..7 and the
    // lander shifts one pixel right per frame, then jumps back to the left.
    display_lander(display_frame & 0b00000111, y_offset);
    
    lander_display.sendBuffer();  // Transfer buffer contents to display
    delay(100);                   // 100ms pause creates viewable animation speed
  }
}