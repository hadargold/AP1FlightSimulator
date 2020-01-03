//
// Created by yuval on 12/26/19.
//

#ifndef EX3_VARCOMMAND_H
#define EX3_VARCOMMAND_H

#include "SymbolTable.h"
#include "Command.h"

using namespace std;

class VarCommand :public Command {
private:
    SymbolTable *symbolTable;
    string nameAccordingToClient;
    int direction;
    string nameAccordingToSim;
public:
    VarCommand(string nameAccordingToClient, string direction, string nameAccordingToSim, SymbolTable* symbolTable);
    void execute(int* index);
};


#endif //EX3_VARCOMMAND_H