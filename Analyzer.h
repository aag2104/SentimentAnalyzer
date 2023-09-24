#ifndef ANALYZER_H
#define ANALYZER_H

#include <iostream>
#include <map>
#include "Tweet.h"
class Analyzer
{
    private:
    std::map<std::string, DSString> Tweets;
    public:
    int train();
    int open_and_parse();
    int convert_and_store(int, std::string, char*);
    int clean(char*);
    // test
};

#endif