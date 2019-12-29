#include <iostream>
#include "Lexer.h"
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>
#include "CommandsManager.h"
#include "Parser.h"





int main(){
        // check the number of arguments is valid
        //if (argc == 2) {
//            vector<string> a = lexer(argFiles[1]);
//            CommandsManager *commandsManager = new CommandsManager();
//            parser(commandsManager, a);
//            delete (commandsManager);
        //} else {
         //   throw "Invalid main";
        //}

//    std::istream *input_stream = new ifstream("temp",  std::ifstream::in);
//    std::string line;
//    getInputs(input_stream);
//    char c = input_stream.getline();
//    cout<<c;
//    std::getline(input,line);
    //std::ifstream input("fly.txt".c_str());
//    std::string buffer;
//    std::string result;
//    while (getline(*input_stream, result)) {
//        cout<<result<<endl;
//        }


    //if (!input.fail()) // if input does not fail
    //{
//
//        while (!input.eof())
//        {
//            std::getline(input, buffer);
//            result.append(buffer);
//        }
//        input.close();
    //}
//    std::string fileName = "fly.txt";
//    std::fstream readFile("fly.txt", std::ios::in);
//    std::string result;
//    while(!readFile.eof()){
//    std::getline(readFile, result);
//        cout<<result<<endl;
//    }
//    cout<<result<<endl;

    string result = "openDataServer(5400)\n"
                    "connectControlClient(\"127.0.0.1\",5402)\n"
                    "var warp -> sim(\"/sim/time/warp\")\n"
                    "var magnetos -> sim(\"/controls/switches/magnetos\")\n"
                    "var throttle -> sim(\"/controls/engines/current-engine/throttle\")\n"
                    "var mixture -> sim(\"/controls/engines/current-engine/mixture\")\n"
                    "var masterbat -> sim(\"/controls/switches/master-bat\")\n"
                    "var masterlat -> sim(\"/controls/switches/master-alt\")\n"
                    "var masteravionics -> sim(\"/controls/switches/master-avionics\")\n"
                    "var brakeparking -> sim(\"/sim/model/c172p/brake-parking\")\n"
                    "var primer -> sim(\"/controls/engines/engine/primer\")\n"
                    "var starter -> sim(\"/controls/switches/starter\")\n"
                    "var autostart -> sim(\"/engines/active-engine/auto-start\")\n"
                    "var breaks -> sim(\"/controls/flight/speedbrake\")\n"
                    "var heading <- sim(\"/instrumentation/heading-indicator/offset-deg\")";

    Lexer *l= new Lexer();
    vector <string> lexerVec = l->lexer("fly.txt");
        for (auto i = lexerVec.begin(); i != lexerVec.end(); ++i)
            std::cout << *i + ','<< ' ';

//    string result = "opEn(22)";
//    Lexer * l= new Lexer(result);
//    vector <string> vec = l->splitLine(result);
//    for (auto i = vec.begin(); i != vec.end(); ++i)
//        std::cout << *i + ','<< ' ';

//yuval:
    CommandsManager *commandsManager = new CommandsManager();
    Parser *parser = new Parser();
    vector <string> lexerForTest;
    lexerForTest.push_back("openDataServer");
    lexerForTest.push_back("5400");
    lexerForTest.push_back("connectControlClient");
    lexerForTest.push_back("127.0.0.1");
    lexerForTest.push_back("5402");
    lexerForTest.push_back("var");
    lexerForTest.push_back("warp");
    lexerForTest.push_back("->");
    lexerForTest.push_back("sim\"/sim/time/warp\"");
    //cout << "sim\"/sim/time/warp\"" << endl;
    int i = 0;
    parser->parse(commandsManager,lexerForTest);

// test openDataServer:
//    vector <string> lexerForTest;
//   lexerForTest.push_back("connectControlClient");
//    lexerForTest.push_back("127.0.0.1");
//   lexerForTest.push_back("5402");
//    int i = 0;
//    //commandsManager -> commandsFactory(lexerVec, i);
//    Command *c = commandsManager -> commandsFactory(lexerVec, i);
//    c->execute(&i);



    return 0;
}