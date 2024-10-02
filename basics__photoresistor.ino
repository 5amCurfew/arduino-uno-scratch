/*
 * Arduino concepts
 * - unsigned int: A 16 bit value containing numbers from 0 to 65535
 * - Serial Monitor: Allows the HERO to display text in an Arduino IDE window.
 * - Serial.begin(): Used to initialize the Serial Monitor.
 * - Serial.print(): Display some text in the Arduino IDE Serial Monitor window.
 * - Serial.println(): Display test in the Serial Monitor followed by a newline.
 * - analogRead(): Read a value from an analog pin that is based on how much voltage is on the pin (0-5v)
 *
 * Parts and electronics concepts introduced in this lesson.
 * - Analog pins: Pins on the HERO that can read many different values instead of just HIGH/LOW.
 * - Photo Resistor: Changes it's resistance depending on how much light it senses.
 */

/*
When setting a pin to INPUT mode:
1. Voltage Sensing: The pin is used to sense voltage levels, either reading an analog signal (for analog pins) or a high/low digital signal (for digital pins). The pin does not provide power but instead reads the state of the external circuit.

2. High Impedance: In input mode, the pin is in a high-impedance state, which means it has very high resistance. This allows it to read the voltage without significantly affecting the external circuit. In essence, the pin draws very little current from the circuit, just enough to measure the voltage.

3. Digital Pins in Input Mode: When you set a digital pin as an input using pinMode(pin, INPUT), the pin can detect two states: HIGH (if the voltage is close to 5V) or LOW (if the voltage is close to 0V or ground).

4. Analog Pins in Input Mode: Analog pins are automatically set to input mode when using analogRead(). These pins can detect a range of voltages, not just two states like digital pins, because they are connected to an analog-to-digital converter (ADC).
*/

#include "Arduino.h"

// Our photoresistor will give us a reading of the current light level on this analog pin
const byte PHOTORESISTOR_INPUT_PIN = A0;    // we pick an analog pin (defined in Arduino.h)
const unsigned int MIN_DELAY = 100;    // 50 ms shortest blink delay
const unsigned int MAX_DELAY = 1000;   // 500 ms longest blink delay

void setup() {
  // We will blink our build in LED based on amount of light received from our photoresistor
  pinMode(LED_BUILTIN, OUTPUT);       // output since we will control the built in LED
  pinMode(PHOTORESISTOR_INPUT_PIN, INPUT);  // input value from analog pin connected to photoresistor
  Serial.begin(9600);  // This initializes the Serial Monitor and sets the speed to 9600 bits per second
}

void loop() {
  unsigned int light_value = analogRead(PHOTORESISTOR_INPUT_PIN);   // light value from 0 to 1024
  Serial.print("Light value: ");  // Display label string to serial monitor
  Serial.print(light_value);      // display the value read from our photoresistor

  static unsigned int darkest_light = light_value;    // this is the lowest value returned by the photoresistor
  static unsigned int brightest_light = light_value;  // this is the highest value returned by the photoresistor

  /*
   * Now that we have a light value let's update our darkest and brightest values
   * if the current value is darker (less than) our previous darkest or brighter
   * (greater than) our previous brightest value.
   */
  if (light_value < darkest_light) {  // If value is LESS THAN ('<') the darkest...
    darkest_light = light_value;      // ...then save current value as our new darkest value
  }
  if (light_value > brightest_light) {  // If value is GREATER THAN ('>') the brightest...
    brightest_light = light_value;      // ...then save current value as our new brightest value
  }

  /*
   * map our light_value (which goes from darkest_light to brightest_light) 
   * and return a value from MAX_DELAY *down* to MIN_DELAY.  Perfect!
   */
  unsigned int delay_value = map(light_value, darkest_light, brightest_light, MAX_DELAY, MIN_DELAY);
  Serial.print(", Delay value: ");  // display label after light_value
  Serial.println(delay_value);      // display delay_value returned by map() function with newline

  // now blink our built in LED using our delay_value.
  digitalWrite(LED_BUILTIN, HIGH);  // Turn on LED
  delay(delay_value);               // Leave on delay_value milliseconds
  digitalWrite(LED_BUILTIN, LOW);   // Turn off LED
  delay(delay_value);               // Leave off delay_value milliseconds
}