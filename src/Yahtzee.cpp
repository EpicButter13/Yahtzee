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
#define BUZZER_PIN D1
// BUTTON
#define YELLOW_PUSH_BUTTON_PIN D9
#define GREEN_PUSH_BUTTON_PIN D10


// Variables
diceSet* fiveDice = new diceSet();
int diceRoll1 = fiveDice->getDiceValue(1);
int diceRoll2 = fiveDice->getDiceValue(2);
int diceRoll3 = fiveDice->getDiceValue(3);
int diceRoll4 = fiveDice->getDiceValue(4);
int diceRoll5 = fiveDice->getDiceValue(5);
int rollsLeft = fiveDice->getRolls();
String score = "";
LiquidCrystal lcd(
  LCD_RS_PIN,
  LCD_E_PIN,
  LCD_D4_PIN,
  LCD_D5_PIN,
  LCD_D6_PIN,
  LCD_D7_PIN
);
unsigned long currentTime = millis();
unsigned long lastTimeButtonPressed = millis();
boolean currentState = FALSE;
boolean lastState;
boolean switchOneState = 0;
boolean switchTwoState = 0;
boolean switchThreeState = 0;
boolean switchFourState = 0;
boolean switchFiveState = 0;

// Functions
int* convertStringtoArray(String diceRolls) {
  int* array = new int[5];
  for (int i = 0; i < 5; i++) {
    String roll = diceRolls.substring(i, 1);
    array[i] = roll.toInt();
  }
  return array;
 
}

int updateSwitchState(String arguments) {

  boolean state;
  int index = (arguments.substring(0,1)).toInt();
  int switchState = (arguments.substring(2)).toInt();
  if (switchState == 1) {
    state = true;
  } else {
    state = false;
  }

  if (index == 0) {
    switchOneState = state;
  } else if (index == 1) {
    switchTwoState = state;
  }
  else if (index == 2) {
    switchThreeState = state;
  }
  else if (index == 3) {
    switchFourState = state;
  }
  else if (index == 4) {
    switchFiveState = state;
  } else {
    return -1;
  }

  return 0;
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
  score = "";
  score += String(fiveDice->basicHand(1)); 
  score += ",";
  score += String(fiveDice->basicHand(2)); 
  score += ",";
  score += String(fiveDice->basicHand(3)); 
  score += ",";
  score += String(fiveDice->basicHand(4)); 
  score += ",";
  score += String(fiveDice->basicHand(5)); 
  score += ",";
  score += String(fiveDice->basicHand(6)); 
  score += ",";
  score += String(fiveDice->threeOfAKind()); 
  score += ",";
  score += String(fiveDice->fourOfAKind()); 
  score += ",";
  score += String(fiveDice->fullHouse()); 
  score += ",";
  score += String(fiveDice->smallStraight()); 
  score += ",";
  score += String(fiveDice->largeStraight()); 
  score += ",";
  score += String(fiveDice->yahtzee()); 
  score += ",";
  score += String(fiveDice->handSum());
}

void ifButtonsPressed() {

  //boolean yellowButtonValue = digitalRead(YELLOW_PUSH_BUTTON_PIN);
  boolean greenButtonValue = digitalRead(GREEN_PUSH_BUTTON_PIN);

  currentTime = millis();
  lastState = currentState;
  currentState = digitalRead(YELLOW_PUSH_BUTTON_PIN);

  if ((lastState == FALSE && currentState == TRUE)) {
    Serial.println("PRESSED!!?!?!??!");
    lastTimeButtonPressed = millis();
    fiveDice->roll();
    rollsLeft = fiveDice->getRolls();
    diceRoll1 = fiveDice->getDiceValue(1);
    diceRoll2 = fiveDice->getDiceValue(2);
    diceRoll3 = fiveDice->getDiceValue(3);
    diceRoll4 = fiveDice->getDiceValue(4);
    diceRoll5 = fiveDice->getDiceValue(5);
    updateScore();
    tone(BUZZER_PIN, 1000, 1000);
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
  fiveDice->select(1, switchOneState);
  fiveDice->select(2, switchTwoState);
  fiveDice->select(3, switchThreeState);
  fiveDice->select(4, switchFourState);
  fiveDice->select(5, switchFiveState);
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

// setup() runs once, when the device is first turned on
void setup() {
  // Begin Instruments
  delay(1000);
  Serial.begin(9600);
  lcd.begin(16, 2);

  // Pin Modes
  pinMode(YELLOW_PUSH_BUTTON_PIN, INPUT_PULLDOWN);
  pinMode(GREEN_PUSH_BUTTON_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  // Cloud Variables + Functions
  //Particle.variable("RollsLeft", rollsLeft);
  Particle.variable("roll", score);
  Particle.variable("SwitchOneState", switchOneState);
  Particle.variable("SwitchTwoState", switchTwoState);
  Particle.variable("SwitchThreeState", switchThreeState);
  Particle.variable("SwitchFourState", switchFourState);
  Particle.variable("SwitchFiveState", switchFiveState);
  Particle.function("UpdateSwitchState", updateSwitchState);

  //seeding random number generation
  srand(millis());

}

// loop() runs over and over again, as quickly as it can execute.
void loop() {


  // Print LCD
  updateLCD();

  //delay(1000);
  Serial.print("Is Button Clicked: ");
  Serial.println(digitalRead(YELLOW_PUSH_BUTTON_PIN));
  Serial.print("Switch 1: ");
  Serial.println(switchOneState);
  Serial.print("Switch 2: ");
  Serial.println(switchTwoState);
  Serial.print("Switch 3: ");
  Serial.println(switchThreeState);
  Serial.print("Switch 4: ");
  Serial.println(switchFourState);
  Serial.print("Switch 5: ");
  Serial.println(switchFiveState);
  Serial.print("Score string: ");
  Serial.println(score);
  Serial.print("Get Select: ");
  for (int i = 0; i < 5; i++)
  {
    Serial.println(fiveDice->getSelect(i));
  }
  // Check the buttons
  ifButtonsPressed();
  Particle.syncTime();
  switchUpdate();

}
