//#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

//Yahtzee is always played with five dice
const int NUM_DICE = 5;

//Code modeled based on previous homework assignments; utilizes random number generation to simulate dice
class dice
{
    public:
    dice() //default constructor
    {
        minRoll = 1;
        maxRoll = 6;
    }

    /* unused constructor, since only default dice are used
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

//diceSet holds dice roll values, the number of rolls left, and functions calculate potential hand scores
class diceSet
{
    public:
    diceSet() //default constructor - each turn of the game gets 3 rolls
    {
        rolls = 3;
    }
    
    void roll() //generates and stores 5 random numbers (1-6 inclusive in this case)
    {
        if (rolls > 0)
        {
            for (int i = 0; i < NUM_DICE; i++)
            {
                if (!selected[i])
                {
                    hand[i] = die.roll();
                }
            }
        rolls--;
        }
    }

    int getRolls()
    {
        return rolls;
    }

    int getDiceValue(int dieNum)
    {
        if (1 <= dieNum && dieNum <= NUM_DICE)
        {
            return hand[dieNum - 1];
        }
        else
        {
            return 0;
        }
    }
 /* for testing purposes - most of this information is instead presented on a webpage
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
    void select(int dieNum) //selecting a dice in Yahtzee means locking its value and not rolling it
    {
        if (1 <= dieNum && dieNum <= NUM_DICE)
        {
            selected[dieNum] = !selected[dieNum];
        }
    }

    void select(int dieNum, bool status)
    {
        if (1 <= dieNum && dieNum <= NUM_DICE)
        {
            selected[dieNum - 1] = status;
        }
    }

    int getSelect(int index)
    {
       return selected[index];
    }

    int handSum() //sum of all 5 dice values
    {
        int sum = 0;
        for (int i = 0; i < NUM_DICE; i++)
        {
            sum += hand[i];
        }
        return sum;
    }

    int countNum (int num) //used in score calculations
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

    int basicHand(int num) //a basic hand is something like a score of 3 for having three different dice with the value 1
    {
        return num * this->countNum(num);
    }

    int maxCount() //used in score calculations (i.e to check if three of the same value is present in the hand)
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

    int yahtzee() //same as five of a kind
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

    int fullHouse() //a hand that contains 3 of a kind and 2 of a kind
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

    //some hands require checking consecutive runs of dice values. The following functions sort the dice values and count these runs (straights).

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
    dice die;
    int hand[NUM_DICE] = {};
    bool selected[NUM_DICE] = {};
    int rolls;
};
// this main function was used for testing before the wepbage was setup
// int main()
// {
//     int totalScore = 0; //variable to keep track of player score for their three rolls

//     srand(time(0));
//     diceSet fiveDice;
//     fiveDice.print();
//     char input = 'y';
//     while (true)
//     {
//         cout << "roll? (y/n) or select dice (#) ";
//         cin >> input;
//         int val = input - '0';
//         while (0 < val && val <= NUM_DICE)
//         {
//             fiveDice.select(val - 1);
//             fiveDice.print();
//             cout << "roll? (y/n) or select dice (#) ";
//             cin >> input;
//             val = input - '0';
//         }
//         if (input == 'y')
//         {
//             fiveDice.roll();
//             fiveDice.print();
//         }
//         else
//         {
//             break;
//         }      
//     }
//     return 0;
// }
