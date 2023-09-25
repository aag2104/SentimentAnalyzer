#ifndef ANALYZER_H
#define ANALYZER_H

#include <iostream>
#include <map>
#include "Tweet.h"
class Analyzer
{
    private:
    std::map<std::string, Tweet> Tweets;

    public:
    int train();
    int open_and_parse();
    int convert_and_store(std::string, std::string, char*);
    int clean(char*);
    int tokenize_map(std::map<std::string, Tweet>);
    //tokenizemap - iterates through Tweets map and calls tokenize on each tweet - returns a vector of words
    //store_words - called in tokenizemap, iterates through vector and stores words and ratios in Tokens map
    //predict
    //evaluate predictions
};

#endif