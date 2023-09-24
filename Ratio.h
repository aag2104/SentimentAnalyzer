#ifndef RATIO_H
#define RATIO_H

#include <iostream>

class Ratio
{
    private:
        int num;
        int denom;
        double calculation;
    public:
        Ratio();
        Ratio(int, int, double);
        double calculate();
        int getNum();
        int getDenom();
        double getCalc();
        void setCalc(double);
        void setNum(int);
        void setDenom(int);
        friend std::ostream &operator<<(std::ostream &, const Ratio &);
        

        
};

#endif