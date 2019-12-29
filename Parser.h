#ifndef EX3_PARSER_H
#define EX3_PARSER_H

#include <string>
#include "CommandsManager.h"
#include "Command.h"

class Parser{
public:
    void parse(CommandsManager* commandsManager ,vector <string> lexer) ;
};




#endif //EX3_PARSER_H
