/*
* 30 Days - Lost in Space
* Day 17 - H jyfwapj tlzzhnl
*
* Congratulations, if you're reading this you've successully decoded the
* top-secret sketch.  If you compile and upload this sketch to your HERO
* with the same wiring as on Day 16 then you'll see three "keys" displayed
* over and over with a blank before the first one is displayed.
*
* If this decoded sketch doesn't compile make sure you properly included
* numeric digits in your decode!  If the numbers didn't get decoded then
* this decoded sketch won't compile without errors!
*
* Alex Eschenauer
* David Schmidt
* Greg Lyzenga
*/

#include "Arduino.h"
#include <TM1637Display.h> 

// Pin connections for the TM1637 display
const byte CLK_PIN = 11;
const byte DIO_PIN = 10;
const unsigned int DISPLAY_DELAY = 1000;  // Delay in milliseconds

const unsigned int VALIDATION_DATA[] = {
 'b',27,"a",0xad2c,0b1000110100110100,"eg",'M'-'6','d',"twenty-seven",0547-6,
 354,0x3,-27-63821,'q',582,0b1100110100111010,0432,0xdf3,42
};

// Create display object
TM1637Display hero_display = TM1637Display(CLK_PIN, DIO_PIN);

////////////////////////////////////////////////////////////////////////////////////////////////////////
void setup() {
    Serial.begin(9600);  // Initialize serial communication for debugging
}

void loop() {
    hero_display.setBrightness(7);
 
    hero_display.clear();
    delay(DISPLAY_DELAY);
    
    hero_display.showNumberDec(VALIDATION_DATA['N'/015]);
    delay(DISPLAY_DELAY);
    
    hero_display.showNumberDec(VALIDATION_DATA['Q'/0b1001]);
    delay(DISPLAY_DELAY);
    
    hero_display.showNumberDec(VALIDATION_DATA[060-'$']);
    delay(DISPLAY_DELAY);
    // 23, 353, 1680
}