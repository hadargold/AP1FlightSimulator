//
// Created by yuval on 12/19/19.
//

#ifndef EX3_CONNECTCOMMAND_H
#define EX3_CONNECTCOMMAND_H
#include "Command.h"
#include <string>
#include <iostream>
#include <queue>
#include "SymbolTable.h"

using namespace std;

class ConnectCommand: public Command{
private:
    SymbolTable* symbolTable;
     string ip;
     int port;
     std::queue<std::pair<std::string, double>> * valuesToSendToTheSim ;
    pthread_mutex_t *mutex;
public:
    ConnectCommand(string ip, std::string  port, SymbolTable* symbolTable1,
        std::queue<std::pair<std::string, double>> * valuesToSendToTheSim, pthread_mutex_t* mutex);
    void execute(int* index) override;
    static void* createConnect(void* parameters);
};

#endif //EX3_CONNECTCOMMAND_H