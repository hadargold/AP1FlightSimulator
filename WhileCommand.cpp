//
// Created by hadar on 12/27/19.
//

#include "WhileCommand.h"

WhileCommand::WhileCommand(vector <string> lexer, int i, SymbolTable *symbolTable, CommandsManager* cmdManager) {
    this->iter = i;
    this->lex = lexer; // check * !!!!!
    this->symbolTable = symbolTable;
    this->commandsManager = cmdManager;
}

void WhileCommand::execute(int *index) { // should get the lex
    (*index) += 1; // first one was "while"
    vector<string> conditionVec, commandsVec;
    while (lex[*index] != "{") {
        conditionVec.push_back(lex[*index]);
        (*index)++;
    }

    // now we have all the condition
    int breaks = 1;
    (*index)++;
    //it++;
    while (breaks != 0) { //!(lex[*index] == "}" &&
        if (lex[*index] == "{")
            breaks++;
        if (lex[*index] == "}")
            breaks--;
        if (breaks != 0)
            commandsVec.push_back(lex[*index]);
        (*index) += 1;
    }

    while(getResult(conditionVec))
    {
        for(auto i = 0; i< commandsVec.size(); ++i)
        {
//            if(!getResult(conditionVec))
//
//            cout << "in while i is: " << i << " " << commandsVec[i] << endl;
            // if this is command - execute it
            if (commandsManager->isCommand(commandsVec[i]))
            {
                Command *c = commandsManager -> commandsFactory(commandsVec, i);
                c->execute(&i);
            }
                // if the command is "=" so the i is on the var name and the next index is the "="
            else if (commandsVec[i+1] == "=") {
                Command *c = new UpdateValCommand(commandsVec[i], commandsVec[i+2], commandsManager->getSymbolTable(),
              commandsManager->getValToSend());
                c->execute(&i);
            }
        }
    }
    (*index) -=1;

}

bool WhileCommand::getResult(vector<string> conditionVec){
    // check the condition
    //CommandsManager *cmdMgr = new CommandsManager();
    //vector <Command*> cmdVec;
//    Condition *cond = new Condition(conditionVec);
//    cond->execute(index);
    bool result = false;
    if(conditionVec.size() == 1)
    {
        //checkkkkkkkkkkkkkkkkkkkkkkk
        result = (conditionVec[0] == "0") ? true : false;
        //*index += 1;
    }
    else {
        int i = 0;
        int conditionLocation;
        string left = conditionVec[0];
        string right = conditionVec[2];
        Expression *sideA, *sideB;

        Interpreter *stringToInterpretForConditionLeft = new Interpreter();
        //SymbolTable *symbolTable = new SymbolTable();
        unordered_map<string, Variable *> nameOfVarToVariableMap = this->symbolTable->getMap();
        stringToInterpretForConditionLeft->setVariablesByMapOfVars(nameOfVarToVariableMap);
        Expression *expressionLeft = stringToInterpretForConditionLeft->interpret(left);

        Interpreter *stringToInterpretForConditionRight = new Interpreter();
        unordered_map<string, Variable *> nameOfVarToVariableMapR = this->symbolTable->getMap();
        stringToInterpretForConditionLeft->setVariablesByMapOfVars(nameOfVarToVariableMap);
        Expression *expressionRight = stringToInterpretForConditionLeft->interpret(right);

        if(conditionVec[1] == ">")
            result = expressionLeft->calculate() > expressionRight->calculate() ? true : false;
        if(conditionVec[1] == "<")
            result = expressionLeft->calculate() < expressionRight->calculate() ? true : false;
        if(conditionVec[1] == "!=")
            result = expressionLeft->calculate() != expressionRight->calculate() ? true : false;
        if(conditionVec[1] == "==")
            result = expressionLeft->calculate() == expressionRight->calculate() ? true : false;
        if(conditionVec[1] == "<=")
            result = expressionLeft->calculate() <= expressionRight->calculate() ? true : false;
        if(conditionVec[1] == ">=")
            result = expressionLeft->calculate() >= expressionRight->calculate() ? true : false;

        //*index += 3;
    }
    return result;
}

