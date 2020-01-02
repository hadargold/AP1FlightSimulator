//
// Created by hadar on 12/27/19.
//

#include "IfCommand.h"

IfCommand::IfCommand(string a, string op, string b, int i ,vector <string> lexer) {
    conditionVec.push_back(a);
    conditionVec.push_back(op);
    conditionVec.push_back(b);
    this->iter = i;
    this->lex = *lexer; // check * !!!!!
}

void IfCommand::doCommand(vector<string> & lex , int iter) { // should get the lex
    iter += 3; // first one was "if"
    vector<string> commandsVec;
    // now we have all the condition
    int breaks = 0;
    //it++;
    while (!(lex[iter] == "}" && breaks == 0)) {
        if (lex[iter] == "{")
            breaks++;
        if (lex[iter] == "}")
            breaks--;
        commandsVec.push_back(lex[iter]);
        iter++;
    }
    // check the condition
    CommandsManager *cmdMgr = new CommandsManager();
    vector <Command*> cmdVec;
    Condition *cond = new Condition(conditionVec);
    cond->execute(0);
    if(cond->getResult())
    {
        //do commandVec
        for(auto i = 0; i< commandsVec.size(); i++)
        {
            cmdVec.push_back(cmdMgr->commandsFactory(commandsVec, i));
        }
    }
    it++;
}