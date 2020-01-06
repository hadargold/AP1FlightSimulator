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

SymbolTable* CommandsManager::getSymbolTable() {
    return this->symbolTable;
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
//    if (lexer[i].compare("while") == 0) {
//
//    } else
    if (lexer[i].compare("if") == 0) {
        return new IfCommand(lexer, i, this->symbolTable, this);
    }else if (lexer[i].compare("while") == 0) {
        return new WhileCommand(lexer, i, this->symbolTable, this);
    }else if (lexer[i].compare("var") == 0) {
        return new VarCommand(lexer[i+1], lexer[i+2],lexer[i+3], this->symbolTable);
    }else if (lexer[i].compare("openDataServer") == 0) {
        return new OpenServerCommand(lexer[i+2], this->symbolTable);
    }else if (lexer[i].compare("connectControlClient") == 0) {
        // TODO- need to be changed. ip and port from the lexer.
        //return new ConnectCommand("127.0.0.1", "15463");
        return new ConnectCommand(lexer[i+2], lexer[i+3], this->symbolTable);
    }else if (lexer[i].compare("Sleep") == 0) {
          return new SleepCommand(lexer[i+2], this->symbolTable);
    }else if (lexer[i].compare("Print") == 0) {
        return new PrintCommand(lexer[i+2], this->symbolTable);
    }
//    else if (lexer[i].compare("if") == 0) {
//        return new IfCommand(i, lexer);
//    }
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

