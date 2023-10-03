// where we train and test data
#include <cstring>
#include <iostream>
#include <fstream>
#include <cstdio>

#include "Analyzer.h"

char *Analyzer::clean(char *tweet) // cleans out unecessary punctuation and special characters in tweet
{
    int index = 0;       // keeps track of index values
    char currChar = ' '; // keeps track of current character in tweet
    do
    {
        currChar = tweet[index];
        if (tweet[index] < 0 || tweet[index] > 128) // checks if not ASCII
        {
            tweet[index] = ' '; // replaces with space
        }
        if ((tweet[index] >= 34 && tweet[index] <= 38) || (tweet[index] >= 40 && tweet[index] <= 47)) // non a-z, A-B, !? ASCII values
        {
            tweet[index] = ' '; //^^
        }
        if ((tweet[index] >= 58 && tweet[index] <= 62) || tweet[index] == 64) // non a-z, A-B, !? ASCII values
        {
            tweet[index] = ' '; //^^
        }
        if ((tweet[index] >= 91 && tweet[index] <= 96) || (tweet[index] >= 123 && tweet[index] <= 126)) // non a-z, A-B, !? ASCII values
        {
            tweet[index] = ' '; //^^
        }
        if (tweet[index] == '\n')
        {
            tweet[index] = ' '; //^^
        }
        if ((tweet[index] >= 0 && tweet[index] <= 31) || tweet[index] == 127) // non a-z, A-B, !? ASCII values
        {
            tweet[index] = ' '; //^^
        }
        index++;                // increments index every loop
    } while (currChar != '\0'); // runs till end of char*
    return tweet;               // returns cleaned tweet
}

void Analyzer::tokenizeMap(std::map<DSString, Tweet> messages) // returns vector of words w/ tweet sentiment in index[0]
{
    std::map<DSString, Tweet>::iterator it = messages.begin(); // it = iterator associated with messages map

    for (it = messages.begin(); it != messages.end(); ++it) // loops through messages map from start to finish
    {
        storeWords(it->second.tokenize()); // returns vector of strings with sentiment of tweet in index[0]
    }
}

// tweet is a vector of words (DSString)
void Analyzer::storeWords(std::vector<DSString> tweet) // iterates through vector and stores words with ratio values/edits current ratio values
{
    DSString sentiment = tweet[0]; // 1st spot in vector is the tweet's sentiment, store

    for (size_t i = 1; i < tweet.size(); i++) // iterate though vector...
    {
        if (Tokens.find(tweet[i]) == Tokens.end()) // if tweet is not already in Token's map...
        {                                          // not found in Tokens map
            if (sentiment == "4")                  // if the tweet's sentiment == 4... (aka positive)
            {
                Ratio rat = {1, 0, 0};          // num = positive, create ratio
                Tokens.insert({tweet[i], rat}); // insert into map
            }
            else
            {                                   //  if sentiment is negative (0
                Ratio rat = {0, 1, 0};          // denom = negative, create ratio
                Tokens.insert({tweet[i], rat}); // insert into map
            }
        }
        else
        {                                                   // in Tokens map already
            if (sentiment == "4")                           // if the tweet's sentiment == 4... (aka positive)
            {                                               // positive
                int newNum = Tokens[tweet[i]].getNum() + 1; // edit current ratio (add 1 to num/good count)
                Tokens[tweet[i]].setNum(newNum);            // store this new value ^ in ratio of Token
            }
            else
            {                                                   // if sentiment is negative (0)
                int newDenom = Tokens[tweet[i]].getDenom() + 1; // edit current ratio (add 1 to denom/bad count)
                Tokens[tweet[i]].setDenom(newDenom);            // store this new value ^ in ratio of Token
            }
        }
    }
}

