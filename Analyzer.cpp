// where we train and test data
#include <cstring>
#include <iostream>
#include <fstream>
#include <cstdio>

#include "Analyzer.h"

char* Analyzer::clean(char* tweet)
{
    int index = 0;
    char currChar = ' ';
    do
    {
        currChar = tweet[index];
        if (tweet[index] < 0 || tweet[index] > 128)
        {
            tweet[index] = ' '; 
        }

        if ((tweet[index] >= 34 && tweet[index] <= 38) || (tweet[index] >= 40 && tweet[index] <= 47))
        {
            tweet[index] = ' ';
        }

        if ((tweet[index] >= 58 && tweet[index] <= 62) || tweet[index] == 64)
        {
            tweet[index] = ' ';
        }

        if ((tweet[index] >= 91 && tweet[index] <= 96) || (tweet[index] >= 123 && tweet[index] <= 126))
        {
            tweet[index] = ' ';
        }

        if (tweet[index] == '\n')
        {
            tweet[index] = ' ';
        }

        if ((tweet[index] >= 0 && tweet[index] <= 31) || tweet[index] == 127)
        {
            tweet[index] = ' ';
        }

        index++;
    } while (currChar != '\0');
    return tweet;
}

int Analyzer::tokenizeMap(std::map<DSString, Tweet> messages) // returns vector of words w/ tweet sentiment in index[0]
{
    std::map<DSString, Tweet>::iterator it = messages.begin();

    for (it = messages.begin(); it != messages.end(); ++it)
    {
        //std::cout << it->second << std::endl;
        //storeWords(it->second.tokenize()); // returns vector of strings with sentiment of tweet in index[0]
    }

    return 0;
}

// tweet is a vector of words (DSString)
int Analyzer::storeWords(std::vector<DSString> tweet) // iterates through vector and stores words with ratio values/edits current ratio values
{
    DSString sentiment = tweet[0];


    for (size_t i = 1; i < tweet.size(); i++)
    {
        if (Tokens.find(tweet[i]) == Tokens.end())
        { // not found in Tokens map
            if (sentiment == "4")
            {                          // positive
                Ratio rat = {1, 0, 0}; // num = positive
                Tokens.insert({tweet[i], rat});
            }
            else
            {                          // negative
                Ratio rat = {0, 1, 0}; // denom = negative
                Tokens.insert({tweet[i], rat});
            }
        }
        else
        { // in Tokens map already
            if (sentiment == "4")
            { // positive
                int newNum = Tokens[tweet[i]].getNum() + 1;
                Tokens[tweet[i]].setNum(newNum);
            }
            else
            { // negative
                int newDenom = Tokens[tweet[i]].getDenom() + 1;
                Tokens[tweet[i]].setDenom(newDenom);
            }
        }
    }

    return 0;
}

int Analyzer::decideSignificance(std::map<DSString, Ratio>)
{
    std::map<DSString, Ratio>::iterator it = Tokens.begin();

    for (it = Tokens.begin(); it != Tokens.end(); ++it)
    { 
        if(it->second.calculate() < 0){
            it->second.setCalc(-1);
        } else {
            it->second.setCalc(1);
        }
    }

    return 0;
}

int Analyzer::openTrain() //char* trainingData
{
    char filename[] = "/users7/cse/ageer/DataStrc/assignment-2-don-t-be-sentimental-aag2104/assignment-2-don-t-be-sentimental-aag2104-1/data/train_dataset_20k.csv";
    FILE *stream;

    // set up the buffer
    char line[10000]; // maximum line length

    stream = fopen(filename, "r"); //trainingData
    if (stream == NULL)
    {
        std::cerr << "Opening the file failed!" << std::endl;
        return (-1);
    }

    fgets(line, sizeof(line), stream);

    while (fgets(line, sizeof(line), stream) != NULL)
    {
        char* sentiment = new char[2];
        char* id = new char[11];

        char tweet[200] = {0};

        sentiment[0] = line[0];
        sentiment[1] = '\0';

        for (int i = 2; i < 12; i++)
        {
            id[i - 2] = line[i];
        }
        id[10] = '\0';

        int commaCounter = 0;
        int line_index = 0;
        int tweet_index = 0;

        while (line_index < (int)sizeof(line))
        {
            if (commaCounter == 5)
            {
                do
                {
                    tweet[tweet_index] = line[line_index];
                    tweet_index++;
                    line_index++;
                } while (line[line_index] != '\n');
                break;
            }

            if (line[line_index] == ',')
            {
                commaCounter++;
            }

            line_index++;
        }

        char* cleanTweet = clean(tweet);
        DSString message = cleanTweet;
        DSString idNum(id);
        delete[] id;
        DSString sent(sentiment);
        delete[] sentiment;
        message = message.toLower();
        Tweet txt(message, sent); 
        
        Tweets.insert({idNum, txt});
    
    }

    fclose(stream);
    return 0;
}

