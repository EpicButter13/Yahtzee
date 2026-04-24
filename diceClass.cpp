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

        cout << "Yahtzee: " << this->yahtzee() << endl;
        
    }

    void select(int index)
    {
        if (0 < index && index < NUM_DICE)
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
                if (!(this->countNum(i) >= 2))
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
    }
/*
    int smallStraight()
    {
        int* sortedHand = this->sort();

        for (int i = 0; i < NUM_DICE; i++)
        {

        }
    }

    int largeStraight()
    {

    }
*/
    private:
    dice* die;
    int hand[NUM_DICE] = {};
    bool selected[NUM_DICE] = {};
    int rolls;
};

int main()
{
    
    srand(time(0));
    diceSet fiveDice;
    fiveDice.print();
    char input = 'y';
    while (input == 'y')
    {
        fiveDice.roll();
        fiveDice.print();
        cout << "roll again? (y/n) or select dice (#) ";
        cin >> input;
        int val = input - '0';
        while (0 < val && val <= NUM_DICE)
        {
            fiveDice.select(val - 1);
            fiveDice.print();
            cout << "roll again? (y/n) or select dice (#) ";
            cin >> input;
            val = input - '0';
        }
    }
    return 0;
}
