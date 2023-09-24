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
        index++;
    }while (currChar != '\0');
    return 0;
}

int Analyzer::convert_and_store(int sentiment, std::string id, char* tweet){
    DSString message = tweet;
    message = message.toLower();
    
    Tweets.insert({id, message});
    
    std::map<std::string,DSString>::iterator it = Tweets.begin();

    /*prints current map 
    for (it=Tweets.begin(); it!=Tweets.end(); ++it){
        std::cout << it->first << " => " << it->second << '\n';
    }
    */

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
        int sentiment;
        char id[20] = {0};
        char tweet[1000] = {0};
               
        sentiment = line[0];
               
        for(int i = 2; i < 12; i++){
            id[i-2] = line[i];
        }
    
        int commaCounter = 0;
        int line_index = 0;
        int tweet_index = 0;

        while (line_index < sizeof(line)){
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
    //call tweet class method to begin other operations
    return 0;
}
