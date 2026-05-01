# Yahtzee

# 1
Created by Shreyas Pradeep, Shriyan Dey, & Aadi Sharma

# 2
Description: Yahtzee is a dice game, where each player rolls a set of five dice and generates points based on specific types of dice combinations. These combinations are called hands, and there are 13 possible hands a player can play.  Instead of using physical dice, we want to roll digital dice when a button is pressed. The values of the dice are continually updated after each roll on a liquid crystal display. The display also shows the number of rolls the player has left in their turn. If the player would like to only roll some as opposed to all of the dice, they can click the corresponding toggle buttons on the accompanying website. The website also displays the calculated score the player would get for playing each of the 13 possible hands. Once the player has decided to end their turn, they click the second button to reset the dice and roll count for the next player/turn.

Sensors:
Yellow Button: Rolls the dice.
Green Button: Resets the turn.
Potentiometer: Coupled with the liquid crystal display; adjusts the brightness of the LCD.

Actuators: 
Speaker: Plays a sound effect when the yellow button is pressed, to emulate the audio feedback of rolling dice.
Liquid Crystal Display: Displays the number value of each of the five dice as well as the number of rolls left.

Cloud Connectivity: 
HTML and javascript files were used to generate a rudimentary webpage.

six cloud variables were used. One variable was a string composed of the concatenation of 13 different integer values. These integers are the calculated potential score corresponding to each hand type. The website receives this string, extracts those 13 values, and displays them in a table. The other five cloud variables correspond to the five buttons on the website. These booleans are switched when their corresponding button is clicked. These values are sent to the photon via a cloud function such that when the physical roll button is pressed, only the un-selected dice are rolled (have their value randomly generated again).

# 3
Yahtzee.cpp - Contains setup and loop function for the photon with all logic related to circuit 
diceClass.cpp - Contains dice and diceset classes that handle rolling and scoring functionality
displayGameData.html - Webpage that displays Yahtzee scores and dice that are locked in
displayStyle.css - CSS file that customizes displayGameData.html file
webPageScript.js - Javascript file that uses particle functions to add functionality to buttons and scores on displayGameData.html file

# 4 REMINDER TO LOOK AT COMPONENTS AND ADD THEIR PART NUMBERS!!!!!!
(1) Particle Photon 2
(1) Passive Buzzer
(1) LCD1602 Module
(2) Push Buttons

# 5
[Wiring_Diagram](Wiring_Diagram.png)
*Press the click while holding command