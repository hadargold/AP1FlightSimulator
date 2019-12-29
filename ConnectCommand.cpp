
#include "ConnectCommand.h"
#include "VariableManager.h"
#include "interpreter.h"
//change this define!!!!!!!
#define PORT 8081

void ConnectCommand:: execute(int& index) {
    Interpreter *stringToInterpretForPort= new Interpreter();
    VariableManager variableManager = new VariableManager();
    stringToInterpretForPrinting.setVariablesByMapOfVars(variableManager.getVarList());
    Expression *expressionToPrint = stringToInterpretForPort->interpret(strPort);
    int port = expressionToPrint->calculate();


    pthread_t thread;
    // parameters contains the parameters to the createConnectString
    pthread_create(&thread, nullptr, createConnect, parameters);
    *index += 2;
}



void* ConnectCommand::createConnect(void* parameters) {
    //create socket
    int client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket == -1) {
        //error
        std::cerr << "Could not create a socket"<<std::endl;
        return -1;
    }

    //We need to create a sockaddr obj to hold address of server
    sockaddr_in address; //in means IP4
    address.sin_family = AF_INET;//IP4
    address.sin_addr.s_addr = inet_addr("127.0.0.1");  //the localhost address
    address.sin_port = htons(PORT);
    //we need to convert our number (both port & localhost)
    // to a number that the network understands.

    // Requesting a connection with the server on local host with port 8081
    int is_connect = connect(client_socket, (struct sockaddr *)&address, sizeof(address));
    if (is_connect == -1) {
        std::cerr << "Could not connect to host server"<<std::endl;
        return -2;
    } else {
        std::cout<<"Client is now connected to server" <<std::endl;
    }
    // the client noe is connected to the server
    // now the client need to send flight instructions to the server


    // this is of vered!! change it!
    while (true) {
        if (params->data->sendNotEmpty()) {

            // parameters to send
            map<string, double> toSend = params->data->getSend();
            string path = params->data->getBind(toSend.begin()->first);
            double value = toSend.begin()->second;

            // creating the message
            string message = "set " + path + " " + to_string(value) + "\r\n";

            ssize_t n;

            // Send message to the server
            n = write(sockfd, message.c_str(), message.length());

            if (n < 0) {
                break;
            }
        }
    }
}