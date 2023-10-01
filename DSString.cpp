#include "DSString.h"
#include "string.h"

/*
 * Implement the functions defined in DSString.h. You may add more functions as needed
 * for the project.
 *
 * Note that c-strings use `\0` as a terminator symbol
 * but your class should store its length in a member variable. Do not use c-string functions
 * from <string.h> or <cstring> other than for conversion from a c-string.
 *
 * you can use `strlen()` and `strcpy()` in your constructor or assignment operator...
 * when you convert a c-string into a DSString.
 */

DSString::DSString()
{ // default constructor - called when DSString object is made without args
    data = new char[1];
    data[0] = '\0';
    len = 0;
}
DSString::DSString(const char *txt)
{ // paramaterized constructor - called when DSString object is made WITH args
    len = 0;
    while(txt[len] != '\0'){
        len++;
    }
    
    data = new char[len + 1];
    
    for(size_t i = 0; i < len; i++){
        data[i] = txt[i];
    }
    data[len] = '\0';
}

DSString::DSString(const DSString &copy_char)
{ // copy constructor
    const int end = copy_char.len;
    data = new char[copy_char.len];

    for (int i = 0; i < end; i++)
    {
        data[i] = copy_char.data[i];
    }
    len = copy_char.len;
    data[len] = '\0';
}

DSString::~DSString()
{ // destructor
    delete[] data;
}

DSString &DSString::operator=(const DSString &copy)
{ // copy assignment
    if(data != copy.data){
        delete[] data;
        data = new char[copy.len];
        len = copy.len;
        for(size_t i = 0; i < len; i++){
            data[i] = copy.data[i];
        }
        data[len] = '\0';
    }
 
    return *this;
}

size_t DSString::length() const
{
    return len;
}

char &DSString::operator[](size_t index)
{ // returns a reference to the character at the given index
    return data[index];
}

DSString DSString::operator+(const DSString &appendString) const // Overloaded operator+ which appends the string in the argument to this string
{
    const int size1 = len;
    const int size2 = appendString.len;

    const int s = (size1 + size2); 
    char* newString = new char[s+1]; //add 1 only in creation 

    for (int i = 0; i < size1; i++)
    {
        newString[i] = data[i];
        //std::cout << newString[i];
    }
    int j = 0;
    for (int i = size1; i < s; i++)
    {
        newString[i] = appendString.data[j];
        //std::cout << newString[i];
        j++;
    }

    newString[s] = '\0';
    DSString newDSString(newString);
    delete[] newString;

    return newDSString;
}

// Standard relational operators to compare and order your strings.
// Feel free to add additional.
bool DSString::operator==(const DSString &rhs) const
{
    bool returnVal = true;
    int i = 0;
    do
    {
        if (data[i] == rhs.data[i])
        {
            returnVal = true;
        }
        else
        {
            return false;
        }
        i++;
    } while (data[i] != '\0' && rhs.data[i] != '\0');

    return returnVal;
}

bool DSString::operator<(const DSString &rhs) const
{
    // if(len > rhs.len){
    //      return false;
    //  } else {
    //      return true;
    // }

    // for(int i = 0; i < len; i++){
    //     if(data[i] > rhs.data[i]){
    //         return false;
    //      }
    //      if(data[i] < rhs.data[i]){
    //          return true;
    //      }
    // }
    // return false;

    int length;
    if(len > rhs.len){
        length = len;
    } else {
        length = rhs.len;
    }
    for(int i = 0; i < length; i++){
        if(data[i] == '\0'){
            return true;
        } else if(rhs.data[i] == '\0'){
            return false;
        }

        if(data[i] > rhs.data[i]){
            return false;
        }
        if(data[i] < rhs.data[i]){
            return true;
        }
    }

    return false;
   
}

bool DSString::operator!=(const DSString &rhs) const
{

    if (len != rhs.len)
    {
        return false;
    }

    for (size_t i = 0; i < len; ++i)
    {
        if (data[i] != rhs.data[i])
        {
            return false;
        }
    }
    return true;
}

DSString DSString::substring(size_t start, size_t numChars) const
{
    /*returns a new string object that contains a
     * sequence of characters from this string object.
     *
     * param start - the index of where to start
     * param numChars - the number (count) of characters to copy into
     *    the substring
     * @return a DSString object containing the requested substring
     */

    const size_t newSize = numChars;
    char* newString = new char[newSize+1];
    for (size_t i = 0; i <= newSize; i++)
    {
        newString[i] = data[i + start];
    }

    newString[newSize] = '\0';
    DSString newDSString(newString);
    delete[] newString;
    return newDSString;
}

void DSString::toLower()  // Returns a new string object with all characters in lowercase
{

    for (size_t i = 0; i < len; i++)
    {
        if (data[i] <= 90 && data[i] >= 65)
        {
            data[i] = data[i] + 32;
        }
        
    }
    
}

char *DSString::c_str() const
{
    /**
     * the c_str function returns a pointer a null-terminated c-string holding the
     * contents of this object. Since data already has a `\0`
     * at the end of the string in DSString so you can just return a pointer to data.
     **/
    return data;
}

char *DSString::getData() const
{
    return data;
}

std::ostream &operator<<(std::ostream &output, const DSString &txt)
{
    /**
     * Overloaded stream insertion operator to print the contents of this
     * string to the output stream in the first argument. Remember:
     * This operator needs to be implemented outside of the class as
     * a friend because it operates on the stream and not the DSString object.
     **/
    output << txt.getData();
    return output;
}
