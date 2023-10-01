#include "Tweet.h"

Tweet::Tweet()
{
    sentiment = ' ';
    message = "empty";
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
    DSString currWord = "";

    do
    {
        currChar = message[index]; // store character

        if (currChar == 33 || currChar == 63) // if ? or !
        {
            words.push_back(currWord); // store
            currWord = "";             // reset word
        }
        else if (currChar == ' ' && currWord[0] != '\0') // if at a space and currWord is not empty (don't want to store empty elements)
        {
            words.push_back(currWord); // store
            currWord = "";             // reset
        }

        if (currChar != ' ' && currChar != '\n') // if we are at a character (not space) and the character is not a newline
        {
            char currC[2]; // convert currChar to char array so it can stored in a DSString
            currC[0] = currChar;
            DSString curr = currC; // stored, now you can concat

            currWord = currWord + curr; // concat
        }

        if (message[index + 1] == '\0')
        {                              // if you are about to be at the end of the vector, you want to store current
            words.push_back(currWord); // store
            break;                     // end
        }

        index++; // move to next char
    } while (currChar != '\0');

    for (int i = 0; i < words.size(); i++)
    { // for some reason i'm still storing blanks
        if (words[i] == "\0")
        {
            words.erase(words.begin() + i);
        }
    }

    for (int i = 0; i < words.size(); i++) // print current vector -for testing purposes
    {
        std::cout << words[i] << "|";
    }
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