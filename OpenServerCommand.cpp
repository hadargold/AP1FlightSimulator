//
// Created by hadar on 12/22/19.
//

#include "OpenServerCommand.h"
#include <thread>
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

OpenServerCommand :: OpenServerCommand(string strPort, SymbolTable* symbolTable) {
    // change the port to int
    auto *stringToInterpretForPort= new Interpreter();
    stringToInterpretForPort->setVariablesByMapOfVars(symbolTable->getMap());
    Expression *expressionToPrint = stringToInterpretForPort->interpret(strPort);
    int intPort = (int) expressionToPrint->calculate();
    this->port = intPort;
    this->symbolTable = symbolTable;
}

struct parameters {
    SymbolTable* symbolTableToConnect;
    int clientSocket;
    int portToconnect;
};

void OpenServerCommand:: execute(int* index) {
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
    address.sin_port = htons(this->port);
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
    int client_socket = accept(socketfd, (struct sockaddr *) &address, (socklen_t * ) & address);

    if (client_socket == -1) {
        std::cerr << "Error accepting client" << std::endl;
        exit(1);
    } else {
        cout << "server connected" << endl;
    }

    close(socketfd); //closing the listening socket

    // parameters contains the parameters to the createConnectString
    struct parameters *parametersToOpenDataServer;
    parametersToOpenDataServer = new parameters();
    parametersToOpenDataServer->portToconnect = this->port;
    parametersToOpenDataServer->clientSocket = client_socket;
    parametersToOpenDataServer->symbolTableToConnect = this->symbolTable;
    pthread_t thread;
    pthread_create(&thread, nullptr, OpenServerCommand::openDataServer, parametersToOpenDataServer);
    *index += 3;
}

void* OpenServerCommand::openDataServer(void* arguments) {
    struct parameters* parametersToOpenDataServer = (struct parameters*) arguments;
    //reading from client
    //while (true) {
    string stringOfValuesFromSim = "";
    char buffer[1024] = {0};
    //valread is 0 if there is no data to read. -1 is there was an erroe
    int valread = read(parametersToOpenDataServer->clientSocket, buffer, 1024);
    if (valread > 0) {
        for (int i = 0; i < valread; i++) {
            char c = buffer[i];
            // if this is the end of the values (36 values)
            if (c == '\n') {
                if (stringOfValuesFromSim.length() > 0) {
                    vector <string> splitValues = splitByComma(stringOfValuesFromSim);
                    parametersToOpenDataServer->symbolTableToConnect->addValuesFromSimToSymbolTable(splitValues);
                    stringOfValuesFromSim = "";
                }
            } else stringOfValuesFromSim += c;
        }
    }
}

//void OpenServerCommand:: execute(int* index) {
//
//    int socketFd; // main socket fileDescriptor
//    int newsockfd; // new socket fileDescriptor
//    int clilen;
//
//    struct sockaddr_in serv_addr, cli_addr;
//
//    //creating socket object
//    socketFd = socket(AF_INET, SOCK_STREAM, 0);
//    //if creation faild
//    if (socketFd < 0) {
//        perror("ERROR opening socket");
//        exit(1);
//    }
//
//
//    //Initialize socket structure
//    bzero((char *) &serv_addr, sizeof(serv_addr));
//
//    serv_addr.sin_family = AF_INET; // tcp server
//    serv_addr.sin_addr.s_addr = INADDR_ANY; //server ip (0.0.0.0 for all incoming connections)
//    serv_addr.sin_port = htons(port); //init server port
//
//    //bind the host address using bind() call
//    if (bind(socketFd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
//        //if binding faild
//        perror("ERROR on binding");
//        exit(1);
//    }
//
//
//    //start listening for the clients using the main socket
//    listen(socketFd,1);
//    clilen = sizeof(cli_addr);
//    cout << "listening" <<endl;
//
//    //accept actual connection from the client
//    newsockfd = accept(socketFd, (struct sockaddr*)&cli_addr, (socklen_t*)&clilen);
//    cout << "im the one doesnt need a gun to get respect on the street";
//
//    //if connections with the client failed
//    if (newsockfd < 0) {
//        perror("ERROR on accept");
//        exit(1);
//    }
//
//    *index +=3;
//}







//void updateValuesInSymbolTable(const string stringOfValuesFromSim, SymbolTable*) {
//    vector <string> splitValues = splitByComma(stringOfValuesFromSim);
//    this->symbolTable->addValuesFromSimToSymbolTable(splitValues);
//}

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








