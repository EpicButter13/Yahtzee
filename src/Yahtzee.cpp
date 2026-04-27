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
#include <LiquidCrystal.h>
#include <diceClass.cpp>
using namespace std;


// Pins
// LCD
#define LCD_RS_PIN S3
#define LCD_E_PIN S4
#define LCD_D4_PIN A0
#define LCD_D5_PIN A1
#define LCD_D6_PIN A2
#define LCD_D7_PIN A5
// BUZZER
#define BUZZER_PIN D7
// BUTTON
#define BLUE_PUSH_BUTTON_PIN D0
#define GREEN_PUSH_BUTTON_PIN D10
// SWITCH
#define SWITCH_ONE_PIN D1
#define SWITCH_TWO_PIN D2
#define SWITCH_THREE_PIN D3
#define SWITCH_FOUR_PIN D4
#define SWITCH_FIVE_PIN D5


// Variables
int diceRoll1 = 0;
int diceRoll2 = 0;
int diceRoll3 = 0;
int diceRoll4 = 0;
int diceRoll5 = 0;
int rollsLeft = 3;
int score;
LiquidCrystal lcd(
  LCD_RS_PIN,
  LCD_E_PIN,
  LCD_D4_PIN,
  LCD_D5_PIN,
  LCD_D6_PIN,
  LCD_D7_PIN
);

// Functions
// int convertStringRollsToInts(String diceRolls) {
//   return 0;
// };

int* convertStringtoArray(String diceRolls) {
  int* array = new int[5];
  for (int i = 0; i < 5; i++) {
    String roll = diceRolls.substring(i, 1);
    array[i] = roll.toInt();
  }
  return array;
}

void ifButtonsPressed() {

  boolean blueButtonValue = digitalRead(BLUE_PUSH_BUTTON_PIN);
  boolean greenButtonValue = digitalRead(GREEN_PUSH_BUTTON_PIN);

  if (blueButtonValue) {

  }

  if (greenButtonValue) {
    
  }

}

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

  //seeding random number generation
  srand(time(0));
}

// loop() runs over and over again, as quickly as it can execute.
void loop() {



  lcd.setCursor(0,0);
  lcd.println("Rolls: 1|2|3|4|5");
  lcd.setCursor(0, 1);
  lcd.println("Rolls Left: ");
  lcd.println(rollsLeft);



  ifButtonsPressed();

}
