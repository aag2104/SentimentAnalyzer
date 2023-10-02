#ifndef ANALYZER_H
#define ANALYZER_H

#include <iostream>
#include <map>
#include "Tweet.h"
class Analyzer
{
private:
    std::map<DSString, Tweet> Tweets;     // map that holds tweet objects and their important numbers (sentiment/id)
    std::map<DSString, Ratio> Tokens;     // map that holds words and their cooresponding good:bad ratios
    std::map<DSString, Tweet> TestTweets; // map that holds tweets and their cooresponding id numbers
    std::map<DSString, int> TweetSums;    // map that holds tweet id numbers and their their prediction (whether the tweet leans good of bad)
    std::map<DSString, char> Predictions; // map that holds tweet ids and predicted sentiments
    std::map<DSString, DSString> Answers; // map that holds tweet ids and true sentiments

public:
    // methods that deal with training data:
    void train(char *);                                // overarching method- runs training functions
    int openTrain(char *);                             // opens training file, parses through it and stores sentiment, id, and tweet -> calls convertToTweets
    int storeWords(std::vector<DSString>);             // iterates through vector of words and stores them in Tokens map with accurate ratios
    int decideSignificance(std::map<DSString, Ratio>); // decides whether to keep certain words in Tokens map, gets rid of words that will confuse program

    // methods that deal with testing data:
    int openTest(char *);     // opens testing file, parses through it and stores sentiment, id, and tweet -> calls convertToTweets
    int iterateThroughTest(); // iterates through test tweets and stores their data in TweetSums

    // methods that deal with both testing and traing data:
    char *clean(char *);                         // gets rid of special characters and unnecessary punctuation
    void tokenizeMap(std::map<DSString, Tweet>); // iterates through map of tweets and calls Tweet class's tokenize function -> calls store words

    void predict(char *, char *);             // overarching method- runs functions used to make predictions on testing data
    int outputPredictions(char *);            // outputs file with predictions
    void evaluatePredictions(char *, char *); // compares predictions with true dataset (answers) and calculates accuracy
    void outputAccuracy(char *);              // outputs accuracy file
    int openAnswers(char *);                  // opens answers file, parses, and stores
};

#endif