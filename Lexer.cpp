#include "Lexer.h"

// translate the file to the string
vector<string> Lexer::lexerToTextFile(const string &lexer) {
    // empty string
    string allFile = "";
    // vector string that we will returned.
    vector<string> lines;
    // the file
    fstream file;
    // lines from the text
    // temp string
    string temp;
    // if it's not open open it.
    if (!file.is_open()) {
        file.open(lexer, fstream::app | fstream::in);
    }
    // get line from the file
    string lineFromText ="";
    while (getline(file, lineFromText)) {
        // if it's not empty
        if(regex_match(lineFromText,regex("="))) {
            allFile.append(lineFromText.substr(0, 1) + ",");
            allFile.append(lineFromText.substr(1, lineFromText.length()-1));
        }
        if (allFile != "") {
            // adding space and the string
            allFile.append(" ");
        }
        allFile.append(lineFromText);
    }
    // after put all the file on the string, we now using spacer to split the whole string , that every symbol will be
    // in a cell on the vector
    spacer(allFile);
    // close the file.
    file.close();
    // split the file by space
    lines = splitLine(allFile);
    // special case to avoid segmantion,
    int some;
    for(auto it = lines.begin(); it != lines.end();it++) {
        string findIfChar = *it;
        if (findIfChar.length() < 2) {
            some = findIfChar[0];
            if (some == 0) {
                lines.erase(it);
                it--;
            }
        }
    }
    return lines;
}
// if it's number
bool Lexer::ifNumber(char ch) {
    return !(ch < '0' || ch > '9');
}
// if it's left parentheses
bool Lexer::isLeftParentheses(char parentheses) {
    return parentheses == '(';
}
// if it's operator
bool Lexer::isOperator(char operation) {
    switch (operation) {
        case ',':
            return true;
        case '+':
            return true;
        case '-':
            return true;
        case '*':
            return true;
        case '/':
            return true;
        case '=':
            return true;
        case '<':
            return true;
        case '>':
            return true;
        case '!':
            return true;
        default:
            return false;
    }
}
// same only for string
bool Lexer::isStrOp(string op) {
    if(op == "+" || op == "-" || op == "*" || op == "/" ||
       op == "==" || op == "!=")
        return true;
    else
        return false;
}
// if it's right parenthese
bool Lexer::isRightParentheses(char parnthese) {
    return parnthese == ')';
}
// makes the sapce
void Lexer::spacer(string &st) {
    bool gersh = false;
    for (unsigned i = 0; i < st.length(); i++) {
        if (!gersh && st[i] == '\"')
            gersh = true;
        else if (gersh && st[i] == '\"')
            gersh = false;
        // Spaces.
        if (st[i] == ' ') {
            continue;
        }
        // Operators And Brackets.
        if ((isOperator(st[i]) || isLeftParentheses(st[i]) || isRightParentheses(st[i])) && !gersh) {
            if (st.length() != i + 1 && ' ' != st[i + 1]) {
                string rep = " ";
                rep.append(1, st[i + 1]);
                st.replace(i + 1, 1, rep);
            }
            continue;
        }
        // Numbers.
        if (ifNumber(st[i])) {
            while (++i != st.length()) {
                if (!ifNumber(st[i]) && st[i] != '.' && !gersh) {
                    if (st[i] != ' ') {
                        string rep = " ";
                        rep.append(1, st[i]);
                        st.replace(i, 1, rep);
                    }
                    break;
                }
            }
            continue;
        }
            // Vars.
        else {
            while (++i != st.length()) {
                if (((isOperator(st[i]) || st[i] == ' ' || isRightParentheses(st[i]))
                     || isLeftParentheses(st[i]))&& !gersh || (st[i] == '\"' && gersh)) {
                    if (st[i] == '\"' && gersh) {
                        i++;
                        gersh = false;
                    }
                    if (st[i] != ' ') {
                        string rep = " ";
                        rep.append(1, st[i]);
                        st.replace(i, 1, rep);
                    }
                    break;
                }
            }
            continue;
        }
    }
}

vector<string> Lexer::splitLine(const string &line) {
    //function to split the line by spaces.
    stringstream splitter(line);
    istream_iterator<string> begin(splitter);
    istream_iterator<string> end;
    vector<string> vstrings(begin, end);
    int j = 0;
    for (auto i = vstrings.begin(); i != vstrings.end(); ++i) {
        if (((vstrings[j] == "-") && (vstrings[j + 1] == ">"))
            || ((vstrings[j] == "<") && (vstrings[j + 1] == "-"))
            || ((vstrings[j] == "+") && (vstrings[j + 1] == "="))
            || ((vstrings[j] == "-") && (vstrings[j + 1] == "="))
            || ((vstrings[j] == "*") && (vstrings[j + 1] == "="))
            || ((vstrings[j] == "/") && (vstrings[j + 1] == "="))
            || ((vstrings[j] == "<") && (vstrings[j + 1] == "="))
            || ((vstrings[j] == ">") && (vstrings[j + 1] == "="))){
            vstrings[j] = vstrings[j] + vstrings[j+1];
            vstrings.erase(i+1);
        }
        if(regex_match(vstrings[j],regex("\".*")) && !regex_match(vstrings[j],regex(".*\""))){

            j++;
            while(!regex_match(vstrings[j],regex(".*\"")))
            {
                vstrings[j-1] = vstrings[j-1] + " " + vstrings[j];
                vstrings.erase(i+1);
            }
            vstrings[j-1] = vstrings[j-1] + " " + vstrings[j];
            vstrings.erase(i+1);
            j--;
        }

        if(vstrings[j-1] == "="){
            // deal with ()
            j++;
            bool flag = false;
            while(((isStrOp(vstrings[j])) && !isStrOp(vstrings[j+1])) ||
                  ((isStrOp(vstrings[j+1])) && !isStrOp(vstrings[j])))
            {
                vstrings[j-1] = vstrings[j-1] + vstrings[j];
                vstrings.erase(i+1);
                flag = true;
            }
            if(flag){
                vstrings[j - 1] = vstrings[j - 1] + vstrings[j];
                vstrings.erase(i + 1); }
            j--;
        }
        if(vstrings[j+1] == ","){ // there is ,
            vstrings.erase(i+1);
        }
        j++;
    }
    for (auto i = vstrings.begin(); i != vstrings.end(); ++i)
        std::cout << *i + ','<< ' ';
    return vstrings;
}