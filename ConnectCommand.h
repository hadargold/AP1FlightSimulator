//
// Created by yuval on 12/19/19.
//

#ifndef EX3_CONNECTCOMMAND_H
#define EX3_CONNECTCOMMAND_H
#include "Command.h"
#include <string>
#include <iostream>
#include "SymbolTable.h"

using namespace std;

class ConnectCommand: public Command{
private:
    SymbolTable* symbolTable;
     string ip;
     int port;
public:
    ConnectCommand(string ip, std::string  port, SymbolTable* symbolTable1);
    void execute(int* index) override;
    static void* createConnect(void* parameters);
};

#endif //EX3_CONNECTCOMMAND_H