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
using namespace std;

// Pins
// LCD
#define LCD_RS_PIN D8
#define LCD_E_PIN D9
#define LCD_D4_PIN A0
#define LCD_D5_PIN A1
#define LCD_D6_PIN A2
#define LCD_D7_PIN A5
// BUZZER
#define BUZZER_PIN D7
// BUTTON
#define PUSH_BUTTON_PIN D0
// SWITCH
#define SWITCH_ONE_PIN D1
#define SWITCH_TWO_PIN D2
#define SWITCH_THREE_PIN D3
#define SWITCH_FOUR_PIN D4
#define SWITCH_FIVE_PIN D5


// Variables
string diceRolls;
LiquidCrystal lcd(
  LCD_RS_PIN,
  LCD_E_PIN,
  LCD_D4_PIN,
  LCD_D5_PIN,
  LCD_D6_PIN,
  LCD_D7_PIN
);

// Functions
void convertRollsToInts(string diceRolls);

// setup() runs once, when the device is first turned on
void setup() {
  // Begin Instruments
  Serial.begin(9600);
  lcd.begin(16, 2);

  // Pin Modes
  pinMode(PUSH_BUTTON_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(SWITCH_ONE_PIN, INPUT);
  pinMode(SWITCH_TWO_PIN, INPUT);
  pinMode(SWITCH_THREE_PIN, INPUT);
  pinMode(SWITCH_FOUR_PIN, INPUT);
  pinMode(SWITCH_FIVE_PIN, INPUT);

  // Cloud Variables + Functions
  //Particle.variable("DiceRolls", diceRolls);
  //Particle.function("ConvertRollsToInts", convertRollsToInts);

}

// loop() runs over and over again, as quickly as it can execute.
void loop() {
  
  Serial.println("Test");

}
