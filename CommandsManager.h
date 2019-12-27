#ifndef EX3_MANAGER_H
#define EX3_MANAGER_H

#include <string>
#include <map>
#include <vector>
#include "Command.h"

class CommandsManager {
private:
    map<string, Command*> stringToCommand;
    map<string, int> commandToNumOfParameters;
public:
    Command* commandsFactory(const sring lexer,int i,int numOfParameters);
    void createCommandsAndNumOfParameters();
    bool isCommand(const string &stringRepresentACommand);
    Command* getCommandByString(const string &stringRepresentACommand);
    int getNumOfParametersByString(const string &stringRepresentACommand);
}


#endif //EX3_MANAGER_H
