#ifndef EX3_MANAGER_H
#define EX3_MANAGER_H

#include <string>
#include <map>
#include <vector>
#include <string>
#include "unordered_map"
#include "Command.h"
#include "ex1.h"

using namespace std;

class CommandsManager {
private:
    vector <string > namesOfCommands;
    map <string , Command*> stringToCommand;
    //map <string , int> commandToNumOfParameters; // was in private
public:
    CommandsManager() {
        namesOfCommands = {"while", "if", "var","openDataServer","connectControlClient", "sleep", "print"};
    }
    explicit CommandsManager(const map<string, Command *> &stringToCommand);
    Command* commandsFactory(vector <string> lexer ,int i);
    //void createCommandsAndNumOfParameters();
    bool isCommand(const string &stringRepresentACommand);
    Command* getCommandByString(const string &stringRepresentACommand);
    //int getNumOfParametersByString(const string &stringRepresentACommand);
};


#endif //EX3_MANAGER_H
