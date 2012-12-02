#include "wsVM.h"

wsVM::wsVM(std::string progIn) : pc(0), sp(0)
{
    this->prog = vectorProg(progIn);

    ops.insert(std::make_pair("Push", & wsVM::push));
    ops.insert(std::make_pair("Dup", & wsVM::dup));
    ops.insert(std::make_pair("Swap", & wsVM::swap));
    ops.insert(std::make_pair("Discard", & wsVM::discard));

    ops.insert(std::make_pair("Plus", & wsVM::plus));
    ops.insert(std::make_pair("Minus", & wsVM::minus));
    ops.insert(std::make_pair("Times", & wsVM::times));
    ops.insert(std::make_pair("Divide", & wsVM::divide));
    ops.insert(std::make_pair("Modulo", & wsVM::modulo));

    ops.insert(std::make_pair("Store", & wsVM::store));
    ops.insert(std::make_pair("Retrieve", & wsVM::retrieve));

    ops.insert(std::make_pair("Mark", & wsVM::mark));
    ops.insert(std::make_pair("Call", & wsVM::call));
    ops.insert(std::make_pair("Jump", & wsVM::jump));
    ops.insert(std::make_pair("JumpZ", & wsVM::jumpZ));
    ops.insert(std::make_pair("JumpN", & wsVM::jumpN));
    ops.insert(std::make_pair("Return", & wsVM::ret));
    ops.insert(std::make_pair("End", & wsVM::end));

    ops.insert(std::make_pair("WriteChar", & wsVM::writeChar));
    ops.insert(std::make_pair("WriteInt", & wsVM::writeInt));
    ops.insert(std::make_pair("ReadChar", & wsVM::readChar));
    ops.insert(std::make_pair("ReadInt", & wsVM::readInt));

}

std::vector<std::string> wsVM::vectorProg(std::string progIn)
{
    std::vector<std::string> vProg;

    std::istringstream iss(progIn);
    std::string ins;

    while (getline(iss, ins, '\n')){
        vProg.push_back(ins);
    }

    return vProg;
}


std::string wsVM::getOp(std::string ins)
{
    std::string op;
    std::istringstream iss(ins);
    getline(iss, op, ' ');

    return op;
}

std::string wsVM::getData(std::string ins)
{
    std::string data;
    std::istringstream iss(ins);
    getline(iss, data, ' ');
    getline(iss, data, ' ');

    return data;
}

void wsVM::runProg(void)
{
    std::vector<std::string>::iterator is;
    opMap::iterator io;
    opPtr op;

    for (is = prog.begin(); is != prog.end(); ++is){
        io = ops.find(getOp(*is));

        if (io != ops.end()){
            op = io->second;
            (this->*op)();
        }
        pc++; // No idea how to handle this!
    }
}

void wsVM::sPush(std::string data) // take int for symmetry?
{
    stack.push(BinaryUtils::wsNumInt(data));
}

int wsVM::sPop(void)
{
    int d = 0;

    d = stack.top();
    stack.pop();

    return d;
}

void wsVM::push(void)
{
    sPush(getData(prog[pc]));
}

void wsVM::dup(void)
{

}
void wsVM::swap(void)
{

}

void wsVM::discard(void)
{

}

void wsVM::plus(void)
{

}

void wsVM::minus(void)
{

}

void wsVM::times(void)
{

}

void wsVM::divide(void)
{

}

void wsVM::modulo(void)
{

}

void wsVM::store(void)
{

}

void wsVM::retrieve(void)
{

}

void wsVM::mark(void)
{

}

void wsVM::call(void)
{

}

void wsVM::jump(void)
{

}

void wsVM::jumpZ(void)
{

}

void wsVM::jumpN(void)
{

}

void wsVM::ret(void)
{

}

void wsVM::end(void)
{

}

void wsVM::writeChar(void)
{

}

void wsVM::writeInt(void)
{

}

void wsVM::readChar(void)
{

}

void wsVM::readInt(void)
{

}
