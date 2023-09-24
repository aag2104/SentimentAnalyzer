#include "Tweet.h"


Tweet::Tweet()
{
    sentiment = ' ';
    message = "empty message";
}

Tweet::Tweet(DSString tweetTxt, char sent)
{
    sentiment = sent;
    message = tweetTxt;
}

int Tweet::tokenize()
{ 
    int index = 0;
    char currChar;
    std::string word = ""; 
    do{
        currChar = message[index];
        if(message[index+1] == ' '){ //if there is going to be a space?
            //if it does exist-> 
            


            //if it doesnt exist already->
            if(sentiment == '4'){
                Ratio wordRatio = {1,0,0}; 
                Tokens.insert({word, wordRatio});
            } else {
                Ratio wordRatio = {0,0,0};
                Tokens.insert({word, wordRatio});
            }
            word = ""; //reset word
        } else {
            word += currChar;
        }
        //also check for special characters

        index++;
    } while (message[index] != '\0');
    //remember to operate on Tweet.message!
    //called on a tweet obj -> turns into words and stores in Tokens map
    
    std::map<std::string,Ratio>::iterator it = Tokens.begin();


    for (it=Tokens.begin(); it!=Tokens.end(); ++it){
        std::cout << it->first << " => " << it->second << '\n';
    }

    return 0;
}

char Tweet::getSentiment()
{
    return sentiment;
}

DSString Tweet::getMessage()
{
    return message;
}

std::ostream &operator<<(std::ostream &output, const Tweet &txt)
{
    
    output << txt.message;
    return output;

}