/* 
 * Project myProject
 * Author: Your Name
 * Date: 
 * For comprehensive documentation and examples, please visit:
 * https://docs.particle.io/firmware/best-practices/firmware-template/
 */

// Include Particle Device OS APIs
#include "Particle.h"

// Let Device OS manage the connection to the Particle Cloud
SYSTEM_MODE(AUTOMATIC);

// Run the application and system concurrently in separate threads
SYSTEM_THREAD(ENABLED);

// Show system, cloud connectivity, and application logs over USB
// View logs with CLI using 'particle serial monitor --follow'
SerialLogHandler logHandler(LOG_LEVEL_INFO);

// Libraries
#include <iostream>
using namespace std;

// Variables
string diceRolls;

// Functions
void convertRollsToInts(string diceRolls);

// setup() runs once, when the device is first turned on
void setup() {
  Serial.begin(9600);
  //Particle.variable("DiceRolls", diceRolls);
  //Particle.function("ConvertRollsToInts", convertRollsToInts);

}

// loop() runs over and over again, as quickly as it can execute.
void loop() {
  
  Serial.println("Test");

}
