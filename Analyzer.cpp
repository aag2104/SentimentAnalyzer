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

int Analyzer::tokenize_map(std::map<DSString, Tweet> messages) //returns vector of words w/ tweet sentiment in index[0]
{
    std::map<DSString,Tweet>::iterator it = messages.begin();

    for (it=messages.begin(); it!=messages.end(); ++it){
        it->second.tokenize();
        //store_words(it->second.tokenize()); //returns vector of strings with sentiment of tweet in index[0]
    }

    //std::map<std::string,Ratio>::iterator ij = Tokens.begin();

    //for (ij=Tokens.begin(); ij!=Tokens.end(); ++ij){
        //std::cout << ij->first << "->" << ij->second << std::endl;
    //}

    return 0;
}

/*
int Analyzer::store_words(std::vector<DSString> tweet) //iterates through vector and stores words with ratio values/edits current ratio values
{
    char sentiment = tweet[0]; //will be fixed later on

    for(int i = 1; i < tweet.size(); i++){
        
        if (Tokens.find(tweet[i]) == Tokens.end()) { // not found in Tokens map 
            if(sentiment == '4'){ //positive
                Ratio rat = {1,0,0}; //num = positive
                Tokens.insert({tweet[i], rat});
            } else { //negative
                Ratio rat = {0,1,0}; //denom = negative
                Tokens.insert({tweet[i], rat});
            }
        } else { //in Tokens map already
            if(sentiment == '4'){ //positive
                int newNum = Tokens[tweet[i]].getNum() + 1;
                Tokens[tweet[i]].setNum(newNum);
            } else { //negative
                int newDenom = Tokens[tweet[i]].getDenom() + 1;
                Tokens[tweet[i]].setDenom(newDenom);
            }
        }

    }

    return 0;
}
*/
/*
int Analyzer::decide_significance(std::map<std::string, Ratio>)
{
    
   std::map<std::string,Ratio>::iterator it = Tokens.begin();

    for (it=Tokens.begin(); it!=Tokens.end(); ++it){
        if(Tokens[it->first].numOccur() < 5 || (Tokens[it->first].calculate() < 1.1 && Tokens[it->first].calculate() > .9)){
            Tokens.erase(it->first);
        }
    }
    

    
    std::map<std::string,Ratio>::iterator it2 = Tokens.begin();

    for (it2=Tokens.begin(); it2!=Tokens.end(); ++it2){
        if(Tokens[it2->first].calculate() > 1.1){
            Tokens[it2->first].setCalc(1);
        } else {
            Tokens[it2->first].setCalc(-1);
        }
    }
    
    return 0;
}
*/

int Analyzer::convert_and_store(char sentiment, char* id, char* tweet){
    DSString message = tweet;
    DSString idNum = id;
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
        char sentiment;
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
    //decide_significance(Tokens);
    return 0;
}
