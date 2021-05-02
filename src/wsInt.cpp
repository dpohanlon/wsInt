#include <iostream>

#include "parser/WsStringTransform.h"
#include "parser/Parser.h"
#include "vm/wsVM.h"

using namespace std;

int main(int argc, char const *argv[])
{
    if (argc != 2) {
        cout << "usage: wsInt <file>" << endl;
        return 1;
    }

    ifstream wsFile;
    wsFile.open(argv[1]);

    WsStringTransform wsStr(wsFile);

    wsFile.close();

    string tokenString = wsStr.getTransformedString();
    cout << tokenString << endl;

    Parser parser(tokenString);
    cout << endl;
    cout << parser.getProg() << endl;

    wsVM vm(parser.getProg());
    vm.runProg();

    return 0;
}
