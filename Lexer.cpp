#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include "Lexer.h"
#include <regex>
#define TXT "txt"

using namespace std;
/**
 * the function out the apostrophes.
 * @param word the word has apostrophes.
 * @return the word without apostrophes.
 */
string Lexer::parseApostrophes(string word){
    int lenghChar=1;
    char delimiter ='\"';
    word.erase(0, word.find(delimiter) + lenghChar);
    word.erase(word.size()-lenghChar, word.find(delimiter) + lenghChar);
    return word;
}
void Lexer::getSpace(string &str) {
    string ans;
    string ch;
    vector<string> one_char_operators = ONE_CHAR_OPERATOR;
    vector<string> two_char_operators = TWO_CHAR_OPERATOR;
    bool is_quotation = false;
    string::iterator it;
    for (it = str.begin(); it != str.end(); ++it) {
        ch = *it;
        if (ch == "\"") {
            is_quotation = !is_quotation;
            ans += ch;
            continue;
        }
        if ((find(one_char_operators.begin(), one_char_operators.end(), ch) != one_char_operators.end()) &&
            !is_quotation) {
            string to_replace = " " + ch + " ";
            ans += to_replace;
        } else {
            ans += ch;
        }
    }
    str = ans;
}

void Lexer::rearrangeVec(){
    int j = 0;
    vector<string> one_char_operators = ONE_CHAR_OPERATOR;
    for (auto i = this->m_vec.begin(); i != this->m_vec.end(); ++i) {
        if (((this->m_vec[j] == "-") && (this->m_vec[j + 1] == ">"))
            || ((this->m_vec[j] == "<") && (this->m_vec[j + 1] == "-"))
               || ((this->m_vec[j] == "+") && (this->m_vec[j + 1] == "="))
                  || ((this->m_vec[j] == "-") && (this->m_vec[j + 1] == "="))
                     || ((this->m_vec[j] == "*") && (this->m_vec[j + 1] == "="))
                        || ((this->m_vec[j] == "/") && (this->m_vec[j + 1] == "="))){
            this->m_vec[j] = this->m_vec[j] + this->m_vec[j+1];
            this->m_vec.erase(i+1);
        }
        if (this->m_vec[j] == "sim"){
            if(this->m_vec[j+1] == "("){
                this->m_vec.erase(i+1);
            }
            this->m_vec[j] = this->m_vec[j] + '"' + this->m_vec[j+1] + '"';
            this->m_vec.erase(i+1);
        }
        if (this->m_vec[j] == "+" || this->m_vec[j] == "-" || this->m_vec[j] == "*" ||
                this->m_vec[j] == "/"){
            this->m_vec[j] = this->m_vec[j-1] + this->m_vec[j] + this->m_vec[j+1];
            this->m_vec.erase(i+1);
            this->m_vec.erase(i-1);
        }
        // check print
        bool flag = true;
        string toPrint = "";
        if (this->m_vec[j] == "print"){
            while(flag){
                string str = m_vec[j+2];
                int saveJ = j+1;
                if(str[str.length()] == '"'){
                    this->m_vec[j+2] = str.substr(0,str.length()-1);
                    this->m_vec[j+1] += this->m_vec[j+2];
                    flag = false;
                    this->m_vec.erase(i+2);
                    i++;
                }
            }
        }
        if (this->m_vec[j] == "(" || this->m_vec[j] == ")"){
            this->m_vec.erase(i);
        }
        j++;
    }

}

void Lexer::lexStr(string &str){
    getSpace(str);
    bool flag = false;
    string line;
    string delimiter=SPACE;
    while(!str.empty()) {
        line=str.substr(0, str.find(delimiter));
        if(line == "print"){
            flag = true;
        }
        if (line[0]=='\"' && !flag){
            line=parseApostrophes(line);
        }
        if(line.empty()){
            str.erase(0, str.find(delimiter) + delimiter.length());
            continue;
        }

        this->m_vec.push_back(line);
        if(str.find(delimiter)==string::npos){
            str="";
        } else {
            str.erase(0, str.find(delimiter) + delimiter.length());
        }
    }
}


/**
 * the function get file or string and lexer it in the space and push every string to vector.
 * at the end of the function got vector of strings.
 * @param fileName file or string
 * @return vector of string.
 */
vector<string> Lexer:: lexer(string fileName) {
    //the function check if he got file or string
    fileName = "openDataServer(5400)\n"
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
               "var heading <- sim(\"/instrumentation/heading-indicator/offset-deg\")\n"
               "var airspeed <- sim(\"/instrumentation/airspeed-indicator/indicated-speed-kt\")\n"
               "var roll <- sim(\"/instrumentation/attitude-indicator/indicated-roll-deg\")\n"
               "var pitch <- sim(\"/instrumentation/attitude-indicator/internal-pitch-deg\")\n"
               "var rudder -> sim(\"/controls/flight/rudder\")\n"
               "var aileron -> sim(\"/controls/flight/aileron\")\n"
               "var elevator -> sim(\"/controls/flight/elevator\")\n"
               "var alt <- sim(\"/instrumentation/altimeter/indicated-altitude-ft\")\n"
               "var rpm <- sim(\"/engines/engine/rpm\")\n"
               "Print(\"waiting 2 minutes for gui\")\n"
               "Sleep(120000)\n"
               "Print(\"let's start\")\n"
               "warp = 32000\n"
               "Sleep(1000)\n"
               "magnetos = 3\n"
               "throttle = 0.2\n"
               "mixture = 0.949\n"
               "masterbat = 1\n"
               "masterlat = 1\n"
               "masteravionics = 1\n"
               "brakeparking = 0\n"
               "primer = 3\n"
               "starter = 1\n"
               "autostart = 1\n"
               "Print(\"engine is warming...\")\n"
               "Print(rpm)\n"
               "while rpm <= 750 {\n"
               "\tPrint(rpm)\n"
               "}\n"
               "Sleep(5000)\n"
               "Print(\"let's fly\")\n"
               "var h0 = heading\n"
               "breaks = 0\n"
               "throttle = 1\n"
               "while alt < 1000 {\n"
               "\trudder = (h0 - heading)/80\n"
               "\taileron = -roll / 70\n"
               "\televator = pitch / 50\n"
               "\tSleep(250)\n"
               "}\n"
               "Print(\"done\")";
    if (fileName.find(TXT) != string::npos) {
        ifstream in;
        string line;
        in.open(fileName);
        if (!in.is_open()) {
            cout << "error while opening the file\n";
            exit(0);
        }
        while (!in.eof()) {
            getline(in, line);
            if(line == "\n" || line.empty()){
                continue;
            }
            bool temp = false;
            if(line[0] == '}')
                temp = true;

            lexStr(line);
            if(temp) {
                this->m_vec.push_back("$");
                temp = false;
            }
            this->m_vec.push_back("\n");
        }
        in.close();
    } else{
        if(fileName != "\n"){
            lexStr(fileName);
        }
        this->m_vec.push_back("\n");


    }
    this->m_vec.push_back("$");
    rearrangeVec();
    return this->m_vec;
}

