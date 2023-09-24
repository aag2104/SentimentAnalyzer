#include "Tweet.h"


Tweet::Tweet()
{
    sentiment = ' ';
    id = "0";
    message = "empty message";
}

Tweet::Tweet(char sent, char* num, DSString tweetTxt)
{
    sentiment = sent;
    id = num;
    message = tweetTxt;
}

int Tweet::tokenizer(std::map<std::string, DSString>)
{
    

    return 0;
}



char Tweet::getSentiment()
{
    return sentiment;
}

char *Tweet::getId()
{
    return id;
}

DSString Tweet::getMessage()
{
    return message;
}