int Analyzer::openTest()
{
    char filename[] = "/users7/cse/ageer/DataStrc/assignment-2-don-t-be-sentimental-aag2104/assignment-2-don-t-be-sentimental-aag2104/data/test_dataset_10k.csv";
    FILE *stream;

    // set up the buffer
    char line[1000]; // maximum line length

    stream = fopen(filename, "r");
    if (stream == NULL)
    {
        std::cerr << "Opening the file failed!" << std::endl;
        return (-1);
    }

    fgets(line, sizeof(line), stream);

    while (fgets(line, sizeof(line), stream) != NULL)
    {
        char id[11] = {0};
        char tweet[200] = {0};
        char sentiment[2] = {0};
        sentiment[0] = '3';

        for (int i = 0; i < 10; i++)
        {
            id[i] = line[i];
        }

        int commaCounter = 0;
        int line_index = 0;
        int tweet_index = 0;

        while (line_index < (int)sizeof(line))
        {
            if (commaCounter == 4)
            {
                do
                {
                    tweet[tweet_index] = line[line_index];
                    tweet_index++;
                    line_index++;
                } while (line[line_index] != '\n');
                break;
            }

            if (line[line_index] == ',')
            {
                commaCounter++;
            }

            line_index++;
        }

        char* cleanTweet = clean(tweet);
        DSString message = cleanTweet;
        DSString idNum = id;
        DSString sent = sentiment;
        message = message.toLower();
        Tweet txt(message, sent); 
    
        TestTweets.insert({id, txt});
    }

    fclose(stream);
    return 0;
}

int Analyzer::iterateThroughTest(){
    std::map<DSString,Tweet>::iterator ij = TestTweets.begin();

    for (ij=TestTweets.begin(); ij!=TestTweets.end(); ++ij){
          std::vector<DSString> words = ij->second.tokenize(); //words in tweetline
          int tweetSum = 0;
          for(size_t i = 0; i < words.size(); i++){
            if(Tokens.find(words[i]) != Tokens.end()){ //if vector word is in map...
                auto it = Tokens.find(words[i]);
                tweetSum += it->second.calculate();
            }
          }
        std::cout << tweetSum << std::endl;
        DSString id = ij->first;
        TweetSums.insert({id, tweetSum}); 
    }


    //tokenize ->
    //vector of words
    //iterate through vector -> search each element in Tokens map
    //if in Tokens map, at Tokens[value].calc() to tweetSum
    //at the end of loop,
    //store id and tweetSum in map
}

int Analyzer::outputPredictions(){
    int sentiment;
    
    FILE *fp;
    fp = fopen ("/users7/cse/ageer/DataStrc/assignment-2-don-t-be-sentimental-aag2104/assignment-2-don-t-be-sentimental-aag2104-1/data/results.csv", "w");

    for (const auto& tweet: TweetSums) {
        if(tweet.second < 0){
            sentiment = 0;
        } else {
            sentiment = 4;
        }
        std::cout << tweet.first << ": " << tweet.second << std::endl;
        char* idNum = {tweet.first.getData()};
        char sentChar = sentiment;
        fputc(sentChar, fp);
        fputs(", ", fp);
        fputs(idNum, fp);
        fputs("\n", fp);
        
    }   

    //output all tweets -> sentiment, idNum
    //if int (tweetSum) is less than 0, sentiment == 0, else sentiment = 4
}

void Analyzer::train() //char* trainingData
{
    openTrain(); //trainingData
    tokenizeMap(Tweets);
    //decideSignificance(Tokens);
    std::map<DSString,Ratio>::iterator ij = Tokens.begin();

    for (ij=Tokens.begin(); ij!=Tokens.end(); ++ij){
         std::cout << ij->first << "," << ij->second << "," << ij->second.calculate() << std::endl;
    }
}

void Analyzer::predict(){
    // openTest();
    // TestTweets.erase("id,Date,Qu");
    // iterateThroughTest();


    // //outputPredictions();

    // std::map<DSString,int>::iterator ij = TweetSums.begin();

    // for (ij=TweetSums.begin(); ij!=TweetSums.end(); ++ij){
    //       std::cout << ij->first << "," << ij->second;
    //       std::cout << std::endl;
    // }
    
}

void Analyzer::evaluatePredictions(){
   //outputAccuracy();
}
