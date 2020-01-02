#include "Parser.h"
#include "CommandsManager.h"
#include "UpdateValCommand.h"

void Parser :: parse(CommandsManager* commandsManager, vector <string> lexer) {
    for (int i = 0; i < lexer.size(); ++i) {
        cout << "i is: " << i << " " << lexer[i] << endl;
        if (i == 209) {
            cout <<"here" << endl;
        }
        // if this is command - execute it
        if (commandsManager->isCommand(lexer[i])) {
            Command *c = commandsManager -> commandsFactory(lexer, i);
            c->execute(&i);
        }
            // if the command is "=" so the i is on the var name and the next index is the "="
        else if (lexer[i+1] == "=") {
            Command *c = new UpdateValCommand(lexer[i], lexer[i+2]);
            c->execute(&i);
        }
    }
//    vector <string> blockCommand = {"while", "if"};
//
//    int linesInBlock = 0;
//    // iterate the lexer string until the end
//    for(int i = 0; i < lexer.size(); ++i) {
//        // if this is command - execute it
//        if (commandsManager->isCommand(lexer[i]) && linesInBlock == 0) {
//            Command* c = commandsManager->getCommand(lexer[i]);
//            c -> execute();
//        }
//
//        for (int j = 0; j < blockCommand.size(); ++j) {
//            // if this is not while or if continue
//            if (!lex[i].compare(blockCommand[j])) {
//                linesInBlock++;
//            }
//        }
//        // if this is the end of the block sub the indent by one
//        if (!lexer[i].compare("}")) {
//            linesInBlock--;
//        }
//
//    }
}