#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <iostream>

// For convenience, three input characters 
//        A => space, B => tab, C => either of CR/LF

// Numbers are binary (A=0, B=1, C=terminator)
// Strings are sequences of binary characters, terminated by C.

// We have:

// * Stack instructions (Preceded by A)
//      Push (Integer)    A
//      Dup           CA
//      Swap          CB
//      Discard       CC

// * Arithmetic (Preceded by BA)
//      Plus          AA
//      Minus         AB
//      Times         AC
//      Divide        BA
//      Modulo        BB

// * Heap access (Preceded by BB)
//      Store         A
//      Retrieve      B

// * Control     (Preceded by C)
//      Label String  AA
//      Call Label    AB
//      Jump Label    AC
//      If Zero Label BA
//      If Neg Label  BB
//      Return        BC
//      End           CC

// * IO instructions (Preceded by BC)
//      OutputChar    AA
//      OutputNum     AB
//      ReadChar      BA
//      ReadNum       BB

class Parser
{
public:

    Parser(std::string tokens);
    std::string getProg() { return prog; }

private:

    std::string tok;
    std::string prog;
    unsigned int tkp; // token pointer

    void parse(void);
    void parseIMP(void);

    void stackIMP(void);
    void arithIMP(void);
    void heapIMP(void);
    void ioIMP(void);
    void flowIMP(void);

    void parseNumber(void);
    void parseLabel(void);

    void push(char c);
    void push(std::string s);

    bool accept(char c); 
    void error(std::string error, int itok);

};

#endif
