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

VarCommand :: VarCommand(string nameAccordingToClient, string direction, string nameAccordingToSim) {
    enum  directions {RIGHT, LEFT};
    this->nameAccordingToClient = nameAccordingToClient;
    this->nameAccordingToSim = nameAccordingToSim;
    if (direction.compare("->") == 0) {
        this->direction = RIGHT;
    } else if (direction.compare("<-") == 0) {
        this->direction = LEFT;
    }
}

void VarCommand:: execute(int* index) {
    SymbolTable *symbolTable  = new SymbolTable();
    unordered_map<string,Variable*> nameOfVarToVariableMap = symbolTable->getMap();
    // create the Variable
    const double defaultVal = 0;
    Variable *newVar = new Variable(nameAccordingToSim, defaultVal, direction);
    nameOfVarToVariableMap.insert(pair<string,Variable*>(nameAccordingToClient,newVar));
    *index += 3;
}