//
////
//// Created by hadar on 12/22/19.
////
//
//#include "OpenServerCommand.h"
//#include <thread>
//#include <sys/socket.h>
//#include <iostream>
//#include <netinet/in.h>
//#include <unistd.h>
//#include "VariableManager.h"
//#include "Interpreter.h"
//#include "ConnectCommand.h"
//#include <regex>
//#include <complex>
//#include "SymbolTable.h"
//
//void updateValuesInSymbolTable(string stringOfValuesFromSim);
//vector <string> splitByComma(string stringOfValuesFromSim);
//
//OpenServerCommand :: OpenServerCommand(string strPort) {
//    // change the port to int
//    auto *stringToInterpretForPort= new Interpreter();
//    SymbolTable *symbolTable = new SymbolTable();;
//    stringToInterpretForPort->setVariablesByMapOfVars(symbolTable->getMap());
//    Expression *expressionToPrint = stringToInterpretForPort->interpret(strPort);
//    int intPort = (int) expressionToPrint->calculate();
//    this->port = intPort;
//}
//
//struct parameters {
//    int portToconnect;
//};
//
//void OpenServerCommand:: execute(int* index) {
//    // parameters contains the parameters to the createConnectString
//    struct parameters *parametersToOpenDataServer;
//    parametersToOpenDataServer = new parameters();
//    parametersToOpenDataServer->portToconnect = this->port;
//    pthread_t thread;
//    pthread_create(&thread, nullptr, OpenServerCommand::openDataServer, parametersToOpenDataServer);
//    *index += 1;
//}
//
//void* OpenServerCommand::openDataServer(void* arguments) {
//    struct parameters* parametersToOpenDataServer = (struct parameters*) arguments;
//    //create socket
//    int socketfd = socket(AF_INET, SOCK_STREAM, 0);
//    if (socketfd == -1) {
//        //error
//        std::cerr << "Could not create a socket" << std::endl;
//        exit(1);
//    }
//
//    //bind socket to IP address
//    // we first need to create the sockaddr obj.
//    sockaddr_in address; //in means IP4
//    address.sin_family = AF_INET;
//    address.sin_addr.s_addr = INADDR_ANY; //give me any IP allocated for my machine
//    address.sin_port = htons(parametersToOpenDataServer->portToconnect);
//    //we need to convert our number
//    // to a number that the network understands.
//
//    //the actual bind command
//    if (bind(socketfd, (struct sockaddr *) &address, sizeof(address)) == -1) {
//        std::cerr << "Could not bind the socket to an IP" << std::endl;
//        exit(1);
//    }
//
//    //making socket listen to the port
//    if (listen(socketfd, 5) == -1) { //can also set to SOMAXCON (max connections)
//        std::cerr << "Error during listening command" << std::endl;
//        exit(1);
//    } else {
//        std::cout << "Server is now listening ..." << std::endl;
//    }
//
//    // accepting a client
//    int client_socket = accept(socketfd, (struct sockaddr *) &address,
//                               (socklen_t * ) & address);
//
//    if (client_socket == -1) {
//        std::cerr << "Error accepting client" << std::endl;
//        exit(1);
//    } else {
//        cout << "server connected" << endl;
//    }
//
//    close(socketfd); //closing the listening socket
//
//    //reading from client
//    while (true) {
//        string stringOfValuesFromSim = "";
//        char buffer[1024] = {0};
//        //valread is 0 if there is no data to read. -1 is there was an erroe
//        int valread = read(client_socket, buffer, 1024);
//        if (valread > 0) {
//            for (int i = 0; i < valread; i++) {
//                char c = buffer[i];
//                // if this is the end of the values (36 values)
//                if (c == '\n') {
//                    if (stringOfValuesFromSim.length() > 0) {
//                        updateValuesInSymbolTable(stringOfValuesFromSim);
//                        stringOfValuesFromSim = "";
//                    }
//                } else stringOfValuesFromSim += c;
//            }
//        }
//    }
//}
//
//void updateValuesInSymbolTable(const string stringOfValuesFromSim) {
//    vector <string> splitValues = splitByComma(stringOfValuesFromSim);
//    auto *symbolTable = new SymbolTable();
//    symbolTable->addValuesFromSimToSymbolTable(splitValues);
//}
//
//vector <string> splitByComma(string stringOfValuesFromSim) {
//    vector <string> splitValues;
//    regex r("[^,]+");
//    std::smatch match;
//    while (regex_search(stringOfValuesFromSim, match, r)) {
//        string str = match[0];
//        splitValues.push_back(str);
//        // the index of the matching
//        int indexOfMatching = match.position();
//        // search again on the continue of the string
//        stringOfValuesFromSim = stringOfValuesFromSim.substr(indexOfMatching + match.length());
//    }
//    return splitValues;
//}
