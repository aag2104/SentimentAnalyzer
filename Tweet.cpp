#include "Tweet.h"

Tweet::Tweet() // default constructor
{
    sentiment = "";   // set sentiment to empty char (space)
    message = "empty"; // set message to "empty"
}
Tweet::Tweet(DSString tweetTxt, DSString sent) // parameterized constructor
{
    sentiment = sent; // set private vars to args values ->
    message = tweetTxt;
}

std::vector<DSString> Tweet::tokenize() //splits tweets into words and outputs a vector of the tweet's words (separated)
{
    std::vector<DSString> words; //vector where words will be stored
    char currChar; //char that holds current character 
    words.push_back(sentiment); //adds sentiment to vector (first element)

    for(size_t i = 0; i < message.length(); i++){ //iterates through tweet's length
        currChar = message[i]; //stores current char in tweet 
        if(currChar != ' '){ //if we reach a space
             int count = 0; //count to keep track of chars till next space
             do{ //iterates through message until next space
                count++; 
                if(i+count >= message.length()){ //if count goes out of bounds, break out of loop
                    break;
                }
                currChar = message[i+count]; //stores current spot in currChar
             }while(currChar != ' '); //"until next space"
            if(i+count < message.length()){ //if we have not gone out of bounds...
                DSString currWord = message.substring(i, count); //store substring (word before next space)
                words.push_back(currWord); //add substring to vector
            }
            i += (count-1); //increment i to avoid iterating over words more than once

        }
    }

     return words; //return filled vector

}

DSString Tweet::getSentiment() //getter - returns sentiment
{
    return sentiment;
}

DSString Tweet::getMessage() //getter - returns messsage
{
    return message;
}

std::ostream &operator<<(std::ostream &output, const Tweet &txt) //overloaded << operator
{
    output << txt.message; //when using << with tweet obj, print out tweet's message
    return output;
}