#include "BinaryUtils.h"

int BinaryUtils::wsNumInt(std::string bStr)
{
    int sign = 0;

    // Strip 'sign' bit -> pass tail to btoi
    if(bStr[0] == '0') sign = 1;
    else if (bStr[0] == '1') sign = -1;

    std::string tail = bStr.substr(1, bStr.size());

    return sign * btoi(tail);
}

std::string BinaryUtils::wsLabelString(std::string bStr)
{
    assert((bStr.size() % 8 == 0) && "Must be N 8-bit chars");

    std::string::iterator si;
    std::vector<std::string> bChars(bStr.size() / 8);

    int bits = 0;
    int chars = -1;

    // Fill a vector of binary strings corresponding to 
    // characters
    for (si = bStr.begin(); si != bStr.end(); ++si){
        if (bits % 8 == 0){
            chars++;
        }
        bChars[chars] += *si;
        bits++;
    }

    return bCharsStr(bChars);
}

int BinaryUtils::btoi(const std::string & bStr)
{
    int num = 0;
    int p = 1;

    std::string::const_iterator si;

    for (si = bStr.end() - 1; si >= bStr.begin(); --si){
        if ( *si == '1') num += p;
        p = p << 1; // Bit shift => power of two
    }

    return num;
}

std::string BinaryUtils::bCharsStr(const std::vector<std::string> & bChars)
{
    std::vector<std::string>::const_iterator vi;
    std::string charStr;
    std::string outString;

    // Convert character in binary-string to integer
    // and then to actual character to cat into string
    for(vi = bChars.begin(); vi != bChars.end(); ++vi){
        charStr = *vi;
        outString += char(btoi(charStr));
    }

    return outString;
}