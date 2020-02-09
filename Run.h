//
// Created by yuval on 12/30/19.
//

#ifndef FLIGHTSIMULATOR_RUN_H
#define FLIGHTSIMULATOR_RUN_H

#include "Lexer.h"
class Run {
    vector <string> lexerVectorString;
    CommandsManager *commandsManager;
    Parser *parser;
public:
    Run(string textFile)
    {
        Lexer myLexer;
        lexerVectorString = myLexer.lexerToTextFile(textFile);
        commandsManager = new CommandsManager();
        parser = new Parser();
    }
    void run(){
    parser->parse(commandsManager,lexerVectorString);

    }
};


#endif //FLIGHTSIMULATOR_RUN_H
