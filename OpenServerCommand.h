#ifndef EX3_OPENSERVERCOMMAND_H
#define EX3_OPENSERVERCOMMAND_H

#include <string>

using namespace std;

class OpenServerCommand: public Command{
private:
    string strPort;
public:
    void ConnectCommand(string ip, string port) {
        this->strPort = port;
    }
    void execute(int& index);
    void* openDataServer(void* parameters);
};

#endif //EX3_OPENSERVERCOMMAND_H
