//
// Created by hadar on 12/27/19.
//

#include "IfCommand.h"

void IfCommand::doCommand(vector<string> &text) {
    it++; // first one was "if"
    vector<string> conditionVec, commandsVec;
    // till we see a { that is the condition
    while (*it != "{") {
        conditionVec.push_back(*it);
        it++;
    }
    // now we have all the condition
    int breaks = 0;
    it++;
    while (!(*it == "}" && breaks == 0)) {
        if (*it == "{")
            breaks++;
        if (*it == "}")
            breaks--;
        commandsVec.push_back(*it);
        it++;
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