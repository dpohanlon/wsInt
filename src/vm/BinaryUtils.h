#ifndef BINARYUTILS_H
#define BINARYUTILS_H

#include <iostream>
#include <string>
#include <vector>
#include <cassert>

namespace BinaryUtils
{

int wsNumInt(std::string b);
std::string wsLabelString(std::string bStr);

int btoi(const std::string & bStr);
std::string bCharsStr(const std::vector<std::string> & bChars);

}

#endif
