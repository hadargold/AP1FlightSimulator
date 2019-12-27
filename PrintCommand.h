//
// Created by hadar on 12/19/19.
//
//
#ifndef EX3_PRINTCOMMAND_H
#define EX3_PRINTCOMMAND_H

#include "PrintCommand.h"
#include <string>
#include "Expression.h"
#include "Command.h"

using namespace std;

class PrintCommand :public Command {
private:
    string toPrint;
public:
    explicit PrintCommand(string sPrint) { this->toPrint = sPrint; }
    void execute(int& index);
};


#endif //EX3_PRINTCOMMAND_H
