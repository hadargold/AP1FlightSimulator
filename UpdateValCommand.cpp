//
// Created by yuval on 12/26/19.
//

#include "UpdateValCommand.h"
#include "SymbolTable.h"

void DefineValCommand :: execute(int& index) {
    // change the value to double by shunting yard
    Interpreter *stringToInterpretForUpdateVal = new Interpreter();
    SymbolTable symbolTable = new SymbolTable();
    map<string,Variable> nameOfVarToVariableMap = symbolTable.getMap();
    stringToInterpretForPrinting.setVariablesByMapOfVars(nameOfVarToVariableMap);
    Expression *expressionToUpdate = stringToInterpretForUpdateVal->interpret(value);

    SymbolTable symbolTable  = new SymbolTable();
    symbolTable.setValueByNameByClinet(this->varName, expressionToPrint->calculate());
    *index += 2;
}
