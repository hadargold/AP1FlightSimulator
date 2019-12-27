//
// Created by hadar on 12/19/19.
//

#ifndef EX3_COMMAND_H
#define EX3_COMMAND_H

class Command {
public:
    virtual void execute(int index) = 0;
    virtual ~Command(){};
};

#endif //EX3_COMMAND_H