#include "Arduino.h" 

#define LED_PIN 12
#define LED_SWITCH_PIN 2

void setup() {
  pinMode(LED_PIN, OUTPUT);
  pinMode(LED_SWITCH_PIN, INPUT);
  //Serial.begin(9600);
}

void loop() {
  //Serial.print(digitalRead(LED_SWITCH_PIN));

  /*
  When the switch is closed, the current primarily flows from the 5V supply to the input pin (connected to the Arduino) 
  instead of the pull-down resistor because of the path of least resistance. 

  When the switch is open, the input pin LED_SWITCH_PIN is not connected to the 5V supply anymore, leaving the pin "floating" or undefined. 
  Without the pull-down resistor, the input pin LED_SWITCH_PIN is in a floating state, resulting in unpredictable readings. 
  The pull-down resistor provides a controlled path for current to flow from the input pin to ground, 
  ensuring the pin is at a definite LOW (0V) state when the switch is open.

  Switch Closed:
    The input pin is directly connected to 5V.
    The pull-down resistor is largely bypassed, and the input pin reads HIGH (1).
  Switch Open:
    The input pin is not connected to 5V.
    The pull-down resistor ensures the input pin is at 0V, by allowing a small current to flow from the input pin through the resistor to ground, 
    forcing the Arduino to read LOW (0).
  */

  if (digitalRead(LED_SWITCH_PIN) == HIGH){
    digitalWrite(LED_PIN, HIGH);
  } else{
    digitalWrite(LED_PIN, LOW);
  }

}
