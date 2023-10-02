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
    DSString sentiment; // stores sentiment associated with tweet
    DSString message;   // stores the tweet's actual message

public:
    Tweet();                   // default constructor - intializes values as empty
    Tweet(DSString, DSString); // parameterized constructor - gives private values values of args

    std::vector<DSString> tokenize(); // splits tweets into words and stores them in a vector of words

    DSString getSentiment();                                        // returns current sentiment value
    DSString getMessage();                                          // returns current message value
    friend std::ostream &operator<<(std::ostream &, const Tweet &); // outputs message when << is used
};

#endif