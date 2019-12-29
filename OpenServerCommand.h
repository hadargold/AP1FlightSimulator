//
// Created by hadar on 12/19/19.
//

#ifndef EX3_OPENSERVERCOMMAND_H
#define EX3_OPENSERVERCOMMAND_H

#include <string>
#include "Command.h"
using namespace std;

class OpenServerCommand: public Command{
private:
    int port;
public:
    OpenServerCommand(string port);
    void execute(int* index) override;
    static void* openDataServer(void* parameters);
};

#endif //EX3_OPENSERVERCOMMAND_H
