#include <iostream>
#include <chrono>
#include <thread>
#include "SleepCommand.h"


void SleepCommand::execute(int& index)
{
    // ask hadar what is getNumericExpression.
    //check time od sleep
    double timeOfSleep = 0;
    Expression* varValue = this->parser->getNumericExpression(it);
    if(varValue != NULL) {
        timeOfSleep = varValue->calculate();
    }

    //from chrono
    this_thread::sleep_for(std::chrono::milliseconds((int) timeOfSleep));
    *index += 2;
}