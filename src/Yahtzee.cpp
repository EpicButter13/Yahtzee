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

// Dice class
class Dice {



};

// setup() runs once, when the device is first turned on
void setup() {
  // Begin Instruments
  delay(1000);
  Serial.begin(9600);
  lcd.begin(16, 2);

  // Pin Modes
  pinMode(BLUE_PUSH_BUTTON_PIN, INPUT);
  pinMode(GREEN_PUSH_BUTTON_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(SWITCH_ONE_PIN, INPUT);
  pinMode(SWITCH_TWO_PIN, INPUT);
  pinMode(SWITCH_THREE_PIN, INPUT);
  pinMode(SWITCH_FOUR_PIN, INPUT);
  pinMode(SWITCH_FIVE_PIN, INPUT);

  // Cloud Variables + Functions
  Particle.variable("DiceRoll1", diceRoll1);
  Particle.variable("DiceRoll2", diceRoll2);
  Particle.variable("DiceRoll3", diceRoll3);
  Particle.variable("DiceRoll4", diceRoll4);
  Particle.variable("DiceRoll5", diceRoll5);
  Particle.variable("RollsLeft", rollsLeft);
  Particle.variable("Score", score);

}

// loop() runs over and over again, as quickly as it can execute.
void loop() {



  lcd.setCursor(0,0);
  lcd.println("Rolls: 1 2 3 4 5");
  lcd.setCursor(0, 1);
  lcd.println("Rolls Left: ");
  lcd.println(rollsLeft);



  ifButtonsPressed();

}
