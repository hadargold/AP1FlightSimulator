//
// Created by yuval on 12/26/19.
//

#include "VarCommand.h"
#include <iostream>
#include <map>
#include "ex1.h"
#include <string>
#include <chrono>
#include <thread>
#include "SleepCommand.h"
#include "Interpreter.h"
#include "VariableManager.h"
#include "ConnectCommand.h"
#include "Command.h"



using namespace std;

VarCommand :: VarCommand(string nameAccordingToClient, string direction, string nameAccordingToSim,
        SymbolTable* symbolTable) {
    enum  directions {RIGHT, LEFT};
    //nameAccordingToSim = nameAccordingToSim.substr(1, nameAccordingToSim.length()-2);
    this->nameAccordingToClient = nameAccordingToClient;
    this->nameAccordingToSim = nameAccordingToSim;
    if (direction.compare("->") == 0) {
        this->direction = RIGHT;
    } else if (direction.compare("<-") == 0) {
        this->direction = LEFT;
    }
    this->symbolTable = symbolTable;
}

void VarCommand:: execute(int* index) {
    // create the Variable
    const double defaultVal = 0;
    unordered_map<string,Variable*> &nameOfVarToVariableMap = this->symbolTable->getMap();
    Variable *newVar = new Variable(nameAccordingToSim, defaultVal, direction);
    nameOfVarToVariableMap.insert(pair<string,Variable*>(nameAccordingToClient,newVar));
    *index += 6;
}
