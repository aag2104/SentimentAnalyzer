#include "DSString.h"

DSString::DSString() // default constructor - called when DSString object is made without args
{
    data = new char[1]; // sets data = to char array with size 1, allocates memory on heap
    data[0] = '\0';     // sets index 0 to nullchar
    len = 0;            // length, size 0 -> empty DSString
}
DSString::DSString(const char *txt) // paramaterized constructor - called when DSString object is made WITH args
{
    len = 0;                 // start with length of 0
    while (txt[len] != '\0') // until hitting end of txt, increment len by 1 (counter)
    {
        len++; // gets length and iterates through while loop
    }

    data = new char[len + 1]; // len + 1 because [size] != last index, but last index+1

    for (size_t i = 0; i < len; i++) // iterate through data
    {
        data[i] = txt[i]; // store txt values in data
    }
    data[len] = '\0'; // set last data index to nullchar
}

DSString::DSString(const DSString &copy_char) // copy constructor
{
    const int end = copy_char.len;      // set variable "end" to length of copy_char
    data = new char[copy_char.len + 1]; // len + 1 because [size] != last index, but last index+1

    for (int i = 0; i < end; i++) // iterate through length of copy_char/data
    {
        data[i] = copy_char.data[i]; // copy over copy_char values into data var
    }
    len = copy_char.len; // set data's length to length of copy_char
    data[len] = '\0';    // set last data index to nullchar
}

DSString::~DSString() // destructor
{
    delete[] data; // deletes pointer "data"
}

DSString &DSString::operator=(const DSString &copy) // copy assignment
{
    if (data != copy.data) // is data and copy.data aren't already equal...
    {
        delete[] data;                   // delete whatever is current held in data (we do not need it anymore)
        data = new char[copy.len + 1];   // len + 1 because [size] != last index, but last index+1
        len = copy.len;                  // set data's len to copy's len
        for (size_t i = 0; i < len; i++) // iterate through length of copy/data
        {
            data[i] = copy.data[i]; // copy over copy's data values into LHS data var
        }
        data[len] = '\0'; // set last data index to nullchar
    }

    return *this;
}

size_t DSString::length() const
{
    return len; // returns length of data, var "len"
}

char &DSString::operator[](size_t index) // returns a reference to the character at the given index
{
    return data[index];
}

DSString DSString::operator+(const DSString &appendString) const // Overloaded operator+ which appends the string in the argument to this string
{
    const int size1 = len;              // size 1 = length of LHS data
    const int size2 = appendString.len; // size 2 = length of RHS data (aka appendString)

    const int s = (size1 + size2);     // add sizes to get combined size, "s"
    char *newString = new char[s + 1]; // add 1 only in creation, to account for nullchar

    for (int i = 0; i < size1; i++) // iterate from 0-size1
    {
        newString[i] = data[i]; // copy data values into newString
    }
    int j = 0;                      // keeps track of appendString index values
    for (int i = size1; i < s; i++) // iterate from size1-s
    {
        newString[i] = appendString.data[j]; // copy over data from appendString to newString
        j++;                                 // increment appendString index as loop iterates
    }

    newString[s] = '\0';             // store a nullChar at the end of newString
    DSString newDSString(newString); // convert newString into a DSString
    delete[] newString;              // delete newString because it is no longer being used, value currently being held in DSString ^

    return newDSString; // return new DSString
}

bool DSString::operator==(const DSString &rhs) const // overloads == operator
{
    bool returnVal = true; // intializes returnVal
    int i = 0;             // will keep track fo data index in do-while loop
    do
    {
        if (data[i] == rhs.data[i]) // if data and RHS characters are equal...
        {
            returnVal = true; // keep returnVal at true
        }
        else
        {
            return false; // if you hit a char where they are not equal, teh DSString themselves are automatically classified as "not equal", so return false
        }
        i++;                                          // increment index
    } while (data[i] != '\0' && rhs.data[i] != '\0'); // continue until we reach the end of LHS or RHS DSString

    return returnVal; // returns val (true/false)
}

bool DSString::operator<(const DSString &rhs) const // overloads < operator
{
    int length;        // create int variable "length"
    if (len > rhs.len) // store the size of the larger DSString "length"
    {
        length = len; // when data.len > rhs.len
    }
    else
    {
        length = rhs.len; // when data.len < rhs.len
    }
    for (int i = 0; i < length; i++) // iterate though length of longer DSString (aka "length")
    {
        if (data[i] == '\0') // if we reach the end of data without returning false, return true
        {
            return true;
        }
        else if (rhs.data[i] == '\0') // if we reach the end of RHS first, that means RHS is shorter, so return false
        {
            return false;
        }

        if (data[i] > rhs.data[i]) // if we get to a char where data is greater... return false
        {
            return false;
        }
        if (data[i] < rhs.data[i]) // if we get to a char where RHS is greater... return true
        {
            return true;
        }
    }

    return false; // reaches only if data and RHS are exactly the same, therefore, return false
}

bool DSString::operator!=(const DSString &rhs) const // overloads != operator
{
    if (len != rhs.len) // if the lengths are not equal, we know the DSStrings are not equal
    {
        return false;
    }

    for (size_t i = 0; i < len; ++i) //^else, iterate through and check characters
    {
        if (data[i] != rhs.data[i]) // if coming across a difference.. return false
        {
            return false;
        }
    }
    return true;
}

DSString DSString::substring(size_t start, size_t numChars) const // returns only a portion of a DSString
{
    const size_t newSize = numChars;         // set newSize to number of chars in substring (numChars)
    char *newString = new char[newSize + 1]; // create a new char* with newSize + 1
    for (size_t i = 0; i <= newSize; i++)    // iterate through size of newString
    {
        newString[i] = data[i + start]; // store values of data at [i + start] (start = first index value of substring) into newString, starting at index 0
    }

    newString[newSize] = '\0';       // make sure last index of newString holds a nullChar
    DSString newDSString(newString); // store char* in "newDSString" DSString (conversion)
    delete[] newString;              // delete contents of newString because we no longer need it
    return newDSString;              // return new DSString
}

DSString DSString::toLower() // returns a new string object with all characters in lowercase
{
    for (size_t i = 0; i < len; i++) // iterate through data
    {
        if (data[i] <= 90 && data[i] >= 65) // if data falls between A-Z...
        {
            data[i] = data[i] + 32; // convert to lowercase
        }
    }
    return *this;
}

char *DSString::c_str() const // returns current data value
{
    return data;
}

char *DSString::getData() const // returns current data value
{
    return data;
}

std::ostream &operator<<(std::ostream &output, const DSString &txt) // overloaded <<
{
    output << txt.getData(); // if using << with DSString obj -> print data associated with that obj
    return output;
}
