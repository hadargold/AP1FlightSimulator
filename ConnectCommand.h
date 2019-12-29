//
// Created by hadar on 12/19/19.
//

#ifndef EX3_CONNECTCOMMAND_H
#define EX3_CONNECTCOMMAND_H
#include "Command.h"
#include <string>
#include <iostream>


class ConnectCommand: public Command{
private:
     char *ip;
     int port;
public:
    ConnectCommand(const char *ip, std::string  port);
    void execute(int* index) override;
    static void* createConnect(void* parameters);
};

#endif //EX3_CONNECTCOMMAND_H