#ifndef RATIO_H
#define RATIO_H

#include <iostream>

class Ratio // this class is used alongside my Tokens map -> each ratio is associated with a word, the ratio describing the word's appearance in good:bad tweets
{           // Ratio objects are only used during Training
private:
    int num;            // used to store the number of times a word shows up in a "good" tweet
    int denom;          // used to store the number of times a word shows up in a "bad" tweet
    double calculation; // stores the quotient of good/bad -> used for calculating the word's "overall score"

public:
    Ratio();                 // default constructor -> initalizes everything to zero
    Ratio(int, int, double); // parameterized constructor -> sets private data members to the values of the arguments

    int getNum();     // returns value of current num (good count)
    int getDenom();   // returns value of current denom (bad count)
    double getCalc(); // returns value of current calculation

    void setCalc(double); // used in decision making processing -> sifting out unimportant words
    void setNum(int);     // sets the num to number of choice, used for incrementing
    void setDenom(int);   // sets the denom to number of choice, used for incrementing

    double calculate(); // returns the quotient of good/bad -> useful for deciding a word's "overall score"
    int numOccur();     // calculates how many occurrences the word makes in the tweet -> used to decide whether a word is important to the training process

    friend std::ostream &operator<<(std::ostream &, const Ratio &); // overides the << operator so the system automatically prints "num/denom"
};

#endif