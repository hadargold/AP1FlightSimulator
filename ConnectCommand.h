//
// Created by hadar on 12/19/19.
//

#ifndef EX3_CONNECTCOMMAND_H
#define EX3_CONNECTCOMMAND_H
#include "Command.h"
#include <string>
#include <iostream>

using namespace std;

class ConnectCommand: public Command{
private:
     string ip;
     int port;
public:
    ConnectCommand(string ip, std::string  port);
    void execute(int* index) override;
    static void* createConnect(void* parameters);
};

#endif //EX3_CONNECTCOMMAND_H