#ifndef EX3_MANAGER_H
#define EX3_MANAGER_H

#include <string>
#include <map>
#include <vector>
#include <string>
#include "unordered_map"
#include "Command.h"
#include "ex1.h"
#include "SymbolTable.h"
using namespace std;

class CommandsManager {
private:
    vector <string > namesOfCommands;
    map <string , Command*> stringToCommand;
    SymbolTable *symbolTable;
    //map <string , int> commandToNumOfParameters; // was in private
public:
    CommandsManager() {
        namesOfCommands = {"while", "if", "var","openDataServer","connectControlClient", "Sleep", "Print"};
        this->symbolTable = new SymbolTable();
    }
    explicit CommandsManager(const map<string, Command *> &stringToCommand);
    Command* commandsFactory(vector <string> lexer ,int i);
    //void createCommandsAndNumOfParameters();
    //int getNumOfParametersByString(const string &stringRepresentACommand);
    bool isCommand(const string &stringRepresentACommand);
    Command* getCommandByString(const string &stringRepresentACommand);
    SymbolTable* getSymbolTable();

};


#endif //EX3_MANAGER_H
