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

std::vector<DSString> Tweet::tokenize()
{
    std::vector<DSString> words;

    DSString sent = &sentiment;

    words.push_back(sent);

    int index = 0;
    char currChar;
    DSString currWord;

    do
    {
        currChar = message[index];

        if (currChar == 33 || currChar == 63)
        {
            words.push_back(currWord);
            currWord = "";
        }
        else if (currChar == ' ' && currWord != "")
        { // and current word is not empty
            words.push_back(currWord);
            currWord = "";
        }

        if (currChar != ' ')
        {
            DSString hello = "hello";
            DSString yo = "yo";
            DSString hi = yo + hello;
            std::cout << hi;

            // currWord = currWord + currC doesnt work
        }

        index++;
    } while (currChar != '\0');

    // print current vector -for testing purposes
    //for (int i = 0; i < words.size(); i++)
    //{
       // std::cout << words[i] << ",";
    //}
    std::cout << std::endl;

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