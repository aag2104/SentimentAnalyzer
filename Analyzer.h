#ifndef ANALYZER_H
#define ANALYZER_H

#include <iostream>
#include <map>
#include "Tweet.h"
class Analyzer
{
    private:
    std::map<std::string, Tweet> Tweets;
    std::map<std::string, Ratio> Tokens;

    public:
    int train();
    int open_and_parse();
    int convert_and_store(char, std::string, char*);
    int clean(char*);
    int tokenize_map(std::map<std::string, Tweet>);
    int store_words(std::vector<std::string>);
    int decide_significance(std::map<std::string, Ratio>);
    //predict
    //evaluate predictions
};

#endif