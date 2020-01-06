//
// Created by yuval on 12/26/19.
//

#ifndef EX3_DEFINEVARCOMMAND_H
#define EX3_DEFINEVARCOMMAND_H

#include <string>
#include "Command.h"
#include <queue>
#include "SymbolTable.h"

using namespace std;

class UpdateValCommand :public Command {
private:
    SymbolTable *symbolTable;
    string varName;
    string value;
    std::queue<std::pair<std::string, double>>* valuesToSendToTheSim ;
    pthread_mutex_t *mutex;
public:
    //UpdateValCommand() = default;
    UpdateValCommand(string varName, string value, SymbolTable* symbolTable,queue<std::pair<std::string, double>> *val,
                     pthread_mutex_t *mutex){
        this->varName = varName;
        this->value = value;
        this->symbolTable = symbolTable;
        this->valuesToSendToTheSim = val;
        this->mutex = mutex;
    }
    void execute(int* index);
    std::queue<std::pair<std::string, double>> *getValuesToSend() {
        return this->valuesToSendToTheSim;
    }
};

#endif //EX3_DEFINEVARCOMMAND_H
