//
// Created by yuval on 12/26/19.
//

#include "UpdateValCommand.h"
#include "SymbolTable.h"
#include "Interpreter.h"
#include <mutex>

void UpdateValCommand :: execute(int* index) {
    // change the value to double by shunting yard
    auto *stringToInterpretForUpdateVal = new Interpreter();
    unordered_map<string,Variable*> nameOfVarToVariableMap = this->symbolTable->getMap();
    stringToInterpretForUpdateVal->setVariablesByMapOfVars(nameOfVarToVariableMap);
    Expression *valueToUpdate = stringToInterpretForUpdateVal->interpret(value);
    // update the value in the symbol table
    unordered_map<string,Variable*>::iterator it = nameOfVarToVariableMap.find(this->varName);
    if (it != nameOfVarToVariableMap.end()) {
        mutex mutex;
        mutex.try_lock();
        it->second->setValue(valueToUpdate->calculate());
        if (it->second->getDirection() == 0) {
            // add the value and the name to a queue in order to sent it to the simulator if the direction is right
            valuesToSendToTheSim.push(make_pair(this->varName, valueToUpdate->calculate()));
        }
        mutex.unlock();
    }
    *index += 2;
}
