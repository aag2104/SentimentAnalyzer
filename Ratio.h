#ifndef RATIO_H
#define RATIO_H

#include <iostream>

class Ratio
{
    private:
        int num;
        int denom;
    public:
        Ratio();
        Ratio(int, int);
        double calculateRatio();
        int getNum();
        int getDenom();
        void setNum(int);
        void setDenom(int);

        
};

#endif