#include <iostream>

#include "Parser/WsStringTransform.h"
#include "Parser/Parser.h"
#include "vm/wsVM.h"

using namespace std;

int main(int argc, char const *argv[])
{
    ifstream wsFile;
    wsFile.open("count.ws");

    WsStringTransform wsStr(&wsFile);

    wsFile.close();

    string tokenString = wsStr.getTransformedString();
    cout << tokenString << endl;

    Parser parser(tokenString);
    cout << endl;
    cout << parser.getProg() << endl;

    wsVM vm(parser.getProg());

    return 0;
}