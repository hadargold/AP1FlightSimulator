//
// Created by yuval on 12/26/19.
//

#ifndef EX3_DEFINEVARCOMMAND_H
#define EX3_DEFINEVARCOMMAND_H

using namespace std;

class DefineValCommand :public Command {
private:
    string varName;
    string value;
public:
    DefineValCommand(string varName, string value) {
        this->varName = varName;
        this->value = value;
    }
    void execute(int& index);
};

#endif //EX3_DEFINEVARCOMMAND_H