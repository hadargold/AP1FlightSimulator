//
// Created by yuval on 12/19/19.
//

#ifndef EX3_PRINTCOMMAND_H
#define EX3_PRINTCOMMAND_H

#include "PrintCommand.h"
#include <string>
#include "Expression.h"
#include "Command.h"
#include "SymbolTable.h"

using namespace std;

class PrintCommand :public Command {
private:
    SymbolTable *symbolTable;
    string toPrint;
public:
    explicit PrintCommand(string sPrint, SymbolTable *symbolTable) {
        this->toPrint = sPrint;
        this->symbolTable = symbolTable;
    }
    void execute(int* index);
};


#endif //EX3_PRINTCOMMAND_H
