#ifndef EX3_OPENSERVERCOMMAND_H
#define EX3_OPENSERVERCOMMAND_H

class OpenServerCommand: public Command{
private:
    string strPort;
public:
    explicit ConnectCommand(string ip, string port) {
        this->strPort = port;
    }
    void execute(int& index);
    void* openDataServer(void* parameters);
};

#endif //EX3_OPENSERVERCOMMAND_H
