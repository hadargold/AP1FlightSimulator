
#ifndef EX3_SLEEPCOMMAND_H
#define EX3_SLEEPCOMMAND_H


#include "Command.h"
#include "Expression.h"
#include "Parser.h"
#include "unistd.h"
using namespace std;

class SleepCommand : public Command {
    string timeToSleep;

public:
    SleepCommand(string timeToSleep) {
        this->timeToSleep = timeToSleep;
    }
    void execute(int index);
};


#endif //EX3_SLEEPCOMMAND_H