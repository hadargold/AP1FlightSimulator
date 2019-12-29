//
// Created by yuval on 12/22/19.
//

#include <iostream>
#include <string>
#include "PrintCommand.h"
#include "VariableManager.h"
#include "Interpreter.h"
#include "SymbolTable.h"

void PrintCommand:: execute(int* index) {
    // if the toPrint is string- print it (without "" )
    if (toPrint[0] == '"' && toPrint[toPrint.length() - 1] == '"') {
        string stringToPrint = toPrint.substr(1, toPrint.length() - 2);
        cout << stringToPrint << endl;
    } else {
        Interpreter *stringToInterpretForPrinting = new Interpreter();
        SymbolTable *symbolTable = new SymbolTable();
        unordered_map<string,Variable*> nameOfVarToVariableMap = symbolTable->getMap();
        stringToInterpretForPrinting->setVariablesByMapOfVars(nameOfVarToVariableMap);
        Expression *expressionToPrint = stringToInterpretForPrinting->interpret(toPrint);
        cout << expressionToPrint->calculate() << endl;
    }
    *index += 2;
}

