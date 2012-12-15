#include "wsVM.h"

wsVM::wsVM(std::string progIn) : pc(0), rp(0)
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

    fillMarks();

    while(pc < prog.size()){
        std::cout << "PC(" << pc << ")" << std::endl;
        io = ops.find(getOp(prog[pc]));
        if (io != ops.end()){
            op = io->second;
            (this->*op)();
        }
        pc++;
    }
}

void wsVM::fillMarks(void)
{
    std::vector<std::string>::iterator is;
    unsigned int p = 0;

    for(is = prog.begin(); is != prog.end(); ++is){
        if (getOp(*is) == "Mark"){
            marks.insert(std::make_pair(getData(*is), p));
        }
        p++;
    }
}

void wsVM::sPush(std::string data) // take int for symmetry?
{
    stack.push(BinaryUtils::wsNumInt(data));
}

int wsVM::sPop(void)
{
    int d = 0;

    if (stack.size() > 0){
        d = stack.top();
        stack.pop();
    }

    return d;
}

void wsVM::push(void)
{
    sPush(getData(prog[pc]));
}

void wsVM::dup(void)
{
    stack.push(stack.top());
}
void wsVM::swap(void)
{
    int temp1 = sPop();
    int temp2 = sPop();

    stack.push(temp1);
    stack.push(temp2);
}

void wsVM::discard(void)
{
    stack.pop();
}

void wsVM::plus(void)
{
    int lhs = sPop();
    int rhs = sPop();
    stack.push(lhs + rhs);
}

void wsVM::minus(void)
{
    int lhs = sPop();
    int rhs = sPop();
    stack.push(lhs - rhs);
}

void wsVM::times(void)
{
    int lhs = sPop();
    int rhs = sPop();
    stack.push(rhs * lhs);
}

void wsVM::divide(void)
{
    int lhs = sPop();
    int rhs = sPop();
    stack.push(lhs / rhs);
}

void wsVM::modulo(void)
{
    int lhs = sPop();
    int rhs = sPop();
    stack.push(lhs % rhs);
}

void wsVM::store(void)
{
    int addr = sPop();
    heap.insert(std::make_pair(addr, sPop()));
}

void wsVM::retrieve(void)
{
    std::map<int, int>::iterator im;
    im = heap.find(sPop());
    if (im != heap.end()) stack.push(im->second);
    else std::cout << "ERROR: Entry not found in heap!" << std::endl;
}

void wsVM::mark(void)
{
    // Does nothing - marks should already be populated by first pass
    //marks.insert(std::make_pair(getData(prog[pc]), pc));
}

void wsVM::call(void)
{
    rp = pc;
    jump();
}

void wsVM::jump(void)
{
    std::map<std::string, int>::iterator p;
    p = marks.find(getData(prog[pc]));
    if (p != marks.end()) this->pc = p->second;
    else std::cout << "ERROR: Mark point not found!" << std::endl;
}

void wsVM::jumpZ(void)
{
    if (sPop() == 0){
        jump();
    }
}

void wsVM::jumpN(void)
{
    if (sPop() < 0){
        jump();
    }
}

void wsVM::ret(void)
{
    pc = rp;
}

void wsVM::end(void)
{

}

void wsVM::writeChar(void)
{
    printf("%c", char(sPop()));
}

void wsVM::writeInt(void)
{
    printf("%i", sPop());
}

void wsVM::readChar(void)
{
    stack.push(getchar());
}

void wsVM::readInt(void)
{
    stack.push(getchar());
}
