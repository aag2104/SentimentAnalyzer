#ifndef TWEET_H
#define TWEET_H

#include <iostream>
#include <map>
#include <vector>
#include "DSString.h"
#include "Ratio.h"

class Tweet
{
    private:
        std::string sentiment;
        DSString message; 
    
    public:
        Tweet();
        Tweet(DSString, char);
        std::vector<std::string> tokenize();
        std::string getSentiment();
        DSString getMessage();
        friend std::ostream &operator<<(std::ostream &, const Tweet &);
};

#endif