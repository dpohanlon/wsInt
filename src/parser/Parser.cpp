#include "Parser.h"

Parser::Parser(std::string tokens)
{
    this->tok = tokens;
    this->prog = "";
    tkp = 0;
    parse();
}

void Parser::parse(void)
{
    parseIMP();
}
void Parser::parseIMP(void)
{
    if (tkp >= (tok.size())) return;

    if (!accept(tok[tkp])){
        error("IMP: Unexpected char at: ", tkp);
        tkp++;
        return;
    }

    if (tok[tkp] == 'A'){
        tkp++;
        stackIMP();
    }
    else if (tok[tkp] == 'B'){
        if (tok[tkp + 1] == 'A'){
            tkp += 2;
            arithIMP();
        }
        else if (tok[tkp + 1] == 'B'){
            tkp += 2;
            heapIMP();
        }
        else if (tok[tkp + 1] == 'C'){
            tkp += 2;
            ioIMP();
        }
    }
    else if (tok[tkp] == 'C'){
        tkp++;
        flowIMP();
    }
    else {
        error("IMP parse error at: ", tkp);
        tkp++;
        return;
    }
    push("\n");
    parseIMP();
}

void Parser::stackIMP(void)
{
    if (!accept(tok[tkp])){
        error("STACK: Unexpected char at: ", tkp);
        tkp++;
        return;
    }

    if (tok[tkp] == 'A'){
        tkp++;
        push("Push ");
        parseNumber();
    }
    else if (tok[tkp] == 'C'){
        if (tok[tkp + 1] == 'A'){
            tkp += 2;
            push("Dup");
        }
        else if (tok[tkp + 1] == 'B'){
            tkp += 2;
            push("Swap");
        }
        else if (tok[tkp + 1] == 'C'){
            tkp += 2;
            push("Discard");
        }
    }
}

void Parser::arithIMP(void)
{
    if (!accept(tok[tkp])){
        error("ARITH: Unexpected char at: ", tkp);
        tkp++;
        return;
    }

    if (tok[tkp] == 'A'){
        if (tok[tkp + 1] == 'A'){
            tkp += 2;
            push("Plus");
        }
        else if (tok[tkp + 1] == 'B'){
            tkp += 2;
            push("Minus");
        }
        else if (tok[tkp + 1] == 'C'){
            tkp += 2;
            push("Times");
        }
    }
    else if (tok[tkp] == 'B'){
        if (tok[tkp + 1] == 'A'){
            tkp += 2;
            push("Divide");
        }
        else if (tok[tkp + 1] == 'B'){
            tkp += 2;
            push("Modulo");
        }
    }
}

void Parser::heapIMP(void)
{
    if (!accept(tok[tkp])){
        error("HEAP: Unexpected char at: ", tkp);
        tkp++;
        return;
    }

    if (tok[tkp] == 'A'){
        tkp++;
        push("Store");
    }
    else if (tok[tkp] == 'B'){
        tkp++;
        push("Retrieve");
    }
}

void Parser::ioIMP(void)
{
    if (!accept(tok[tkp])){
        error("IO: Unexpected char at: ", tkp);
        tkp++;
        return;
    }

    if (tok[tkp] == 'A'){
        if (tok[tkp + 1] == 'A'){
            tkp += 2;
            push("WriteChar");
        }
        else if (tok[tkp + 1] == 'B'){
            tkp += 2;
            push("WriteInt");
        }
    }
    else if (tok[tkp] == 'B'){
        if (tok[tkp + 1] == 'A'){
            tkp += 2;
            push("ReadChar");
        }
        else if (tok[tkp + 1] == 'B'){
            tkp += 2;
            push("ReadInt");
        }
    }
}

void Parser::flowIMP(void)
{
    if (!accept(tok[tkp])){
        error("FLOW: Unexpected char at: ", tkp);
        tkp++;
        return;
    }

    if (tok[tkp] == 'A'){
        if (tok[tkp + 1] == 'A'){
            tkp += 2;
            push("Mark ");
            parseLabel();
        }
        else if (tok[tkp + 1] == 'B'){
            tkp += 2;
            push("Call ");
            parseLabel();
        }
        else if (tok[tkp + 1] == 'C'){
            tkp += 2;
            push("Jump ");
            parseLabel();
        }
    }
    else if (tok[tkp] == 'B'){
        if (tok[tkp + 1] == 'A'){
            tkp += 2;
            push("JumpZ ");
            parseLabel();
        }
        else if (tok[tkp + 1] == 'B'){
            tkp += 2;
            push("JumpN ");
            parseLabel();
        }
        else if (tok[tkp + 1] == 'C'){
            tkp += 2;
            push("Return");
        }
    }
    else if (tok[tkp] == 'C'){
        if (tok[tkp] == 'C'){
            if (tok[tkp + 1] == 'C'){
                tkp += 2;
                push("End");
            }
        }
    }
}

void Parser::parseLabel(void)
{
    // Does not enforce grammar
    // label = (A|B),{A|B},C;

    parseNumber();
}

void Parser::parseNumber(void)
{
    // Does not enforce grammar
    // number = (A|B),(A|B),{A|B},C;

    if (!accept(tok[tkp])){
        error("NUMBER: Unexpected char at: ", tkp);
        tkp++;
        return;
    }

    if (tok[tkp] == 'A'){
        push('0');
        tkp++;
        parseNumber();
    }
    else if (tok[tkp] == 'B'){
        push('1');
        tkp++;
        parseNumber();
    }
    else if (tok[tkp] == 'C'){ // End of number
        tkp++;
        return;
    }
    else {
        error("Number parse error at: ", tkp);
        tkp++;
        return;
    }
}

void Parser::push(char c)
{
    prog.push_back(c);
}

void Parser::push(std::string s)
{
    std::string::iterator is;

    for (is = s.begin(); is != s.end(); is++){
        prog.push_back(*is);
    }
}

bool Parser::accept(char c)
{
    if (c == 'A' || c == 'B' || c == 'C') return true;
    else return false;
}

void Parser::error(std::string error, int itok)
{
    std::cerr << "ERROR: " << error << itok << ":" << tok[itok - 1] << std::endl;
}
