//
// Created by yuval on 12/19/19.
//

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
public:
    CommandsManager() {
        namesOfCommands = {"while", "if", "var","openDataServer","connectControlClient", "Sleep", "Print"};
        this->symbolTable = new SymbolTable();
    }
    explicit CommandsManager(const map<string, Command *> &stringToCommand);
    Command* commandsFactory(vector <string> lexer ,int i);
    bool isCommand(const string &stringRepresentACommand);
    Command* getCommandByString(const string &stringRepresentACommand);
    SymbolTable* getSymbolTable();

};


#endif //EX3_MANAGER_H
