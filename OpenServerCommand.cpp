//
// Created by hadar on 12/22/19.
//

#include "OpenServerCommand.h"
#include <thread>
#include <bits/socket.h>
#include <bits/socket_type.h>
#include <sys/socket.h>
#include <iostream>
#include <netinet/in.h>
#include <unistd.h>
#include "VariableManager.h"
#include "Interpreter.h"
#include "ConnectCommand.h"
#include <regex>
#include <complex>
#include "SymbolTable.h"

void updateValuesInSymbolTable(string stringOfValuesFromSim);
vector <string> splitByComma(string stringOfValuesFromSim);

OpenServerCommand :: OpenServerCommand(std::string strPort) {
    // change the port to int
    auto *stringToInterpretForPort= new Interpreter();
    auto *variableManager = new VariableManager();
    stringToInterpretForPort->setVariablesByMapOfVars(variableManager->getVarList());
    Expression *expressionToPrint = stringToInterpretForPort->interpret(strPort);
    int intPort = (int) expressionToPrint->calculate();
    this->port = intPort;
}

void OpenServerCommand:: execute(int* index) {
    pthread_t thread;
    // parameters contains the parameters to the createConnectString
    struct parameters {
        int portToconnect;
    };
    parameters *parametersToOpenDataServer = new parameters();
    parametersToOpenDataServer->portToconnect = this->port;
    pthread_create(&thread, nullptr, openDataServer, parametersToOpenDataServer);
    *index += 1;
}

void* OpenServerCommand::openDataServer(void* arguments) {
    struct parameters* parametersToOpenDataServer = (struct parameters*) arguments;
    //create socket
    int socketfd = socket(AF_INET, SOCK_STREAM, 0);
    if (socketfd == -1) {
        //error
        std::cerr << "Could not create a socket" << std::endl;
        exit(1);
    }

    //bind socket to IP address
    // we first need to create the sockaddr obj.
    sockaddr_in address; //in means IP4
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY; //give me any IP allocated for my machine
    address.sin_port = htons(parametersToOpenDataServer.portToconnect);
    //we need to convert our number
    // to a number that the network understands.

    //the actual bind command
    if (bind(socketfd, (struct sockaddr *) &address, sizeof(address)) == -1) {
        std::cerr << "Could not bind the socket to an IP" << std::endl;
        exit(1);
    }

    //making socket listen to the port
    if (listen(socketfd, 5) == -1) { //can also set to SOMAXCON (max connections)
        std::cerr << "Error during listening command" << std::endl;
        exit(1);
    } else {
        std::cout << "Server is now listening ..." << std::endl;
    }

    // accepting a client
    int client_socket = accept(socketfd, (struct sockaddr *) &address,
                               (socklen_t * ) & address);

    if (client_socket == -1) {
        std::cerr << "Error accepting client" << std::endl;
        exit(1);
    }

    close(socketfd); //closing the listening socket

    //reading from client
    while (true) {
        string stringOfValuesFromSim = "";
        char buffer[1024] = {0};
        //valread is 0 if there is no data to read. -1 is there was an erroe
        int valread = read(client_socket, buffer, 1024);
        if (valread > 0) {
            for (int i = 0; i < valread; i++) {
                char c = buffer[i];
                // if this is the end of the values (36 values)
                if (c == '\n') {
                    if (stringOfValuesFromSim.length() > 0) {
                        updateValuesInSymbolTable(stringOfValuesFromSim);
                        stringOfValuesFromSim = "";
                    }
                } else stringOfValuesFromSim += c;
            }
        }
    }
}

void updateValuesInSymbolTable(const string stringOfValuesFromSim) {
    vector <string> splitValues = splitByComma(stringOfValuesFromSim);
    auto *symbolTable = new SymbolTable();
    symbolTable->addValuesFromSimToSymbolTable(splitValues);
}

vector <string> splitByComma(string stringOfValuesFromSim) {
    vector <string> splitValues;
    regex r("[^,]+");
    std::smatch match;
    while (regex_search(stringOfValuesFromSim, match, r)) {
        string str = match[0];
        splitValues.push_back(str);
        // the index of the matching
        int indexOfMatching = match.position();
        // search again on the continue of the string
        stringOfValuesFromSim = stringOfValuesFromSim.substr(indexOfMatching + match.length());
    }
    return splitValues;
}


