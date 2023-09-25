//where we train and test data
#include <cstring>
#include <iostream>
#include <fstream>
#include <cstdio>

#include "Analyzer.h"

int Analyzer::clean(char* tweet){
    int index = 0;
    char currChar = ' ';
    do{
        currChar = tweet[index];
        if(tweet[index] < 0 || tweet[index] > 128){
            tweet[index] = ' '; //keep this in mind when you are tokenizing
        }

        if((tweet[index] >= 34 && tweet[index] <= 38) || (tweet[index] >= 40 && tweet[index] <= 47)){
            tweet[index] = ' ';
        }

        if((tweet[index] >= 58 && tweet[index] <= 62) || tweet[index] == 64){
            tweet[index] = ' ';
        }

        if((tweet[index] >= 91 && tweet[index] <= 96) || (tweet[index] >= 123 && tweet[index] <= 126)){
            tweet[index] = ' ';
        }

        index++;
    }while (currChar != '\0');
    return 0;
}

int Analyzer::tokenize_map(std::map<std::string, Tweet> messages)
{
    std::map<std::string,Tweet>::iterator it = messages.begin();


    for (it=messages.begin(); it!=messages.end(); ++it){
        it->second.tokenize();
    }
    
    
    /* iterate till end of map 
        call tweet.tokenize() - returns vector of words w/ tweet sentiment in index[0]
        store_words() -> iterates through vector and stores words with ratio values/edits current ratio values
    */
    return 0;
}

int Analyzer::convert_and_store(std::string sentiment, std::string id, char* tweet){
    DSString message = tweet;
    message = message.toLower();

    Tweet txt(message, sentiment);
    
    Tweets.insert({id, txt});

    return 0;
}

int Analyzer::open_and_parse(){
    char filename[] = "/Users/alexandrageer/2341Projects/assignment-2-don-t-be-sentimental-aag2104/data/SmallDataSet.txt";
    FILE *stream;
           
    // set up the buffer
    char line[1000]; // maximum line length

    stream = fopen(filename, "r");
    if (stream == NULL) {
        std::cerr << "Opening the file failed!" << std::endl;
        return(-1);
    }

        
    while (fgets(line, sizeof(line), stream) != NULL){
        std::string sentiment;
        char id[20] = {0};
        char tweet[1000] = {0};
               
        sentiment = line[0];
               
        for(int i = 2; i < 12; i++){
            id[i-2] = line[i];
        }
    
        int commaCounter = 0;
        int line_index = 0;
        int tweet_index = 0;

        while (line_index < (int)sizeof(line)){ 
            if(commaCounter == 5){
                do {
                    tweet[tweet_index] = line[line_index];
                    tweet_index++;
                    line_index++;
                } while (line[line_index] != '\0');
                break;
            }
                    
            if(line[line_index] == ','){
                commaCounter++;
            }

            line_index++;      
            }

            clean(tweet);
            convert_and_store(sentiment, id, tweet);
            std::cout << std::endl;
            }
     
    fclose(stream);
    return 0;
}


int Analyzer::train()
{
    open_and_parse();
    tokenize_map(Tweets);
    return 0;
}