void Analyzer::decideSignificance(std::map<DSString, Ratio>) // decides whether a word is to be classifed as positive or negative
{
    std::map<DSString, Ratio>::iterator it = Tokens.begin(); // iterator that starts at beginning of Tokens map

    for (it = Tokens.begin(); it != Tokens.end(); ++it) // iterates through Tokens map
    {
        if (it->second.calculate() < 0) // if calculate result is less then zero
        {
            it->second.setCalc(-1); // word is negative
        }
        else // if greater than zero
        {
            it->second.setCalc(1); // word is positive
        }
    }
}

int Analyzer::openTrain(char *trainingData) // pass in argv
{
    FILE *stream; // create place for file

    // set up the buffer
    char line[10000]; // maximum line length

    stream = fopen(trainingData, "r"); // open training data for reading
    if (stream == NULL)                // if the stream is empty...
    {
        std::cerr << "Opening the file failed!" << std::endl; // the file did not open correctly
        return (-1);                                          // return -1 as (error)
    }

    fgets(line, sizeof(line), stream); // get first line - don't need it

    while (fgets(line, sizeof(line), stream) != NULL) // iterate through lines in file
    {
        char *sentiment = new char[2]; // create place for sentiment value
        char *id = new char[11];       // create place for id value

        char tweet[200] = {0}; // create place for tweet

        sentiment[0] = line[0]; // index 0 of each line holds sentiment, set sentiment to value
        sentiment[1] = '\0';    // last spot in sentiment should hold nullchar

        for (int i = 2; i < 12; i++) // iterate through 10 digits to hold id value
        {
            id[i - 2] = line[i]; // store
        }
        id[10] = '\0'; // last value in id should be nullchar

        int commaCounter = 0; // to count commas in line
        int line_index = 0;   // counts index values
        int tweet_index = 0;  // keeps track of tweet index

        while (line_index < (int)sizeof(line)) // iterate till end of line
        {
            if (commaCounter == 5) // if we have reached 5 commas, that means we are at tweet...
            {
                do
                {
                    tweet[tweet_index] = line[line_index]; // store line char in tweet - starting at index 0
                    tweet_index++;                         // increment both indexes ->
                    line_index++;
                } while (line[line_index] != '\n'); // do until we hit newline char (end of line)
                break;                              // exit loop
            }

            if (line[line_index] == ',') // if we reach a comma...
            {
                commaCounter++; // add to counter
            }

            line_index++; // increase line index by 1
        }

        char *cleanTweet = clean(tweet); // call clean tweet and store new tweet in char* cleanTweet
        DSString message = cleanTweet;   // convert to DSString
        DSString idNum(id);              // convert id char* to DSString
        delete[] id;                     // delete char* id <- no longer needed
        DSString sent(sentiment);        // convert sentiment char* to DSString
        delete[] sentiment;              // delete char* sentiment <- no longer needed
        message = message.toLower();     // call toLower() on message and restore into message
        Tweet txt(message, sent);        // store message and sentiment into Tweet obj

        Tweets.insert({idNum, txt}); // insert id and tweet into Tweets map
    }

    fclose(stream); // close file
    return 0;
}

