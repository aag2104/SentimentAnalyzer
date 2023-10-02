#include "Tweet.h"

Tweet::Tweet() // default constructor
{
    sentiment = ' ';   // set sentiment to empty char (space)
    message = "empty"; // set message to "empty"
}
Tweet::Tweet(DSString tweetTxt, char sent) // parameterized constructor
{
    sentiment = sent; // set private vars to args values ->
    message = tweetTxt;
}

std::vector<DSString> Tweet::tokenize()
{
    std::vector<DSString> words;
    char currChar;
    DSString currWord = "";

    for(size_t i = 0; i < message.length(); i++){
        currChar = message[i];
        if(currChar != ' '){ 
             int count = 0;
             do{
                count++;
                currChar = message[i+count];
             }while(currChar != ' ');
            currWord = message.substring(i, count);
            words.push_back(currWord);
            currWord = "";
            i += (count-1);
        }
    }

    // for(size_t i = 0; i < words.size(); i++){
    //     std::cout << words[i] << "|";
    // }
    // std::cout << std::endl;

     return words;

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