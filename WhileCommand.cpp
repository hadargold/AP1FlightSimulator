//
// Created by hadar on 12/27/19.
//

#include "WhileCommand.h"

void WhileCommand::execute(int *index) { // should get the lex
    (*index) += 1; // first one was "if"
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

//    while(calcResult(conditionVec))
//    {
//        // do commandVec
//        for(auto i = 0; i< commandsVec.size(); i++)
//        {
//            //TODO SEND COMMAND VEC TO PARSER - ASK YUVAL on if too
//            //cmdVec.push_back(cmdMgr->commandsFactory(commandsVec, i));
//            //cmdMgr->commandsFactory(commandsVec, i);
//        }
//    }
    (*index) -=1;
//    cout<<(*index)<<endl;
}


bool WhileCommand::calcResult(vector<string> conditionVec) {
    // check the condition
    CommandsManager *cmdMgr = new CommandsManager();
    vector<Command *> cmdVec;
//    Condition *cond = new Condition(conditionVec);
//    cond->execute(index);
    bool result = false;
    if (conditionVec.size() == 1) {
        //checkkkkkkkkkkkkkkkkkkkkkkk
        result = (conditionVec[0] == "1") ? true : false;
        //*index += 1;
    } else {
        int i = 0;
        int conditionLocation;
        string left = conditionVec[0];
        string right = conditionVec[2];
        Expression *sideA, *sideB;
        // maybe dont need it
//        while (conditionVec[i] != "<" && conditionVec[i] != ">"
//               && conditionVec[i] != "<=" && conditionVec[i] != ">="
//               && conditionVec[i] != "!=" && conditionVec[i] != "==")
//        {
//            left += conditionVec[i];
//            i++;
//        }
//        conditionLocation = i;
//        while(i < conditionVec.size()){
//            right += conditionVec[i];
//        }

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

        if (conditionVec[1] == ">")
            result = expressionLeft->calculate() > expressionRight->calculate() ? true : false;
        if (conditionVec[1] == "<")
            result = expressionLeft->calculate() < expressionRight->calculate() ? true : false;
        if (conditionVec[1] == "!=")
            result = expressionLeft->calculate() != expressionRight->calculate() ? true : false;
        if (conditionVec[1] == "==")
            result = expressionLeft->calculate() == expressionRight->calculate() ? true : false;
        if (conditionVec[1] == "<=")
            result = expressionLeft->calculate() <= expressionRight->calculate() ? true : false;
        if (conditionVec[1] == ">=")
            result = expressionLeft->calculate() >= expressionRight->calculate() ? true : false;

        //*index += 3;
    }
}



////
//// Created by hadar on 12/29/19.
////
//
//#include "WhileCommand.h"
//
//void WhileCommand::doCommand(vector<string> &text) {
//    it++; // first one was "if"
//    vector<string> conditionVec, commandsVec;
//    // till we see a { that is the condition
//    while (*it != "{") {
//        conditionVec.push_back(*it);
//        it++;
//    }
//    // now we have all the condition
//    int breaks = 0;
//    it++;
//    while (!(*it == "}" && breaks == 0)) {
//        if (*it == "{")
//            breaks++;
//        if (*it == "}")
//            breaks--;
//        commandsVec.push_back(*it);
//        it++;
//    }
//    // check the condition
//    const map<string, Command *> &stringToCommand = {};
//    CommandsManager * cmdMgr = new CommandsManager(stringToCommand);
//    vector <Command> cmdVec;
//    Condition *cond = new Condition(conditionVec);
//    cond->execute(0);
//    while(cond->getResult())
//    {
//        //do commandVec
//        for(auto i = 0; i< commandsVec.size(); i++)
//        {
//            cmdVec.push_back(cmdMgr->commandsFactory(commandsVec, i));
//        }
//    }
//    it++;
//}
