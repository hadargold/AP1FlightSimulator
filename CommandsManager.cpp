#include "CommandsManager.h"
#include "SleepCommand.h"
#include "ConnectCommand.h"
#include "WhileCommand.h"
#include "IfCommand.h"
#include "PrintCommand.h"
#include "UpdateValCommand.h"
#include "OpenServerCommand.h"
#include "ex1.h"
#include "VarCommand.h"
#include "OpenServerCommand.h"
#include <algorithm>

using namespace std;


// return true if there is a command represented by the string
bool CommandsManager::isCommand(const string &stringRepresentACommand) {
    if (std::find(namesOfCommands.begin(), namesOfCommands.end(),
            stringRepresentACommand) != namesOfCommands.end()) {
        return true;
    } else {
        return false;
    }
}

// returns the command of the string
Command* CommandsManager::getCommandByString(const string &stringRepresentACommand){
    return stringToCommand[stringRepresentACommand];
}

//int getNumOfParametersByString(const string &stringRepresentACommand) {
//    return commandToNumOfParameters[stringRepresentACommand];
//}


Command* CommandsManager::commandsFactory(vector <string> lexer ,int i) {
    //enum commandsName {WHILE, IF, OPEN_DATA_SERVER ,CONNECT,VAR,SLEEP,PRINT};
    if (lexer[i].compare("while")) {

    } else if (lexer[i].compare("if")) {

    } else if (lexer[i].compare("var")) {
        return new VarCommand(lexer[i+1], lexer[i+2], lexer[i+3]);
    }else if (lexer[i].compare("openDataServer")) {
        return new OpenServerCommand(lexer[i+1]);
    }else if (lexer[i].compare("connectControlClient")) {
        return new ConnectCommand(lexer[i+1].c_str(), lexer[i+2]);
    }else if (lexer[i].compare("sleep")) {
        return new SleepCommand(lexer[i+1]);
    }else if (lexer[i].compare("print")) {
        return new PrintCommand(lexer[i+1]);
    }
}

//void CommandsManager::createCommandsAndNumOfParameters() {
//    commandToNumOfParameters["while"] = // do it!!;
//    commandToNumOfParameters["if"] = // do it!!;
//    commandToNumOfParameters["openDataServer"] = 1;
//    commandToNumOfParameters["connect"] = 2;
//    commandToNumOfParameters["var"] = // do it!!;
//    commandToNumOfParameters["sleep"] = 1;
//    commandToNumOfParameters["print"] = 1;
//
//}

