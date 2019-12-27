//
// Created by yuval on 12/26/19.
//

#include "VarCommand.h"
#include <iostream>
#include <map>
#include "ex1.h"

using namespace std

void VarCommand ::VarCommand(string nameAccordingToClient, string direction, string nameAccordingToSim) {
    enum  directions {RIGHT, LEFT};
    this->nameAccordingToClient = nameAccordingToClient;
    this->nameAccordingToSim = nameAccordingToSim;
    if (direction.compare("->") == 0) {
        this->direction = RIGHT;
    } else if (direction.compare("<-") == 0) {
        this->direction = LEFT;
    }
}

void VarCommand:: execute(int& index) {
    enum  directions {RIGHT, LEFT};
    SymbolTable symbolTable  = new SymbolTable();
    map<string,Variable> nameOfVarToVariableMap = symbolTable.getMap();
    // create the Variable
    Variable newVar = new Variable(nameAccordingToSim, 0, direction);
    nameOfVarToVariableMap.insert (pair<string,Variable>(nameAccordingToClient,newVar))

    *index += 3;
}