int Analyzer::openTest(char *testingData) // pass in argv
{

    FILE *stream; // create place for file

    // set up the buffer
    char line[1000]; // maximum line length

    stream = fopen(testingData, "r"); // open testing data for reading
    if (stream == NULL)               // if the stream is empty...
    {
        std::cerr << "Opening the file failed!" << std::endl; // the file did not open correctly
        return (-1);                                          // return -1 as (error)
    }

    fgets(line, sizeof(line), stream); // get first line - don't need it

    while (fgets(line, sizeof(line), stream) != NULL) // iterate through lines in file
    {
        char *sentiment = new char[2]; // create place for sentiment value - in this case there isnt one
        char *id = new char[11];       // create place for id value

        char tweet[200] = {0}; // create place for tweet

        sentiment[0] = '3';  // set to 3, it doesnt really matter, only there for storing in Tweet obj
        sentiment[1] = '\0'; // last char should be nullchar

        for (int i = 0; i < 10; i++) // iterate through 10 digits to hold id value
        {
            id[i] = line[i]; // store
        }
        id[10] = '\0'; // last value in id should be nullchar

        int commaCounter = 0; // to count commas in line
        int line_index = 0;   // counts index values
        int tweet_index = 0;  // keeps track of tweet index

        while (line_index < (int)sizeof(line)) // iterate till end of line
        {
            if (commaCounter == 4) // if we have reached 4 commas, that means we are at tweet...
            {
                do
                {
                    tweet[tweet_index] = line[line_index]; // store line char in tweet - starting at index 0
                    tweet_index++;                         // increment both indexes ->
                    line_index++;
                } while (line[line_index] != '\n'); // do until we hit newline char (end of line)
                break;                              // exit loop
            }

            if (line[line_index] == ',') // if we hit a comma
            {
                commaCounter++; // increment comma counter
            }

            line_index++; // increment line index
        }

        char *cleanTweet = clean(tweet); // call clean tweet and store new tweet in char* cleanTweet
        DSString message = cleanTweet;   // convert to DSString
        DSString idNum(id);              // convert id char* to DSString
        delete[] id;                     // delete char* id <- no longer needed
        DSString sent(sentiment);        // convert sentiment char* to DSString
        delete[] sentiment;              // delete char* sentiment <- no longer needed
        message = message.toLower();     // call toLower() on message and restore into message
        Tweet txt(message, sent);        // store message and sentiment into Tweet obj

        TestTweets.insert({idNum, txt}); // insert id and tweet into TestTweets map
    }

    fclose(stream); // close file
    return 0;
}

int Analyzer::openAnswers(char *sentiments) // opens answers file and stores into Answers map
{

    FILE *stream; // place for file

    // set up the buffer
    char line[1000]; // maximum line length

    stream = fopen(sentiments, "r"); // reading sentiments file
    if (stream == NULL)              // if empty...
    {
        std::cerr << "Opening the file failed!" << std::endl; // the file did not open correctly
        return (-1);                                          // return -1 as (error)
    }

    fgets(line, sizeof(line), stream); // do not need first line

    while (fgets(line, sizeof(line), stream) != NULL) // iterate through lines in file
    {
        char *sentiment = new char[2]; // create a place for sentiment
        char *id = new char[11];       // create a place for id

        sentiment[0] = line[0]; // index 0 of each line holds sentiment, set sentiment to value
        sentiment[1] = '\0';    // last char should be nullchar

        for (int i = 2; i < 12; i++) // iterate through 10 digits to hold id value
        {
            id[i - 2] = line[i]; // store
        }
        id[10] = '\0'; // last value in id should be nullchar

        DSString idNum(id);       // convert id char* to DSString
        delete[] id;              // delete char* id <- no longer needed
        DSString sent(sentiment); // convert sentiment char* to DSString
        delete[] sentiment;       // delete char* sentiment <- no longer needed

        Answers.insert({idNum, sent}); // insert id and sentiment into answers map
    }

    fclose(stream); // close file
    return 0;
}

