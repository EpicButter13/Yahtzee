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
#include <cstdlib>
#include <ctime>
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
diceSet* fiveDice = new diceSet();
int diceRoll1 = fiveDice->getDiceValue(1);
int diceRoll2 = fiveDice->getDiceValue(2);
int diceRoll3 = fiveDice->getDiceValue(3);
int diceRoll4 = fiveDice->getDiceValue(4);
int diceRoll5 = fiveDice->getDiceValue(5);
int rollsLeft = fiveDice->getRolls();
String scoreData;
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
/* From the web page javascript code; to see order in which scores are interpreted by the webpage
must packaged score data accordingly
const ids = [
        "ones_score",
        "twos_score",
        "threes_score",
        "fours_score",
        "fives_score",
        "sixes_score",
        "three_kind_score",
        "four_kind_score",
        "full_house_score",
        "small_straight_score",
        "large_straight_score",
        "yahtzee_score",
        "chance_score"
    ];
*/
void updateScore() {
  score += fiveDice->basicHand(1) + ",";
  score += fiveDice->basicHand(2) + ",";
  score += fiveDice->basicHand(3) + ",";
  score += fiveDice->basicHand(4) + ",";
  score += fiveDice->basicHand(5) + ",";
  score += fiveDice->basicHand(6) + ",";
  score += fiveDice->threeOfAKind() + ",";
  score += fiveDice->fourOfAKind() + ",";
  score += fiveDice->smallStraight() + ",";
  score += fiveDice->largeStraight() + ",";
  score += fiveDice->yahtzee() + ",";
  score += fiveDice->handSum() + ",";
}

void ifButtonsPressed() {

  boolean blueButtonValue = digitalRead(BLUE_PUSH_BUTTON_PIN);
  boolean greenButtonValue = digitalRead(GREEN_PUSH_BUTTON_PIN);

  if (blueButtonValue) {
    fiveDice->roll();
    rollsLeft = fiveDice->getRolls();
    diceRoll1 = fiveDice->getDiceValue(1);
    diceRoll2 = fiveDice->getDiceValue(2);
    diceRoll3 = fiveDice->getDiceValue(3);
    diceRoll4 = fiveDice->getDiceValue(4);
    diceRoll5 = fiveDice->getDiceValue(5);
    updateScore();
    delay(250);
  }

  if (greenButtonValue) {
    delete fiveDice;
    fiveDice = new diceSet;
    rollsLeft = fiveDice->getRolls();
    diceRoll1 = fiveDice->getDiceValue(1);
    diceRoll2 = fiveDice->getDiceValue(2);
    diceRoll3 = fiveDice->getDiceValue(3);
    diceRoll4 = fiveDice->getDiceValue(4);
    diceRoll5 = fiveDice->getDiceValue(5);
    updateScore();
  }

}

void switchUpdate() {
  fiveDice->select(1, digitalRead(SWITCH_ONE_PIN));
  fiveDice->select(2, digitalRead(SWITCH_TWO_PIN));
  fiveDice->select(3, digitalRead(SWITCH_THREE_PIN));
  fiveDice->select(4, digitalRead(SWITCH_FOUR_PIN));
  fiveDice->select(5, digitalRead(SWITCH_FIVE_PIN));
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
  pinMode(SWITCH_ONE_PIN, INPUT_PULLUP);
  pinMode(SWITCH_TWO_PIN, INPUT_PULLUP);
  pinMode(SWITCH_THREE_PIN, INPUT_PULLUP);
  pinMode(SWITCH_FOUR_PIN, INPUT_PULLUP);
  pinMode(SWITCH_FIVE_PIN, INPUT_PULLUP);

  // Cloud Variables + Functions
  Particle.variable("RollsLeft", rollsLeft);
  Particle.variable("RollData", scoreData);

  //seeding random number generation
  srand(millis());

}

void updateLCD() {
  // Print LCD
  lcd.setCursor(0,0);
  lcd.print("Dice: ");
  lcd.print(diceRoll1);
  lcd.print("|");
  lcd.print(diceRoll2);
  lcd.print("|");
  lcd.print(diceRoll3);
  lcd.print("|");
  lcd.print(diceRoll4);
  lcd.print("|");
  lcd.print(diceRoll5);
  lcd.print("|");
  lcd.setCursor(0, 1);
  lcd.print("Rolls Left: ");
  lcd.print(rollsLeft);
}

// loop() runs over and over again, as quickly as it can execute.
void loop() {


  // Print LCD
  updateLCD();

  Serial.print("Is Button Clicked: ");
  Serial.println(digitalRead(BLUE_PUSH_BUTTON_PIN));
  Serial.print("Switch 1: ");
  Serial.println(digitalRead(SWITCH_ONE_PIN));
  Serial.print("Switch 2: ");
  Serial.println(digitalRead(SWITCH_TWO_PIN));
  Serial.print("Switch 3: ");
  Serial.println(digitalRead(SWITCH_THREE_PIN));
  Serial.print("Switch 4: ");
  Serial.println(digitalRead(SWITCH_FOUR_PIN));
  Serial.print("Switch 5: ");
  Serial.println(digitalRead(SWITCH_FIVE_PIN));


  // Check the buttons
  ifButtonsPressed();
  switchUpdate();

}
