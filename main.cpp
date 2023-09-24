#include <iostream>
#include "Analyzer.h"

int main(int argc, char** argv)
{  

/*
    Your program should take 5 command line arguments in this order:
    1. training data set filename - the file with the training tweets
    2. testing data set filename - tweets that your program will classify
    3. testing data set sentiment filename - the file with the classifications for the testing tweet data
    4. classifier results file name - see Output Files section below
    5. classifier accuracy and errors file name - see Output Files section below

    Example: In the build folder executing this command in the terminal should work.
    
    ./sentiment data/train_dataset_20k.csv data/test_dataset_10k.csv 
    data/test_dataset_sentiment_10k.csv results.csv accuracy.txt
    
*/
    
    std::cout << "I will be a sentiment analyzer!" << std::endl;

/*
    Your program should produce two output files. The first file should contain your classifier's
    results for all tweets in the testing dataset in the same format as the sentiment file:

    4, 1467811596
    ...

    The second file should be organized as follows:
    * The first line of the output file will contain the accuracy, a single floating point number with exactly 3 decimal places of precision.  
    See the section “How good is your classifier” below to understand Accuracy.
    * The remaining lines of the file will contain for each tweet that your algorithm incorrectly 
    classified your prediction,
    the ground truth and the Tweet ID. This could be useful information 
    as you tweak your algorithm to increase efficiency.

    Example of the testing data tweet classifications file:

    0.500
    4, 1, 2323232323
    1, 3, 1132553423
*/

/*
Clearly separate training from testing in your code. 
You should implement your classifier model in a class 
and your main function could look like this pseudo code:

```cpp
int main(some args)
{
   SentimentClassifier classifier;
   
   classifier.train(some args);

   classifier.predict(some args);
   classifier.evaluatePredictions(some args);

   return 0;
}
*/

    return 0;
}