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
    }

    void select(int index)
    {
        if (0 < index && index < NUM_DICE)
        {
            selected[index] = !selected[index];
        }
    }

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
