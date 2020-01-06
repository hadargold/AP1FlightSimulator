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
#include "ConnectCommand.h"
#include "Command.h"



using namespace std;

// constructor
VarCommand :: VarCommand(string nameAccordingToClient, string direction, string nameAccordingToSim,
        SymbolTable* symbolTable) {
    nameAccordingToSim = nameAccordingToSim.substr(5, nameAccordingToSim.length() - 7);
    enum  directions {RIGHT, LEFT, EQUAL};
    this->nameAccordingToClient = nameAccordingToClient;
    this->nameAccordingToSim = nameAccordingToSim;
    if (direction.compare("->") == 0) {
        this->direction = RIGHT;
    } else if (direction.compare("<-") == 0) {
        this->direction = LEFT;
    } else if (direction.compare("=") == 0) {
        this->direction = EQUAL;
    }
    this->symbolTable = symbolTable;
}

// creates the variable and insert them to the symbol table
void VarCommand:: execute(int* index) {
    // create the Variable
    const double defaultVal = 0;
    unordered_map<string,Variable*> &nameOfVarToVariableMap = this->symbolTable->getMap();
    Variable *newVar = new Variable(nameAccordingToSim, defaultVal, direction);
    nameOfVarToVariableMap.insert(pair<string,Variable*>(nameAccordingToClient,newVar));
    *index += 3;
}
