#ifndef UNTITLED8_LEXER_H
#define UNTITLED8_LEXER_H

#define SPACE " "

#define ONE_CHAR_OPERATOR {"+","-","*","/", "\"","<",">","<=",">=","==","=","->","<-","(", ")"}
#define TWO_CHAR_OPERATOR {"+=","-=","*=","/=","==","->","<-"}


#include <vector>
#include <string>
#include <fstream>
#include <iostream>



using namespace std;

class Lexer{
    vector<string> m_vec;
    string parseApostrophes(string word);
    void lexStr(string &str);
    void getSpace(string &str);
    void rearrangeVec();

public:
    Lexer(){}
    vector<string> lexer(string fileName);
};




#endif //UNTITLED8_LEXER_H

