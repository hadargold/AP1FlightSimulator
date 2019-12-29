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
    explicit CommandsManager(const map<string, Command *> &stringToCommand);
    Command* commandsFactory(vector <string> lexer ,int i);
    //void createCommandsAndNumOfParameters();
    bool isCommand(const string &stringRepresentACommand);
    Command* getCommandByString(const string &stringRepresentACommand);
    //int getNumOfParametersByString(const string &stringRepresentACommand);
};


#endif //EX3_MANAGER_H
