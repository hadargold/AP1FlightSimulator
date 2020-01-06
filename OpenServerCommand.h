//
// Created by yuval on 12/22/19.
//
#ifndef EX3_OPENSERVERCOMMAND_H
#define EX3_OPENSERVERCOMMAND_H

#include <string>
#include "Command.h"
#include "SymbolTable.h"

using namespace std;

class OpenServerCommand: public Command{
private:
    SymbolTable* symbolTable;
    int port;
    pthread_mutex_t *mutex;
public:
    OpenServerCommand(string strPort, SymbolTable* symbolTable, pthread_mutex_t* mutex);
    void execute(int* index);
    static void* openDataServer(void* parameters);
};

#endif //EX3_OPENSERVERCOMMAND_H
