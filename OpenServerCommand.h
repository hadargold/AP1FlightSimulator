#ifndef EX3_OPENSERVERCOMMAND_H
#define EX3_OPENSERVERCOMMAND_H

#include <string>
#include "Command.h"

using namespace std;

class OpenServerCommand: public Command{
private:
    string strPort;
public:
    OpenServerCommand(string strPort);
    void execute(int* index);
    void* openDataServer(void* parameters);
};

#endif //EX3_OPENSERVERCOMMAND_H
