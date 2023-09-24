#ifndef TWEET_H
#define TWEET_H

#include <iostream>
#include <map>
#include "DSString.h"
#include "Ratio.h"

class Tweet
{
    private:
        char sentiment;
        DSString message; 
        std::map<std::string, Ratio> Tokens;
    
    public:
        Tweet();
        Tweet(DSString, char);
        int tokenize();
        char getSentiment();
        DSString getMessage();
        friend std::ostream &operator<<(std::ostream &, const Tweet &);
};

#endif