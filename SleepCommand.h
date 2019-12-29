
#ifndef EX3_SLEEPCOMMAND_H
#define EX3_SLEEPCOMMAND_H


#include "Command.h"
#include <string>
#include <iostream>

class SleepCommand : public Command {
private:
    int timeToSleep = 0;
public:
    SleepCommand(std::string timeToSleep);
    void execute(int* index) override;
};


#endif //EX3_SLEEPCOMMAND_H