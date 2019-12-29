//
// Created by hadar on 12/19/19.
//

#include <bits/socket.h>
#include <sys/socket.h>
#include <iostream>
#include <map>
#include "ConnectCommand.h"
#include "VariableManager.h"
#include "Interpreter.h"
#include <sys/socket.h>
#include <string>
#include <iostream>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "UpdateValCommand.h"
#include "SymbolTable.h"

string getNameOfVarBySimulator(string nameAccordingToClientAndValue);

ConnectCommand :: ConnectCommand(std::string  ip, std::string  port) {
    this->ip = ip;
    // change the port to int
    auto *stringToInterpretForPort= new Interpreter();
    auto *variableManager = new VariableManager();
    stringToInterpretForPort->setVariablesByMapOfVars(variableManager->getVarList());
    Expression *expressionToPrint = stringToInterpretForPort->interpret(port);
    int intPort = (int) expressionToPrint->calculate();
    this->port = intPort;
}

void ConnectCommand:: execute(int* index) {
    pthread_t thread;
    // parameters contains the parameters to the createConnectString
    pthread_create(&thread, nullptr, ConnectCommand::createConnect , nullptr);
    *index += 2;
}


void* ConnectCommand::createConnect(void* parameters) {
    //create socket
    int client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket == -1) {
        //error
        std::cerr << "Could not create a socket"<<std::endl;
        exit(1);
    }

    //We need to create a sockaddr obj to hold address of server
    sockaddr_in address{}; //in means IP4
    address.sin_family = AF_INET;//IP4
    address.sin_addr.s_addr = inet_addr(this->ip);  //the localhost address
    address.sin_port = htons(this->port);
    //we need to convert our number (both port & localhost)
    // to a number that the network understands.

    // Requesting a connection with the server on local host with port 8081
    int is_connect = connect(client_socket, (struct sockaddr *)&address, sizeof(address));
    if (is_connect == -1) {
        std::cerr << "Could not connect to host server"<<std::endl;
        exit(1);
    } else {
        std::cout<<"Client is now connected to server" <<std::endl;
    }
    // the client noe is connected to the server
    // now the client need to send flight instructions to the server
    auto *updateValCommand = new UpdateValCommand();
    std::queue<std::pair<std::string, double>> valuesToSend = updateValCommand->getValuesToSend();
    while (true) {
        // values to send is queue of values so send to the simulator
        if (!valuesToSend.empty()) {
            std::pair<std::string, double> nameAccordingToClientAndValue = valuesToSend.front();
            valuesToSend.pop();
            string NameOfVarBySimulator = getNameOfVarBySimulator(nameAccordingToClientAndValue.first);
            string message = "set " + NameOfVarBySimulator + " " + to_string(nameAccordingToClientAndValue.second) + "\r\n";
            write(client_socket, message.c_str(), message.length());
        }
    }
}

string getNameOfVarBySimulator(const string nameAccordingToClientAndValue) {
    auto *symbolTable = new SymbolTable();
    map<string, Variable> NameToVariableMap = symbolTable->getMap();
    Variable var = NameToVariableMap[nameAccordingToClientAndValue];
    return var.getName();
}



