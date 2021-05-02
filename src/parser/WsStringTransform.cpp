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
        char wsChar = *si;
        if (wsChar == ' '){
            tWs.push_back('A');
        }
        else if (wsChar == '\t'){
            tWs.push_back('B');
        }
        else if (wsChar == '\n'){
            tWs.push_back('C');
        }
    }
    return tWs;
}
