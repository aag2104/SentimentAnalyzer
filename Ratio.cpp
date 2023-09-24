#include "Ratio.h"

Ratio::Ratio()
{
    num = 0; 
    denom = 0;
}

Ratio::Ratio(int one, int two)
{
    num = one;
    denom = two;
}

double Ratio::calculateRatio()
{
    return num/denom;
}

int Ratio::getNum()
{
    return num;
}

int Ratio::getDenom()
{
    return denom;
}

void Ratio::setNum(int newNum)
{
    num = newNum;
}

void Ratio::setDenom(int newDenom)
{
    denom = newDenom;
}
