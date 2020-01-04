//
// Created by hadar on 12/27/19.
//

#ifndef FLIGHTSIMULATOR_WHILECOMMAND_H
#define FLIGHTSIMULATOR_WHILECOMMAND_H

#include <string>
#include "Condition.h"
#include "CommandsManager.h"

//class IfCommand : public Condition{
class WhileCommand : public Command{
    //vector<string>::iterator &it;
    //vector<string> conditionVec;
    int iter;
    vector <string> lex;
public:
    explicit WhileCommand(int i ,vector <string> lexer) {
        this->iter = i;
        this->lex = lexer; // check * !!!!!
    }
    void doCommand(vector<string> &text);
    void execute(int *index);
    bool calcResult(vector<string> conditionVec);
};


#endif //FLIGHTSIMULATOR_WHILECOMMAND_H


////
//// Created by hadar on 12/29/19.
////
//
//#ifndef FLIGHTSIMULATOR_WHILECOMMAND_H
//#define FLIGHTSIMULATOR_WHILECOMMAND_H
//
//
//#include "Condition.h"
//#include "CommandsManager.h"
//
//class WhileCommand : Condition {
//    vector<string>::iterator &it;
//public:
//    void doCommand(vector<string> &text);
//};
//
//#endif //FLIGHTSIMULATOR_WHILECOMMAND_H
