//
// Created by yuval on 12/26/19.
//

#ifndef EX3_DEFINEVARCOMMAND_H
#define EX3_DEFINEVARCOMMAND_H

#include <string>
#include "Command.h"
#include <queue>

using namespace std;

class UpdateValCommand :public Command {
private:
    string varName;
    string value;
    std::queue<std::pair<std::string, double>> valuesToSendToTheSim ;
public:
    UpdateValCommand() = default;
    UpdateValCommand(string varName, string value) {
        this->varName = varName;
        this->value = value;
    }
    void execute(int* index);
    std::queue<std::pair<std::string, double>> getValuesToSend() {
        return this->valuesToSendToTheSim;
    }
};

#endif //EX3_DEFINEVARCOMMAND_H
