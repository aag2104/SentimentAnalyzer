#include <iostream>
#include "Analyzer.h"
#include "DSString.h"
#include "Tweet.h"

int main(){ //int argc, char** argv
    
    Analyzer analysis;
    
    analysis.train(); //argv[1]
    //argv[1] = "data/train_dataset_20k.csv"
    //argv[2] = "data/test_dataset_10k.csv"
    //argv[3] = 
    
    analysis.predict();
    analysis.evaluatePredictions();
    
    //paste in terminal when you run 
    //./sentiment data/train_dataset_20k.csv data/test_dataset_10k.csv data/test_dataset_sentiment_10k.csv results.csv accuracy.txt
    //./sentiment ../ ->
    return(0);
}