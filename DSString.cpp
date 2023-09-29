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
    data = new char[strlen(txt) + 1];
    strcpy(data, txt);
    len = strlen(data) + 1;
}

DSString::DSString(const DSString &copy_char)
{ // copy constructor
    const int end = copy_char.length();
    data = new char[copy_char.length()];

    for (int i = 0; i < end; i++)
    {
        data[i] = copy_char.data[i];
    }
    len = copy_char.length();
}

DSString::~DSString()
{ // destructor
    delete[] data;
}

DSString &DSString::operator=(const DSString &copy)
{ // copy assignment
    if (strcmp(data, copy.data) != 0)
    {
        data = new char[copy.length()];
        strcpy(data, (copy.data));
        len = copy.length();
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
    const int size2 = appendString.length();

    const int s = (size1 + size2) - 1; // plus 1 to account for null char
    char newString[s];

    for (int i = 0; i < size1; i++)
    {
        newString[i] = data[i];
    }
    int j = 0;
    for (int i = size1; i < s; i++)
    {
        newString[i] = appendString.data[j];
        j++;
    }

    int index = 0;
    do{
        std::cout << newString[index];
        index++;
    }while(newString[index] != '\0');

    DSString newDSString(newString);

    return newDSString;
}

DSString DSString::operator+=(const char) const
{
    return DSString();
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
            returnVal = false;
        }
        i++;
    } while (data[i] != '\0' && rhs.data[i] != '\0');

    return returnVal;
}

bool DSString::operator<(const DSString &rhs) const
{
    bool returnVal = false;
    int i = 0;
    do
    {
        if (data[i] < rhs.data[i])
        {
            returnVal = true;
            break;
        }
        i++;
    } while (data[i] != '\0' && rhs.data[i] != '\0');

    return returnVal;
}

bool DSString::operator!=(const DSString &rhs) const
{

    if (length() != rhs.length())
    {
        return false;
    }

    for (size_t i = 0; i < length(); ++i)
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

    const size_t newSize = numChars + 1;
    char newString[newSize];
    for (size_t i = 0; i <= newSize; i++)
    {
        newString[i] = data[i + start];
    }

    DSString newDSString(newString);
    return newDSString;
}

DSString DSString::toLower() const // Returns a new string object with all characters in lowercase
{
    char newString[len];
    for (size_t i = 0; i < len; i++)
    {
        if (data[i] <= 90 && data[i] >= 65)
        {
            newString[i] = data[i] + 32;
        }
        else
        {
            newString[i] = data[i];
        }
    }
    DSString newDSString(newString);
    return newDSString;
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
    output << txt.data;
    return output;
}
