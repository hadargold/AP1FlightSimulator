#ifndef PROJECT_LEXER_H
#define PROJECT_LEXER_H
using namespace std;
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <regex>
#include "Parser.h"
//
//#define ONE_CHAR_OPERATOR {"+","-","*","/", "\"","<",">","<=",">=","==","=","->","<-","(", ")"}
//#define TWO_CHAR_OPERATOR {"+=","-=","*=","/=","==","->","<-"}
//
class Lexer {

public:
//    // get the lines from the file.
    vector<string> lexerToTextFile(string lexer);
    string remove(string s);
    void checkCondition(vector<string> *lines, string condition);
    void assign(vector<string> *lines, string condition);

    ///////////////////////////////////////////////////////

//    // split by " " and string.
//    vector<string> splitLine(const string& line);
//    vector<string> rearrangeVec(vector<string> vstrings);
//    // function that split all the string by " ".
//    void spacer(string &after);
//    // if it's number
//    bool ifNumber(char number);
//    // if it's '('
//    bool isLeftParentheses(char parentheses);
//    // if it's ')'
//    bool isRightParentheses(char parnthese);
//    // if it's operator.
//    bool isOperator(char operation);
//
//    bool isSavedWord(string word);
//
//    bool isStrOp(string operation);
};

#endif //PROJECT_LEXER_H
