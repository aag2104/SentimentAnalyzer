#ifndef ANALYZER_H
#define ANALYZER_H

#include <iostream>
#include <map>
#include "Tweet.h"
class Analyzer
{
private:
    std::map<DSString, Tweet> Tweets; // map that holds tweet objects and their important numbers (sentiment/id)
    std::map<DSString, Ratio> Tokens; // map that holds words and their coorsponding good:bad ratios
    std::map<DSString, Tweet> TestTweets;
    std::map<DSString, int> TweetSums;


public:
    // methods that deal with training data:
    void train();                                       // overarching method- runs training functions
    int openTrain();                                   // opens training file, parses through it and stores sentiment, id, and tweet -> calls convertToTweets
    int storeWords(std::vector<DSString>);             // iterates through vector of words and stores them in Tokens map with accurate ratios
    int decideSignificance(std::map<DSString, Ratio>); // decides whether to keep certain words in Tokens map, gets rid of words that will confuse program

    int openTest(); // opens testing file, parses through it and stores sentiment, id, and tweet -> calls convertToTweets
    int iterateThroughTest();
    int outputPredictions();

    void outputAccuracy();

    char* clean(char*);                          // gets rid of special characters and unnecessary punctuation
    int tokenizeMap(std::map<DSString, Tweet>); // iterates through map of tweets and calls Tweet class's tokenize function -> calls store words

    void predict();             // overarching method- runs functions used to make predictions on testing data
    void evaluatePredictions(); // compares predictions with true dataset (answers) and calculates accuracy
};

#endif