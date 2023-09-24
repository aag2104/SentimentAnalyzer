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
    char* id;
    DSString message; 
    std::map<std::string, Ratio> Tokens;
    public:

    Tweet();
    Tweet(char, char*, DSString);
    int tokenizer(std::map<std::string, DSString> mp);
    
    char getSentiment();
    char* getId();
    DSString getMessage();

};

#endif