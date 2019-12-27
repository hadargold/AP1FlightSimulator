#include "CommandsManager.h"
#include "SleepCommand.h"
#include "ConnectCommand.h"
#include "WhileCommand.h"
#include "IfCommand.h"
#include "PrintCommand.h"
#include "UpdateValCommand.h"
#include "OpenServerCommand.h"
using namespace std

// return true if there is a command represented by the string
bool CommandsManager::isCommand(const string &stringRepresentACommand) {
    map<string, Command*> :: iterator it = commandToNumOfParameters.find(stringRepresentACommand);
    // if find didnt return pointer to the end of the map so the key is exists
    if (it != commandToNumOfParameters.end()) {
        return true;
    }
    return false;
}

// returns the command of the string
Command* CommandsManager::getCommandByString(const string &stringRepresentACommand){
    return stringToCommand[stringRepresentACommand];
}

int getNumOfParametersByString(const string &stringRepresentACommand) {
    return commandToNumOfParameters[stringRepresentACommand];
}


Command* commandsFactory(const sring lexer ,int i) {
    enum commandsName {WHILE, IF, OPEN_DATA_SERVER ,CONNECT,VAR,SLEEP,PRINT};
    if (lexer[i].compare("while")) {

    } else if (lexer[i].compare("if")) {

    } else if (lexer[i].compare("var")) {
        return new Var(lexer[i+1], lexer[i+2], lexer[i+3]);
    }else if (lexer[i].compare("openDataServer")) {
        return new OpenServerCommand(lexer[i+1]);
    }else if (lexer[i].compare("connectControlClient")) {
        return new ConnectCommand(lexer[i+1], lexer[i+2]);
    }else if (lexer[i].compare("sleep")) {
        return new SleepCommand(lexer[i+1]);
    }else if (lexer[i].compare("print")) {
        return new PrintCommand(lexer[i+1]);
    }
}

void CommandsManager::createCommandsAndNumOfParameters() {
    commandToNumOfParameters["while"] = // do it!!;
    commandToNumOfParameters["if"] = // do it!!;
    commandToNumOfParameters["openDataServer"] = 1;
    commandToNumOfParameters["connect"] = 2;
    commandToNumOfParameters["var"] = // do it!!;
    commandToNumOfParameters["sleep"] = 1;
    commandToNumOfParameters["print"] = 1;

}