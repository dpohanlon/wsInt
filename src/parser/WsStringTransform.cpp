#include "WsStringTransform.h"

WsStringTransform::WsStringTransform(std::ifstream & wsFile)
{

    char dum;
    std::ostringstream wsStrStr;

    if (wsFile.is_open()){
        while (wsFile >> std::noskipws >> dum){
            wsStrStr << dum;
        }
        this->wsString = stringTransform(wsStrStr.str());
    }
}

std::string WsStringTransform::stringTransform(std::string ws)
{
    std::string tWs;
    std::string::iterator si;

    for (si = ws.begin(); si != ws.end(); ++si){
        tWs.push_back(charTransform(*si));
    }
    return tWs;
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
