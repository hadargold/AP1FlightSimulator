//
// Created by yuval on 12/19/19.
//

#ifndef EX3_MANAGER_H
#define EX3_MANAGER_H

#include <string>
#include <map>
#include <vector>
#include <string>
#include <queue>
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
    std::queue<std::pair<std::string, double>> valuesToSendToTheSim;
    pthread_mutex_t mutex;
public:
    CommandsManager() {
        namesOfCommands = {"while", "if", "var","openDataServer","connectControlClient", "Sleep", "Print"};
        this->symbolTable = new SymbolTable();
        pthread_mutex_init(&mutex, nullptr);
    }
    explicit CommandsManager(const map<string, Command *> &stringToCommand );
    Command* commandsFactory(vector <string> lexer ,int i);
    bool isCommand(const string &stringRepresentACommand);
    Command* getCommandByString(const string &stringRepresentACommand);
    SymbolTable* getSymbolTable();
    std::queue<std::pair<std::string, double>>* getValToSend() {
      return &valuesToSendToTheSim;
    }
    pthread_mutex_t* getMutex() {
        return &(this->mutex);
    }
    ~CommandsManager() {
        pthread_mutex_destroy(&mutex);
    }


};


#endif //EX3_MANAGER_H
