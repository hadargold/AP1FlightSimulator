#ifndef UNTITLED8_LEXER_H
#define UNTITLED8_LEXER_H

#define SPACE " "

#define ONE_CHAR_OPERATOR {"+","-","*","/", "\"","<",">","<=",">=","==","=","->","<-","(", ")"}
#define TWO_CHAR_OPERATOR {"+=","-=","*=","/=","==","->","<-"}


#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <regex>

using namespace std;

class Lexer{
    // vector<string> m_vec;
    string parseApostrophes(string word);
    void lexStr(string &str);
    void getSpace(string &str);
    void rearrangeVec(vector<string> m_vec);
    void spacer(string &st);
    vector<string> splitLine(const string &line);
    bool ifNumber(char ch);
    bool isLeftParentheses(char parentheses);
    bool isOperator(char operation);
    bool isRightParentheses(char parnthese);
public:
    Lexer(){}
    vector<string> lexer(string fileName);

    vector<string> lexerToTextFile(const string &lexer);
};




#endif //UNTITLED8_LEXER_H