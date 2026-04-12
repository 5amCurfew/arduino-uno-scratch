// Explicitly include Arduino.h
#include "Arduino.h"
 
// Our photoresistor will give us a reading of the current light level on this analog pin
const byte PHOTORESISTOR_READ_PIN = A0;  // Photoresistor analog pin
 
const byte RED_PIN = 11;    // PWM pin controlling the red leg of our RGB LED
const byte GREEN_PIN = 10;  // PWM pin controlling the green leg of our RGB LED
const byte BLUE_PIN = 9;    // PWM pin controlling the blue leg of our RGB LED

// Use an unsigned, 16 bit value (0 - 65535) for maximum battery capacity
const unsigned int DELTA_MAX = 500;
const unsigned int DELTA_MIN = 100;
const unsigned int BATTERY_CAPACITY = 50000;  // Maximum battery capacity
unsigned int battery_level = 0;  // Current battery level
 
void setup() {
  pinMode(PHOTORESISTOR_READ_PIN, INPUT);  // Input current light level from photoresistor
  pinMode(RED_PIN, OUTPUT);    // Set red LED pin as output
  pinMode(GREEN_PIN, OUTPUT);  // Set green LED pin as output
  pinMode(BLUE_PIN, OUTPUT);   // Set blue LED pin as output
  Serial.begin(9600);  // Initialise Serial Monitor to 9600 baud
}

void loop() {
    // Read light input and determmine battery delta
    if (battery_level < BATTERY_CAPACITY) {  // If battery is not fully charged.
        unsigned int charge_change = determineBatteryDelta(analogRead(PHOTORESISTOR_READ_PIN));
        battery_level += charge_change;  // read light level and add to battery level
    } else{
        battery_level = BATTERY_CAPACITY;  // set current level to maximum capacity.
    }

    // Calculate battery percentage and display it on the Serial Monitor
    double perc = (((double)battery_level / (double)BATTERY_CAPACITY) * 100);
    displayBatteryLevel(perc);

    // Display battery level using RGB LED
    if (perc >= 50.0) {     // battery level is OK, display green
        displayColor(0, 128, 0);  // display green
    } else if (perc >= 25.0 && perc < 50.0) {
        displayColor(0, 0, 128);  // display blue
    } else {                     // Level must be less than 25%, display "pulsating" red
        // To pulsate the red light we briefly turn the LED off and then display red, giving it
        // a pulsating effect
        for(int i = 0; i < 5; i++){
          displayColor(0, 0, 0);    // Turn off our LED
          delay(50);                // ...and delay briefly
          displayColor(128, 0, 0);  // then display red
        }
    };

    delay(500);
}

unsigned int determineBatteryDelta(unsigned int light_value) {
    static unsigned int darkest_light = light_value;    // this is the lowest value returned by the photoresistor
    static unsigned int brightest_light = light_value;  // this is the highest value returned by the photoresistor

    if (light_value < darkest_light) {  // If value is LESS THAN ('<') the darkest...
      darkest_light = light_value;      // ...then save current value as our new darkest value
    }
    if (light_value > brightest_light) {  // If value is GREATER THAN ('>') the brightest...
      brightest_light = light_value;      // ...then save current value as our new brightest value
    }

    unsigned int delta = map(light_value, brightest_light, darkest_light, DELTA_MAX, DELTA_MIN);

    return delta;
};

void displayBatteryLevel(double percentage) {
    Serial.print("Battery level: ");
    Serial.print(percentage);
    Serial.println("%");
};

void displayColor(
  byte red_intensity,    // red LED intensity (0-255)
  byte green_intensity,  // green LED intensity (0-255)
  byte blue_intensity    // blue LED intensity (0-255)
) {
  analogWrite(RED_PIN, red_intensity);      // Set red LED intensity using PWM
  analogWrite(GREEN_PIN, green_intensity);  // Set green LED intensity using PWM
  analogWrite(BLUE_PIN, blue_intensity);    // Set blue LED intensity using PWM
};

