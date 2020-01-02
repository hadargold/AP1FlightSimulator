//
// Created by yuval on 12/30/19.
//

#ifndef FLIGHTSIMULATOR_INTERPETERFORSMARTPEOPLE_H
#define FLIGHTSIMULATOR_INTERPETERFORSMARTPEOPLE_H

#include "Lexer.h"
class InterpeterForSmartPeople {
    vector <string> lexerVectorString;
    CommandsManager *commandsManager;
    Parser *parser;
public:
    InterpeterForSmartPeople(string textFile)
    {
        Lexer myLexer;
        lexerVectorString = myLexer.lexerToTextFile("fly.txt");
        commandsManager = new CommandsManager();
        parser = new Parser();
    }
    void run(){
    //vector <string> lexerForTest;
//    lexerForTest.push_back("openDataServer");
//    lexerForTest.push_back("12345");
//    lexerForTest.push_back("connectControlClient");
//    lexerForTest.push_back("127.0.0.1");
//    lexerForTest.push_back("5402");
//    lexerForTest.push_back("var");
//    lexerForTest.push_back("warp");
//    lexerForTest.push_back("->");
//    lexerForTest.push_back("sim\"/sim/time/warp\"");
    parser->parse(commandsManager,lexerVectorString);

    }
};


#endif //FLIGHTSIMULATOR_INTERPETERFORSMARTPEOPLE_H
