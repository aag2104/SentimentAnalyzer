#include "Tweet.h"


Tweet::Tweet()
{
    sentiment = "";
    message = "empty message";
}

Tweet::Tweet(DSString tweetTxt, std::string sent)
{
    sentiment = sent;
    message = tweetTxt;
}

std::vector<std::string> Tweet::tokenize()
{ 
    std::vector<std::string> words; 
    
    words.push_back(sentiment);

    int index = 0; 
    char currChar;
    std::string currWord = "";
    do{
       currChar = message[index];
       if(currChar == 33 || currChar == 63){ //store ! or ? as their own token
            currWord = currChar; //converts currChar to string
            words.push_back(currWord); //stores new string in vector
            currWord = ""; //stored, therefore, reset
            index++;
       } //else if(currChar != ' '){
            //DSString DSWord = message.substring(currChar, message.findNextSpace(currChar));
            //char DSChar = *(DSWord.getData());
            //currWord = DSChar;
            //index = index + DSWord.length();
            //currWord = ""; //reset word
            
            //store substring till next space
            //message.find() returns index of next space 
            //currWord = message.substring(-, message.find())
       //} 
        index++;
    }while (currChar != '\0');
    
    
    //print current vector -for testing purposes
    for(int i = 0; i < words.size(); i++){
        std::cout << words[i] << " ";
    }
    std::cout << std::endl;

    return words;
}

std::string Tweet::getSentiment()
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