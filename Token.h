#ifndef TOKEN_H
#define TOKEN_H

#include <iostream>
#include "DSString.h"

class Token
{
    private:
        DSString word;
        int numGood;
        int numBad;
    ;
    public:
    Token();
    Token(DSString, int, int);
    

};

#endif