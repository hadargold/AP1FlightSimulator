
#ifndef EX3_SLEEPCOMMAND_H
#define EX3_SLEEPCOMMAND_H


#include "Command.h"
#include <string>
#include <iostream>
#include "SymbolTable.h"

class SleepCommand : public Command {
private:
    SymbolTable* symbolTable;
    int timeToSleep = 0;
public:
    SleepCommand(std::string timeToSleep, SymbolTable* symbolTable1);
    void execute(int* index) override;
};


#endif //EX3_SLEEPCOMMAND_H