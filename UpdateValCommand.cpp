//
// Created by yuval on 12/26/19.
//

#include "UpdateValCommand.h"
#include "SymbolTable.h"
#include "Interpreter.h"

void UpdateValCommand :: execute(int* index) {
    // change the value to double by shunting yard
    auto *stringToInterpretForUpdateVal = new Interpreter();
    auto *symbolTable = new SymbolTable();
    unordered_map<string,Variable*> nameOfVarToVariableMap = symbolTable->getMap();
    stringToInterpretForUpdateVal->setVariablesByMapOfVars(nameOfVarToVariableMap);
    Expression *valueToUpdate = stringToInterpretForUpdateVal->interpret(value);

    // add the value and the name to a queue in order to sent it to the simulator.
    valuesToSendToTheSim.push(make_pair(this->varName, valueToUpdate->calculate()));
    *index += 2;
}
