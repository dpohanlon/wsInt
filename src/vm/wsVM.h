#ifndef WSVM_H
#define WSVM_H

#include <string>
#include <vector>
#include <map>
#include <stack>
#include <sstream>
#include <iostream>

#include "BinaryUtils.h"

class wsVM
{
public:

    wsVM(std::string progIn);
    void runProg(void);

private:

    typedef void (wsVM::*opPtr)(void);
    typedef std::map<std::string, opPtr> opMap;

    int pc;
    int sp;

    std::vector<std::string> prog;
    std::stack<int> stack;

    std::vector<std::string> vectorProg(std:: string progIn);
    std::string getOp(std::string ins);
    std::string getData(std::string ins);

    opMap ops;

    void sPush(std::string data);
    int sPop(void);

    void push(void);
    void dup(void);
    void swap(void);
    void discard(void);
    void plus(void);
    void minus(void);
    void times(void);
    void divide(void);
    void modulo(void);
    void store(void);
    void retrieve(void);
    void mark(void);
    void call(void);
    void jump(void);
    void jumpZ(void);
    void jumpN(void);
    void ret(void);
    void end(void);
    void writeChar(void);
    void writeInt(void);
    void readChar(void);
    void readInt(void);

};

#endif
