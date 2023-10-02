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
    words.push_back(sentiment);

    for(size_t i = 0; i < message.length(); i++){
        currChar = message[i];
        if(currChar != ' '){ 
             int count = 0;
             do{
                count++;
                if(i+count >= message.length()){
                    break;
                }
                currChar = message[i+count];
             }while(currChar != ' ');
            if(i+count < message.length()){
                DSString currWord = message.substring(i, count);
                words.push_back(currWord);
            }
            i += (count-1);

        }
    }

    // for(size_t i = 0; i < words.size(); i++){
    //     std::cout << words[i] << "|";
    // }
    // std::cout << std::endl;

     return words; //return filled vector

}

DSString Tweet::getSentiment()
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