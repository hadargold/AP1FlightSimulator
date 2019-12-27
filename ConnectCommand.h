//
// Created by hadar on 12/19/19.
//

#ifndef EX3_CONNECTCOMMAND_H
#define EX3_CONNECTCOMMAND_H
#include "Command.h"

class ConnectCommand: public Command{
private:
    string ip;
    string strPort;
public:
    explicit ConnectCommand(string ip, string port) {
        this->ip = ip;
        this->strPort = port;
    }
    void execute(int& index);
    void* createConnect(void* parameters);
};

#endif //EX3_CONNECTCOMMAND_H