//
// Created by yuval on 12/19/19.
//

#include <sys/socket.h>
#include <iostream>
#include <map>
#include "ConnectCommand.h"
#include "Interpreter.h"
#include <sys/socket.h>
#include <string>
#include <iostream>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "UpdateValCommand.h"
#include "SymbolTable.h"
#include <mutex>
using namespace std;

string getNameOfVarBySimulator(string nameAccordingToClientAndValue, SymbolTable* symbolTable);

// constructor for connect command
ConnectCommand :: ConnectCommand(string ip, string  port, SymbolTable* symbolTable1,
    std::queue<std::pair<std::string, double>>* valuesToSendToTheSim, pthread_mutex_t* mutex) {
    this -> mutex = mutex;
    this->valuesToSendToTheSim = valuesToSendToTheSim;
    ip = ip.substr(1, ip.length()-2);
    this->ip = ip;
    this->symbolTable = symbolTable1;
    // change the port to int
    auto *stringToInterpretForPort= new Interpreter();
    unordered_map<string,Variable*> nameOfVarToVariableMap = this->symbolTable->getMap();
    stringToInterpretForPort->setVariablesByMapOfVars(nameOfVarToVariableMap);
    Expression *expressionToPort = stringToInterpretForPort->interpret(port);
    int intPort = (int) expressionToPort->calculate();
    this->port = intPort;
}

// parameters for coonect function
struct parameters {
    int clientSocket;
    SymbolTable* symbolTableForConnection;
    std::queue<std::pair<std::string, double>>* valuesToSend ;
    pthread_mutex_t *mutex;
};

// execute the connection
void ConnectCommand:: execute(int* index) {
    int client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket == -1) {
        //error
        std::cerr << "Could not create a socket"<<std::endl;
        exit(1);
    }
    //We need to create a sockaddr obj to hold address of server
    sockaddr_in address{}; //in means IP4
    address.sin_family = AF_INET;//IP4
    address.sin_addr.s_addr = inet_addr(this->ip.c_str());  //the localhost address
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

    // parameters contains the parameters to the createConnectString
    struct parameters *parametersToConnect;
    parametersToConnect = new parameters();
    parametersToConnect->clientSocket = client_socket;
    parametersToConnect->symbolTableForConnection = this->symbolTable;
    parametersToConnect->valuesToSend = this->valuesToSendToTheSim;
    parametersToConnect->mutex = this->mutex;
    pthread_t thread;
    pthread_create(&thread, nullptr, ConnectCommand::createConnect , parametersToConnect);
    *index += 4;
}


// creates the connection to the simulator and sends values to it
void* ConnectCommand::createConnect(void* arguments) {
    struct parameters *parametersToConnect = (struct parameters *) arguments;
//
    //auto *updateValCommand = new UpdateValCommand();
    //std::queue<std::pair<std::string, double>> valuesToSend = updateValCommand->getValuesToSend();
    while (true) {
        // values to send is queue of values so send to the simulator
        if (!parametersToConnect->valuesToSend->empty()) {
            pthread_mutex_lock(parametersToConnect->mutex);
          std::pair<std::string, double> nameAccordingToClientAndValue = parametersToConnect->valuesToSend->front();
          parametersToConnect->valuesToSend->pop();
          string nameOfVarBySimulator = getNameOfVarBySimulator(nameAccordingToClientAndValue.first,
                                                                  parametersToConnect->symbolTableForConnection);
            // remove the sim" from beginning and " from end
            nameOfVarBySimulator = nameOfVarBySimulator.substr(4, nameOfVarBySimulator.length() - 2);
           string message =
                    "set " + nameOfVarBySimulator + " " + to_string(nameAccordingToClientAndValue.second) + "\r\n";
            cout << message << endl;
            write(parametersToConnect->clientSocket, message.c_str(), message.length());
            pthread_mutex_unlock(parametersToConnect->mutex);
        }
    }
}

// returns the mame of the variable according to the simulator by the name according to the client
string getNameOfVarBySimulator(const string nameAccordingToClientAndValue, SymbolTable* symbolTable) {
    unordered_map<string, Variable*> nameToVariableMap = symbolTable->getMap();
    Variable *var = (nameToVariableMap)[nameAccordingToClientAndValue];
    return var->getName();
}
