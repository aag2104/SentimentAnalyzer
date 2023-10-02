#include "Ratio.h"

Ratio::Ratio() // sets num, denom, and calculation to zero
{
    num = 0;
    denom = 0;
    calculation = 0;
}

Ratio::Ratio(int one, int two, double three) // sets num, denom, and calculation to arg values
{
    num = one;
    denom = two;
    calculation = three;
}

double Ratio::calculate()
{
    if (denom == 0)
    { // cannot divide by zero -> so, if denom == zero, return 0 as calculation
        return 0;
    }
    calculation = num / denom; // divide to get calculation
    return calculation;        // return value
}

int Ratio::getNum() // returns num
{
    return num;
}

int Ratio::getDenom() // returns denom
{
    return denom;
}

double Ratio::getCalc() // returns calculation value
{
    return calculation;
}

void Ratio::setNum(int newNum) // allows access to private vars -> changes value of num
{
    num = newNum;
}

void Ratio::setDenom(int newDenom) // allows access to private vars -> changes value of denom
{
    denom = newDenom;
}

void Ratio::setCalc(double newCalc) // allows access to private vars -> changes value of calc
{
    calculation = newCalc;
}

int Ratio::numOccur() // counts number of occurrences
{
    return num + denom; // returns result of addition
}

std::ostream &operator<<(std::ostream &output, const Ratio &rat)
{
    output << rat.num << "/" << rat.denom; //<- prints with << operator is used before Ratio object
    return output;
}
