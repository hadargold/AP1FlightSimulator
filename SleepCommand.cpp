#include <string>
#include <chrono>
#include <thread>
#include "SleepCommand.h"
#include "Interpreter.h"
#include "VariableManager.h"
#include "ConnectCommand.h"


SleepCommand :: SleepCommand(string strTime) {
    // change the timeToSleep to int
    auto *stringToInterpretForPort= new Interpreter();
    auto *variableManager = new VariableManager();
    stringToInterpretForPort->setVariablesByMapOfVars(variableManager->getVarList());
    Expression *expressionToPrint = stringToInterpretForPort->interpret(strTime);
    int intTime = (int) expressionToPrint->calculate();
    this->timeToSleep = intTime;
}

void SleepCommand::execute(int* index)
{
    //from chrono
    this_thread::sleep_for(std::chrono::milliseconds((int) timeToSleep));
    *index += 2;
}