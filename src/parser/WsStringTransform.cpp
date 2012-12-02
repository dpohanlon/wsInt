#include "WsStringTransform.h"

WsStringTransform::WsStringTransform(std::ifstream * wsFile)
{

    char dumChar;
    std::ostringstream wsStrStr;

    if (wsFile->is_open()){
        while (*wsFile >> std::noskipws >> dumChar){
            wsStrStr << dumChar;
        }
        this->wsString = stringTransform(wsStrStr.str());
    }
}

std::string WsStringTransform::stringTransform(std::string wsString)
{
    std::string tString;
    std::string::iterator si;

    for (si = wsString.begin(); si != wsString.end(); ++si){
        tString.push_back(charTransform(*si));
    }
    return tString;
}

char WsStringTransform::charTransform(char wsChar)
{
    if (wsChar == ' '){
        return 'A';
    }
    else if (wsChar == '\t'){
        return 'B';
    }
    else if (wsChar == '\n'){
        return 'C';
    }
    else{
        return wsChar; // Throw up parse exception - not ws
    }
}
