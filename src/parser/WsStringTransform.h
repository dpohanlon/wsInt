#ifndef WSSTRINGTRANSFORM_H
#define WSSTRINGTRANSFORM_H

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

class WsStringTransform
{
public:
    WsStringTransform(std::ifstream * wsFile);

    std::string getTransformedString(void){ return this->wsString; }

private:
    std::string wsString;

    std::string stringTransform(std::string wsString);

    char charTransform(char wsChar);
};

#endif
