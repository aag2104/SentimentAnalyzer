#include "Tweet.h"


Tweet::Tweet()
{
    sentiment = 0;
    message = "empty message";
}

Tweet::Tweet(DSString tweetTxt, int sent)
{
    sentiment = sent;
    message = tweetTxt;
}

int Tweet::tokenize()
{
    //called on a tweet obj -> turns into words and stores in Tokens map

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