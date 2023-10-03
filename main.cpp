#include <iostream>
#include "Analyzer.h"
#include "DSString.h"
#include "Tweet.h"

int main(int argc, char **argv)
{
    if (argc > 1)
    {
        Analyzer analysis;

        analysis.train(argv[1]);
        // argv[1] = "data/train_dataset_20k.csv"
        // argv[2] = "data/test_dataset_10k.csv"
        // argv[3] = "data/test_dataset_sentiment_10k.csv"
        // argv[4] = "results.csv"
        // argv[5] = "accuracy.txt"

        analysis.predict(argv[2], argv[4]);

        analysis.evaluatePredictions(argv[3], argv[5]);
    }

    // paste in terminal to run
    //./sentiment  ../data/train_dataset_20k.csv ../data/test_dataset_10k.csv ../data/test_dataset_sentiment_10k.csv ../data/results.csv ../data/accuracy.txt
    return (0);
}