#include <iostream>
#include <string>
#include <sstream>
#include <map>

#include "../Parser/Parser.h"

using namespace std;

void test(const map<string, string> * ops);

int main(int argc, char const *argv[])
{
    map<string, string> ops;

    ops.insert(make_pair("AA", "Push "));
    ops.insert(make_pair("ACA", "Dup"));
    ops.insert(make_pair("ACB", "Swap"));
    ops.insert(make_pair("ACC", "Discard"));

    ops.insert(make_pair("BAAA", "Plus"));
    ops.insert(make_pair("BAAB", "Minus"));
    ops.insert(make_pair("BAAC", "Times"));
    ops.insert(make_pair("BABA", "Divide"));
    ops.insert(make_pair("BABB", "Modulo"));

    ops.insert(make_pair("BBA", "Store"));
    ops.insert(make_pair("BBB", "Retrieve"));

    ops.insert(make_pair("CAA", "Mark "));
    ops.insert(make_pair("CAB", "Call "));
    ops.insert(make_pair("CAC", "Jump "));
    ops.insert(make_pair("CBA", "JumpZ "));
    ops.insert(make_pair("CBB", "JumpN "));
    ops.insert(make_pair("CBC", "Return"));
    ops.insert(make_pair("CCC", "End"));

    ops.insert(make_pair("BCAA", "WriteChar"));
    ops.insert(make_pair("BCAB", "WriteInt"));
    ops.insert(make_pair("BCBA", "ReadChar"));
    ops.insert(make_pair("BCBB", "ReadInt"));

    test(&ops);

    return 0;
}

void test(const map<string, string> * ops)
{
    int i = 0;
    int passed = 0;
    string out;

    map<string, string>::const_iterator si;

    for (si = ops->begin(); si != ops->end(); ++si){
        i++;

        Parser p(si->first);

        if ((out = p.getProg()) == si->second + "\n"){
            cout << "Passed test " << i << "." << endl;
            passed++;
        }
        else {
            cout << "Failed test " << i << "." << endl;
            cout << "-----Expected: " << si->second << endl;
            cout << "-----Returned: " << out << endl;
        }
    }

    cout << endl << passed << "/" << i << " tests passed." << endl;

    return;
}
