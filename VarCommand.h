//
// Created by yuval on 12/26/19.
//

#ifndef EX3_VARCOMMAND_H
#define EX3_VARCOMMAND_H

#include "SymbolTable.h"
using namespace std;

class VarCommand :public Command {
private:
    string nameAccordingToClient;
    string direction;
    string nameAccordingToSim;
public:
    VarCommand(string nameAccordingToClient, string direction, string nameAccordingToSim) {
        this->nameAccordingToClient = nameAccordingToClient;
        this->direction = direction;
        this->nameAccordingToSim = nameAccordingToSim;
    }
    void execute(int& index, SymbolTable symbolTable);
};


#endif //EX3_VARCOMMAND_H