//
// Created by hadar on 12/27/19.
//

#include "IfCommand.h"


//void IfCommand::doCommand(vector<string> & lex , int iter) { // should get the lex
//    iter += 3; // first one was "if"
//    vector<string> commandsVec;
//    // now we have all the condition
//    int breaks = 0;
//    //it++;
//    while (!(lex[iter] == "}" && breaks == 0)) {
//        if (lex[iter] == "{")
//            breaks++;
//        if (lex[iter] == "}")
//            breaks--;
//        commandsVec.push_back(lex[iter]);
//        iter++;
//    }
//    // check the condition
//    CommandsManager *cmdMgr = new CommandsManager();
//    vector <Command*> cmdVec;
//    Condition *cond = new Condition(conditionVec);
//    cond->execute(0);
//    if(cond->getResult())
//    {
//        //do commandVec
//        for(auto i = 0; i< commandsVec.size(); i++)
//        {
//            cmdVec.push_back(cmdMgr->commandsFactory(commandsVec, i));
//        }
//    }
//    //it++;
//}

void IfCommand::execute(int *index) { // should get the lex
    *index += 1; // first one was "if"
    vector<string> conditionVec, commandsVec;
    while (lex[iter] != "{") {
        conditionVec.push_back(lex[iter]);
        index++;
    }
    // now we have all the condition
    int breaks = 0;
    //it++;
    while (!(lex[iter] == "}" && breaks == 0)) {
        if (lex[iter] == "{")
            breaks++;
        if (lex[iter] == "}")
            breaks--;
        commandsVec.push_back(lex[iter]);
        *index +=1;
    }
//    // check the condition
//    CommandsManager *cmdMgr = new CommandsManager();
//    vector <Command*> cmdVec;
//    Condition *cond = new Condition(conditionVec);
//    cond->execute(index);
//    if(cond->getResult())
//   {
//    // do commandVec
//        for(auto i = 0; i< commandsVec.size(); i++)
//        {
//            cmdVec.push_back(cmdMgr->commandsFactory(commandsVec, i));
//        }
//    }
//    //*index +=1;
//}

    // check the condition
    CommandsManager *cmdMgr = new CommandsManager();
    vector <Command*> cmdVec;
//    Condition *cond = new Condition(conditionVec);
//    cond->execute(index);
    bool result = false;
    if(conditionVec.size() == 1)
    {
        result = (conditionVec[0] == "1") ? true : false;
        *index += 1;
    }
    else {
        int i = 0;
        int conditionLocation;
        string left = "";
        string right = "";
        Expression *sideA, *sideB;
        while (conditionVec[i] != "<" && conditionVec[i] != ">"
               && conditionVec[i] != "<=" && conditionVec[i] != ">="
               && conditionVec[i] != "!=" && conditionVec[i] != "==")
        {
            left += conditionVec[i];
            i++;
        }
        conditionLocation = i;
        while(i < conditionVec.size()){
            right += conditionVec[i];
        }

        Interpreter *stringToInterpretForConditionLeft = new Interpreter();
        SymbolTable *symbolTable = new SymbolTable();
        unordered_map<string, Variable *> nameOfVarToVariableMap = symbolTable->getMap();
        stringToInterpretForConditionLeft->setVariablesByMapOfVars(nameOfVarToVariableMap);
        Expression *expressionLeft = stringToInterpretForConditionLeft->interpret(left);

        Interpreter *stringToInterpretForConditionRight = new Interpreter();
        SymbolTable *symbolTableR = new SymbolTable();
        unordered_map<string, Variable *> nameOfVarToVariableMapR = symbolTable->getMap();
        stringToInterpretForConditionLeft->setVariablesByMapOfVars(nameOfVarToVariableMap);
        Expression *expressionRight = stringToInterpretForConditionLeft->interpret(right);

        if(conditionVec[conditionLocation] == ">")
            result = expressionLeft->calculate() > expressionRight->calculate() ? true : false;
        if(conditionVec[conditionLocation] == "<")
            result = expressionLeft->calculate() < expressionRight->calculate() ? true : false;
        if(conditionVec[conditionLocation] == "!=")
            result = expressionLeft->calculate() != expressionRight->calculate() ? true : false;
        if(conditionVec[conditionLocation] == "==")
            result = expressionLeft->calculate() == expressionRight->calculate() ? true : false;
        if(conditionVec[conditionLocation] == "<=")
            result = expressionLeft->calculate() <= expressionRight->calculate() ? true : false;
        if(conditionVec[conditionLocation] == ">=")
            result = expressionLeft->calculate() >= expressionRight->calculate() ? true : false;

        *index += 3;
    }

    if(result)
    {
        // do commandVec
        for(auto i = 0; i< commandsVec.size(); i++)
        {
            cmdVec.push_back(cmdMgr->commandsFactory(commandsVec, i));
        }
    }
    //*index +=1;
}
