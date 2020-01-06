//
// Created by yuval on 12/22/19.
//
#include "Parser.h"
#include "CommandsManager.h"
#include "UpdateValCommand.h"

// parse the lexer,create commands and executing it
void Parser :: parse(CommandsManager* commandsManager, vector <string> lexer) {
    for (int i = 0; i < lexer.size(); ++i) {
        // if this is command - execute it
        if (commandsManager->isCommand(lexer[i])) {
            Command *c = commandsManager -> commandsFactory(lexer, i);
            c->execute(&i);
        }
            // if the command is "=" so the i is on the var name and the next index is the "="
        else if (lexer[i+1] == "=") {
            Command *c = new UpdateValCommand(lexer[i], lexer[i+2], commandsManager->getSymbolTable());
            c->execute(&i);
        }
    }
}