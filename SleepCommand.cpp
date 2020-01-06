//
// Created by hadar on 12/22/19.
//
#include <string>
#include <chrono>
#include <thread>
#include "SleepCommand.h"
#include "Interpreter.h"
#include "ConnectCommand.h"
#include "SymbolTable.h"

// construcotr
SleepCommand :: SleepCommand(string strTime, SymbolTable* symbolTable1) {
    // change the timeToSleep to int
    this->symbolTable = symbolTable1;
    auto *stringToInterpretForPort= new Interpreter();
    stringToInterpretForPort->setVariablesByMapOfVars(this->symbolTable->getMap());
    Expression *expressionToPrint = stringToInterpretForPort->interpret(strTime);
    int intTime = (int) expressionToPrint->calculate();
    this->timeToSleep = intTime;
}

// execute the sleep
void SleepCommand::execute(int* index)
{
    //from chrono
    this_thread::sleep_for(std::chrono::milliseconds((int) timeToSleep));
    *index += 3;
}