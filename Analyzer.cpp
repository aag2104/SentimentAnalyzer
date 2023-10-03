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
    std::map<DSString, Ratio>::iterator it = Tokens.begin();

    for (it = Tokens.begin(); it != Tokens.end(); ++it)
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
    FILE *stream;

    // set up the buffer
    char line[10000]; // maximum line length

    stream = fopen(trainingData, "r"); // trainingData
    if (stream == NULL)
    {
        std::cerr << "Opening the file failed!" << std::endl;
        return (-1);
    }

    fgets(line, sizeof(line), stream);

    while (fgets(line, sizeof(line), stream) != NULL)
    {
        char *sentiment = new char[2];
        char *id = new char[11];

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

        char *cleanTweet = clean(tweet);
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

int Analyzer::openTest(char *testingData)
{
    // char filename[] = "/users7/cse/ageer/DataStrc/assignment-2-don-t-be-sentimental-aag2104/assignment-2-don-t-be-sentimental-aag2104/data/test_dataset_10k.csv";
    FILE *stream;

    // set up the buffer
    char line[1000]; // maximum line length

    stream = fopen(testingData, "r");
    if (stream == NULL)
    {
        std::cerr << "Opening the file failed!" << std::endl;
        return (-1);
    }

    fgets(line, sizeof(line), stream);

    while (fgets(line, sizeof(line), stream) != NULL)
    {
        char *sentiment = new char[2];
        char *id = new char[11];

        char tweet[200] = {0};

        sentiment[0] = '3';
        sentiment[1] = '\0';

        for (int i = 0; i < 10; i++)
        {
            id[i] = line[i];
        }
        id[10] = '\0';

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

        char *cleanTweet = clean(tweet);
        DSString message = cleanTweet;
        DSString idNum(id);
        delete[] id;
        DSString sent(sentiment);
        delete[] sentiment;
        message = message.toLower();
        Tweet txt(message, sent);

        TestTweets.insert({idNum, txt});
    }

    fclose(stream);
    return 0;
}

int Analyzer::openAnswers(char *sentiments)
{
    // char filename[] = "/users7/cse/ageer/DataStrc/assignment-2-don-t-be-sentimental-aag2104/assignment-2-don-t-be-sentimental-aag2104-1/data/test_dataset_sentiment_10k.csv";
    FILE *stream;

    // set up the buffer
    char line[1000]; // maximum line length

    stream = fopen(sentiments, "r");
    if (stream == NULL)
    {
        std::cerr << "Opening the file failed!" << std::endl;
        return (-1);
    }

    fgets(line, sizeof(line), stream);

    while (fgets(line, sizeof(line), stream) != NULL)
    {
        char *sentiment = new char[2];
        char *id = new char[11];

        sentiment[0] = line[0];
        sentiment[1] = '\0';

        for (int i = 2; i < 12; i++)
        {
            id[i - 2] = line[i];
        }
        id[10] = '\0';

        DSString idNum(id);
        delete[] id;
        DSString sent(sentiment);
        delete[] sentiment;

        Answers.insert({idNum, sent});
    }

    fclose(stream);
    return 0;
}

void Analyzer::outputAccuracy(char *accuracyFile)
{
    int correct = 0;
    double numInDataSet = 0;
    double accuracy;
    FILE *fp;
    // fp = fopen ("/users7/cse/ageer/DataStrc/assignment-2-don-t-be-sentimental-aag2104/assignment-2-don-t-be-sentimental-aag2104-1/data/accuracy.txt","w");
    fp = fopen(accuracyFile, "w");

    std::map<DSString, DSString>::iterator it1 = Answers.begin();
    std::map<DSString, char>::iterator it2 = Predictions.begin();

    for (it1 = Answers.begin(); it1 != Answers.end(); ++it1)
    { // finding accuracy

        if (Answers.find(it2->first) != Answers.end())
        {
            char *predictionsSent = new char[2];
            predictionsSent[0] = it2->second;
            predictionsSent[1] = '\0';
            DSString sent(predictionsSent);
            delete[] predictionsSent;

            auto i = Answers.find(it2->first);

            if (sent == i->second)
            {
                correct++;
            }
        }
        it2++;
        numInDataSet++;
    }

    accuracy = correct / numInDataSet;
    fprintf(fp, "%.3f", accuracy);
    fputs("\n", fp);

    for (const auto &output : Predictions)
    {

        fputc(output.second, fp);
        fputs(", ", fp);

        auto i = Answers.find(output.first);

        char *sent = i->second.getData();
        fputs(sent, fp);
        fputs(", ", fp);

        char *id = output.first.getData();
        fputs(id, fp);

        fputs("\n", fp);
    }

    fclose(fp);
}

int Analyzer::iterateThroughTest()
{
    std::map<DSString, Tweet>::iterator ij = TestTweets.begin();

    for (ij = TestTweets.begin(); ij != TestTweets.end(); ++ij)
    {
        std::vector<DSString> words = ij->second.tokenize(); // words in tweetline
        int tweetSum = 0;
        for (size_t i = 0; i < words.size(); i++)
        {
            if (Tokens.find(words[i]) != Tokens.end())
            { // if vector word is in map...
                auto it = Tokens.find(words[i]);
                tweetSum += it->second.calculate();
            }
        }
        DSString id = ij->first;
        TweetSums.insert({id, tweetSum});
    }
}

int Analyzer::outputPredictions(char *results)
{
    char sentiment;

    FILE *fp;
    // fp = fopen ("/users7/cse/ageer/DataStrc/assignment-2-don-t-be-sentimental-aag2104/assignment-2-don-t-be-sentimental-aag2104-1/data/results.csv", "w");
    fp = fopen(results, "w");

    for (const auto &tweet : TweetSums)
    {
        if (tweet.second < 0)
        {
            sentiment = '0';
        }
        else
        {
            sentiment = '4';
        }
        Predictions.insert({tweet.first, sentiment});

        char *idNum = {tweet.first.getData()};
        fputc(sentiment, fp);
        fputs(", ", fp);
        fputs(idNum, fp);
        fputs("\n", fp);
    }

    fclose(fp);
}

void Analyzer::train(char *trainingData) // char* trainingData
{
    openTrain(trainingData); // trainingData
    tokenizeMap(Tweets);
    decideSignificance(Tokens);
}

void Analyzer::predict(char *testingData, char *results)
{
    openTest(testingData);
    TestTweets.erase("id,Date,Qu");
    iterateThroughTest();
    outputPredictions(results);
}

void Analyzer::evaluatePredictions(char *sentimentData, char *accuracy)
{
    openAnswers(sentimentData);
    outputAccuracy(accuracy);
}