void Analyzer::outputAccuracy(char *accuracyFile) // creates and writes to accuracy file
{
    int correct = 0;               // stores number of correct predictions
    double numInDataSet = 0;       // keeps track of how much data is in dataset
    double accuracy;               // will hold final accuracy calculation
    FILE *fp;                      // holds file
    fp = fopen(accuracyFile, "w"); // create, open, and write to file

    std::map<DSString, DSString>::iterator it1 = Answers.begin(); // iterator that starts at beginning of Answers map
    std::map<DSString, char>::iterator it2 = Predictions.begin(); // iterator that starts at beginning of Predictions map

    for (it1 = Answers.begin(); it1 != Answers.end(); ++it1) // iterate through Answers map
    {                                                        // finding accuracy

        if (Answers.find(it2->first) != Answers.end()) // if current predictions id is found in answers map...
        {
            char *predictionsSent = new char[2]; // create space for predictions sentiment
            predictionsSent[0] = it2->second;    // hold current sentiment
            predictionsSent[1] = '\0';           // last char needs to store nullchar
            DSString sent(predictionsSent);      // convert to DSString
            delete[] predictionsSent;            // we no longer need char* predictionSent - delete

            auto i = Answers.find(it2->first); // store index where Answers has current id

            if (sent == i->second) // if the sentiments of predictions and answers map (for same id value) match...
            {
                correct++; // increment correct count
            }
        }
        it2++; // increment vars ->
        numInDataSet++;
    }

    accuracy = correct / numInDataSet; // calculate accuracy
    fprintf(fp, "%.3f", accuracy);     // print accuracy with 3 decimal points
    fputs("\n", fp);                   // formatting

    for (const auto &output : Predictions) // iterate through predictions
    {

        fputc(output.second, fp); // write ground truth to file
        fputs(", ", fp);

        auto i = Answers.find(output.first); // find what sentiment the program predicted for the same tweet

        char *sent = i->second.getData(); // get the "data" at that spot - sentiment
        fputs(sent, fp);                  // write predicted sentiment to file
        fputs(", ", fp);                  // formatting

        char *id = output.first.getData(); // find id at current tweet
        fputs(id, fp);                     // write id to file

        fputs("\n", fp); // formatting
    }

    fclose(fp); // close file
}

void Analyzer::iterateThroughTest() // stores test tweets in tweet sum
{
    std::map<DSString, Tweet>::iterator ij = TestTweets.begin(); // creates iterator that starts at beginning of Test tweets map

    for (ij = TestTweets.begin(); ij != TestTweets.end(); ++ij) // iterates through tweets
    {
        std::vector<DSString> words = ij->second.tokenize(); // iterates through map of words
        int tweetSum = 0;
        for (size_t i = 0; i < words.size(); i++) // iterates through words map
        {
            if (Tokens.find(words[i]) != Tokens.end()) // checks ->
            {                                          // if vector word is in map...
                auto it = Tokens.find(words[i]);       // finds place where word is located
                tweetSum += it->second.calculate();    // adds calc values of words in tweet to tweet sum
            }
        }
        DSString id = ij->first;          // id num equals whatever id is in the key of TestTweets map
        TweetSums.insert({id, tweetSum}); // insert ids and their sums into map
    }
}

void Analyzer::outputPredictions(char *results) // prints results
{
    char sentiment; // holds sentiment value

    FILE *fp;                 // holds file
    fp = fopen(results, "w"); // opens file to write - "w"

    for (const auto &tweet : TweetSums) // iterates through tweetSums
    {
        if (tweet.second < 0) // if the tweet's sum is less then zero -> it leans negative
        {
            sentiment = '0';
        }
        else // if the tweet's sum is less then zero -> it leans negative
        {
            sentiment = '4';
        }
        Predictions.insert({tweet.first, sentiment}); // insert predictions into map because we need them for later

        char *idNum = {tweet.first.getData()}; // format and print data into file ->
        fputc(sentiment, fp);
        fputs(", ", fp);
        fputs(idNum, fp);
        fputs("\n", fp);
    }

    fclose(fp); // close file
}

void Analyzer::train(char *trainingData) // trains program to identify sentiments
{
    openTrain(trainingData);    // opens training data
    tokenizeMap(Tweets);        // splits tweets into words
    decideSignificance(Tokens); // makes final decision whether word is positive or negative
}

void Analyzer::predict(char *testingData, char *results) // makes prediction on test data
{
    openTest(testingData);          // opens file with test tweets
    TestTweets.erase("id,Date,Qu"); // gets rid of header data
    iterateThroughTest();           // iterates through test tweets and tokenizes
    outputPredictions(results);     // decides and predicts
}

void Analyzer::evaluatePredictions(char *sentimentData, char *accuracy) // evaluates how accurate predictions are
{
    openAnswers(sentimentData); // opens file with answers
    outputAccuracy(accuracy);   // prints out accuracy
}
