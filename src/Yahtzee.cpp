/* 
 * Project myProject
 * Author: Your Name
 * Date: 
 * For comprehensive documentation and examples, please visit:
 * https://docs.particle.io/firmware/best-practices/firmware-template/
 */

// Blynk
#define BLYNK_TEMPLATE_ID "TMPL2hejoPvA3"
#define BLYNK_TEMPLATE_NAME "Photon"
#define BLYNK_AUTH_TOKEN "N6f-kXaUZWYlsEYQtC_AsFFka62kWxX0"

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
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

const int NUM_DICE = 5;

class dice
{
    public:
    dice() //default constructor
    {
        minRoll = 1;
        maxRoll = 6;
    }

    /*
    dice(int minValue, int maxValue)
    {
        minRoll = minValue;
        maxRoll = maxValue;
    }
    */

    int roll()
    {
    int range = maxRoll - minRoll + 1;
    return (rand() % range) + minRoll;
    }

    private:
    int minRoll;
    int maxRoll;
};

class diceSet
{
    public:
    diceSet()
    {
        die = new dice;
        rolls = 3;
    }
    
    void roll()
    {
        for (int i = 0; i < NUM_DICE; i++)
        {
            if (!selected[i])
            {
                hand[i] = die->roll();
            }
        }
        rolls--;
    }

    int getRolls()
    {
        return rolls;
    }
    
    /*
    void print()
    {
        cout << "Rolls left: " << rolls << endl;
        for (int i = 0; i < NUM_DICE; i++)
        {
            cout << hand[i] << " selected: " << selected[i] << endl;
        }
        cout << endl;
        cout << "Potential hand scores: " << endl;
        cout << "ones: " << this->basicHand(1) << endl;
        cout << "twos: " << this->basicHand(2) << endl;
        cout << "threes: " << this->basicHand(3) << endl;
        cout << "fours: " << this->basicHand(4) << endl;
        cout << "fives: " << this->basicHand(5) << endl;
        cout << "sixes: " << this->basicHand(6) << endl;
        cout << "chance: " << this->handSum() << endl;
        cout << "three of a kind : " << this->threeOfAKind() << endl;
        cout << "four of a kind : " << this->fourOfAKind() << endl;
        cout << "full house: " << this->fullHouse() << endl;
        cout << "small straight: " << this->smallStraight() << endl;
        cout << "large straight: " << this->largeStraight() << endl;
        cout << "Yahtzee: " << this->yahtzee() << endl;
        cout << endl;
        
    }
    */

    void select(int index)
    {
        if (0 <= index && index < NUM_DICE)
        {
            selected[index] = !selected[index];
        }
    }

    int handSum()
    {
        int sum = 0;
        for (int i = 0; i < NUM_DICE; i++)
        {
            sum += hand[i];
        }
        return sum;
    }

    int countNum (int num)
    {
        int count = 0;
        for (int i = 0; i < NUM_DICE; i++)
        {
            if (hand[i] == num)
            {
                count++;
            }
        }
        return count;
    }

    int basicHand(int num)
    {
        return num * this->countNum(num);
    }

    int maxCount()
    {
        int count;
        int mCount = this->countNum(1);
        for (int i = 2; i <= 6; i++)
        {
            count = this->countNum(i);
            if (count >= mCount)
            {
                mCount = count;
            }
        }
        return mCount;
    }

    int threeOfAKind()
    {
        int count = this->maxCount();
        if (count >= 3)
        {
            return this->handSum();
        }
        else{
            return 0;
        }
    }

    int fourOfAKind()
    {
        int count = this->maxCount();
        if (count >= 4)
        {
            return this->handSum();
        }
        else{
            return 0;
        }
    }

    int yahtzee()
    {
        int count = this->maxCount();
        if (count == 5)
        {
            return 50;
        }
        else{
            return 0;
        }
    }

    int fullHouse()
    {
        if (this->maxCount() == 3)
        {
            for (int i = 0; i < NUM_DICE; i++)
            {
                if (!(this->countNum(hand[i]) >= 2))
                {
                    return 0;
                }
            }
            return 25;
        }
        return 0;
    }

    int* sort()
    {
        int* sortedHand = new int[NUM_DICE];
        for (int i = 0; i < NUM_DICE; i++)
        {
            sortedHand[i] = hand[i];
        }

        for (int i = 0; i < NUM_DICE - 1; i++)
        {
            for (int j = i + 1; j < NUM_DICE; j++)
            {
                if (sortedHand[j] < sortedHand[i])
                {
                    int temp = sortedHand[j];
                    sortedHand[j] = sortedHand[i];
                    sortedHand[i] = temp;
                }
            }
        }
        return sortedHand;
    }

    int countConsec(int* sortedHand, int index)
    {
        int consecCount = 0;
        for (int i = index; i < NUM_DICE - 1; i++)
        {
            int j = i + 1;
            if (sortedHand[j] == sortedHand[i] + 1)
            {
                consecCount++;
            }
            else{
                break;
            }
        }
        return consecCount;
    }

    int maxConsec(int* sortedHand)
    {
        int mConsec = 0;
        for (int i = 0; i < NUM_DICE; i++)
        {
            int consecCount = countConsec(sortedHand, i);
            if (consecCount > mConsec)
            {
                mConsec = consecCount;
            }
        }
        return mConsec;
    }

    int smallStraight()
    {
        int* sortedHand = this->sort();
        if (maxConsec(sortedHand) >= 3) {
            delete[] sortedHand;
            return 30;
        }
        else{
            delete[] sortedHand;
            return 0;
        }
    }

    int largeStraight()
    {
        int* sortedHand = this->sort();
        if (maxConsec(sortedHand) >= 4) {
            delete[] sortedHand;
            return 40;
        }
        else{
            delete[] sortedHand;
            return 0;
        }
    }

    private:
    dice* die;
    int hand[NUM_DICE] = {};
    bool selected[NUM_DICE] = {};
    int rolls;
};


//declaring pins for the DIP switch (5 of them)
#define S1 = D1;
#define S2 = D2;
#define S3 = D3;
#define S4 = D4;
#define S5 = D5;


// setup() runs once, when the device is first turned on
void setup() {
  // Put initialization like pinMode and begin functions here
}

// loop() runs over and over again, as quickly as it can execute.
void loop() {
  // The core of your code will likely live here.

  // Example: Publish event to cloud every 10 seconds. Uncomment the next 3 lines to try it!
  // Log.info("Sending Hello World to the cloud!");
  // Particle.publish("Hello world!");
  // delay( 10 * 1000 ); // milliseconds and blocking - see docs for more info!
}
//wassup
