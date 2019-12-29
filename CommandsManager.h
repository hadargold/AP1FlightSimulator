#ifndef EX3_MANAGER_H
#define EX3_MANAGER_H

#include <string>
#include <map>
#include <vector>
#include <string>
#include "unordered_map"
#include "Command.h"

using namespace std;

class CommandsManager {
private:
    map <string , Command*> stringToCommand;

public:
    map <string , int> commandToNumOfParameters; // was in private
    CommandsManager(const map<string, Command *> &stringToCommand);
    Command* commandsFactory(const string lexer,int i,int numOfParameters);
    void createCommandsAndNumOfParameters();
    bool isCommand(const string &stringRepresentACommand);
    Command* getCommandByString(const string &stringRepresentACommand);
    int getNumOfParametersByString(const string &stringRepresentACommand);
};


#endif //EX3_MANAGER_H
