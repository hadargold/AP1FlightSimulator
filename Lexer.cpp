#include "Lexer.h"

vector<string> Lexer::lexerToTextFile(string fileName) {
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
    file.open(fileName, fstream::app | fstream::in);
  }
  // get line from the file
  string lineFromText;
  string shirshur = "";
  bool flag = false;
  int index;
  while (getline(file, lineFromText)) {
    lineFromText = remove(lineFromText);
    index = lineFromText.find("openDataServer");
    if (index < lineFromText.length()) {
      lines.push_back("openDataServer");
      lines.push_back("(");
      lines.push_back(lineFromText.substr(index + 15, lineFromText.length() - index - 16));
      lines.push_back(")");
      continue;
    }
    index = lineFromText.find("connectControlClient");
    if (index < lineFromText.length()) {
      lines.push_back("connectControlClient");
      lines.push_back("(");
      string substr = lineFromText.substr(21, lineFromText.length() - 21);
      int index2 = substr.find(",");
      string ip = substr.substr(0, index2);
      string port = substr.substr(index2 + 1, substr.length() - index2 - 2);
      lines.push_back(ip);
      lines.push_back(port);
      lines.push_back(")");
      continue;
    }
    index = lineFromText.find("Sleep");
    if (index < lineFromText.length()) {
      lines.push_back("Sleep");
      lines.push_back("(");
      string substr = lineFromText.substr(6, lineFromText.length() - 7);
      lines.push_back(substr);
      lines.push_back(")");
      continue;
    }
    index = lineFromText.find("Print");
    if (index < lineFromText.length()) {
      lines.push_back("Print");
      lines.push_back("(");
      string substr = lineFromText.substr(6, lineFromText.length() - 7);
      lines.push_back(substr);
      lines.push_back(")");
      continue;
    }
    index = lineFromText.find("->");
    if (index < lineFromText.length()) {
      lines.push_back("var");
      string name = lineFromText.substr(3, index - 3);
      lines.push_back(name);
      lines.push_back("->");
      lines.push_back(lineFromText.substr(index + 2, lineFromText.length() - index - 2));
      continue;
    }
    index = lineFromText.find("<-");
    if (index < lineFromText.length()) {
      lines.push_back("var");
      string name = lineFromText.substr(3, index - 3);
      lines.push_back(name);
      lines.push_back("<-");
      lines.push_back(lineFromText.substr(index + 2, lineFromText.length() - index - 2));
      continue;
    }
    index = lineFromText.find("var");
    if (index < lineFromText.length()) {
      lines.push_back("var");
      int index2 = lineFromText.find("=");
      string name = lineFromText.substr(index+3, index2-3);
      lines.push_back(name);
      lines.push_back("=");
      string exp2 = lineFromText.substr(index2+1, lineFromText.length() - index2 - 1);
      lines.push_back(exp2);
      continue;
    }
    index = lineFromText.find("while");
    if (index < lineFromText.length()) {
      lines.push_back("while");
      checkCondition(&lines, lineFromText.substr(5, lineFromText.length() - 5));
      continue;
    }
    index = lineFromText.find("if");
    if (index < lineFromText.length()) {
      lines.push_back("if");
      checkCondition(&lines, lineFromText.substr(2, lineFromText.length() - 2));
      continue;
    }
    if (lineFromText == "}") {
      lines.push_back("}");
    }
    if (lineFromText == "{") {
      lines.push_back("{");
    }
    index = lineFromText.find("=");
    if (index < lineFromText.length()) {
      assign(&lines, lineFromText);
      continue;
    }

  }
  //for (auto i = lines.begin(); i != lines.end(); ++i)
    //std::cout << *i + ','<< ' ';
  return lines;
}

string Lexer:: remove(string s) {
  string noSpaces = "";
  for (int i = 0; i < s.length(); i++) {
    if ( s[i] == '"') {
      noSpaces += s[i];
      i++;
      while (s[i] != '"') {
        noSpaces += s[i];
        i++;
      }
    }
    if (s[i] != ' ' && s[i] != '\t') {
      noSpaces += s[i];
    }
  }
  return noSpaces;
}

void Lexer:: checkCondition(vector<string> *lines, string condition) {
  string exp1, exp2;
  int index = condition.find("<=");
  if(index < condition.length()) {
    exp1 = condition.substr(0, index);
    lines->push_back(exp1);
    lines->push_back("<=");
    exp2 = condition.substr(index + 2, condition.length() - index - 3);
    lines->push_back(exp2);
    lines->push_back("{");
    return;
  }
  index = condition.find(">=");
  if(index < condition.length()) {
    exp1 = condition.substr(0, index);
    lines->push_back(exp1);
    lines->push_back(">=");
    exp2 = condition.substr(index + 2, condition.length() - index - 3);
    lines->push_back(exp2);
    lines->push_back("{");
    return;
  }
  index = condition.find("==");
  if(index < condition.length()) {
    exp1 = condition.substr(0, index);
    lines->push_back(exp1);
    lines->push_back("==");
    exp2 = condition.substr(index + 2, condition.length() - index - 3);
    lines->push_back(exp2);
    lines->push_back("{");
    return;
  }
  index = condition.find(">");
  if(index < condition.length()) {
    exp1 = condition.substr(0, index);
    lines->push_back(exp1);
    lines->push_back(">");
    exp2 = condition.substr(index + 1, condition.length() - index - 2);
    lines->push_back(exp2);
    lines->push_back("{");
    return;
  }
  index = condition.find("<");
  if(index < condition.length()) {
    exp1 = condition.substr(0, index);
    lines->push_back(exp1);
    lines->push_back("<");
    exp2 = condition.substr(index + 1, condition.length() - index - 2); // maybe 1
    lines->push_back(exp2);
    lines->push_back("{");
    return;
  }
  index = condition.find("!=");
  if(index < condition.length()) {
    exp1 = condition.substr(0, index);
    lines->push_back(exp1);
    lines->push_back("!=");
    exp2 = condition.substr(index + 2, condition.length() - index - 3);
    lines->push_back(exp2);
    lines->push_back("{");
    return;
  }
  exp1 = condition.substr(0, condition.length() - 2);
  lines->push_back(exp1);
  lines->push_back("{");

}

void Lexer:: assign(vector<string> *lines, string condition) {
  string name, exp2;
  int index = condition.find("+=");
  if(index < condition.length()) {
    name = condition.substr(0, index);
    lines->push_back(name);
    lines->push_back("=");
    exp2 = condition.substr(index + 1, condition.length() - index - 3);
    lines->push_back(name+"+"+exp2);
    return;
  }
  index = condition.find("-=");
  if(index < condition.length()) {
    name = condition.substr(0, index);
    lines->push_back(name);
    lines->push_back("=");
    exp2 = condition.substr(index +1, condition.length() - index - 3);
    lines->push_back(name+"-"+exp2);
    return;
  }
  index = condition.find("/=");
  if(index < condition.length()) {
    name = condition.substr(0, index);
    lines->push_back(name);
    lines->push_back("=");
    exp2 = condition.substr(index + 1, condition.length() - index - 3);
    lines->push_back(name+"/"+exp2);
    return;
  }
  index = condition.find("*=");
  if(index < condition.length()) {
    name = condition.substr(0, index);
    lines->push_back(name);
    lines->push_back("=");
    exp2 = condition.substr(index + 1, condition.length() - index - 3);
    lines->push_back(name+"*"+exp2);
    return;
  }
  index = condition.find("=");
  if(index < condition.length()) {
    name = condition.substr(0, index);
    lines->push_back(name);
    lines->push_back("=");
    exp2 = condition.substr(index + 1, condition.length() - index - 1);
    lines->push_back(exp2);
    return;
  }
}

////////////////////////////////////////////////

//#include "Lexer.h"
//
//// translate the file to the string
//vector<string> Lexer::lexerToTextFile(const string &lexer) {
//    // empty string
//    string allFile = "";
//    // vector string that we will returned.
//    vector<string> lines;
//    // the file
//    fstream file;
//    // lines from the text
//    // temp string
//    string temp;
//    // if it's not open open it.
//    if (!file.is_open()) {
//        file.open(lexer, fstream::app | fstream::in);
//    }
//    // get line from the file
//    string lineFromText ="";
//    bool flag = false;
//    while (getline(file, lineFromText)) {
//        // if it's not empty
//        if (allFile != "") {
//            // adding space and the string
//            allFile.append(" ");
//        }
//        if(lineFromText.find("=")!=std::string::npos
//        && !(lineFromText.find("==")!=std::string::npos))
//        { allFile.append(lineFromText);
//            allFile.append(" @ ");
//            //flag = true;
//            //allFile.append(lineFromText.substr(0, 1) + ",");
//            //string WithoutSpace = lineFromText.substr(1, lineFromText.length()-1);
//        }
//        else
//            allFile.append(lineFromText);
//    }
//    // after put all the file on the string, we now using spacer to split the whole string , that every symbol will be
//    // in a cell on the vector
//    spacer(allFile);
//    // close the file.
//    file.close();
//    // split the file by space
//    lines = splitLine(allFile);
//    // special case to avoid segmantion,
//    int some;
//    for(auto it = lines.begin(); it != lines.end();it++) {
//        string findIfChar = *it;
//        if (findIfChar.length() < 2) {
//            some = findIfChar[0];
//            if (some == 0) {
//                lines.erase(it);
//                it--;
//            }
//        }
//    }
//    return lines;
//}
//// if it's number
//bool Lexer::ifNumber(char ch) {
//    return !(ch < '0' || ch > '9');
//}
//// if it's left parentheses
//bool Lexer::isLeftParentheses(char parentheses) {
//    return parentheses == '(';
//}
//// if it's operator
//bool Lexer::isOperator(char operation) {
//    switch (operation) {
//        case ',':
//            return true;
//        case '+':
//            return true;
//        case '-':
//            return true;
//        case '*':
//            return true;
//        case '/':
//            return true;
//        case '=':
//            return true;
//        case '<':
//            return true;
//        case '>':
//            return true;
//        case '!':
//            return true;
//        default:
//            return false;
//    }
//}
//// same only for string
//bool Lexer::isStrOp(string op) {
//    if(op == "+" || op == "-" || op == "*" || op == "/" ||
//       op == "==" || op == "!=")
//        return true;
//    else
//        return false;
//}
//// if it's right parenthese
//bool Lexer::isRightParentheses(char parnthese) {
//    return parnthese == ')';
//}
//// makes the sapce
//void Lexer::spacer(string &st) {
//    bool gersh = false;
//    for (unsigned i = 0; i < st.length(); i++) {
//        if (!gersh && st[i] == '\"')
//            gersh = true;
//        else if (gersh && st[i] == '\"')
//            gersh = false;
//        // Spaces.
//        if (st[i] == ' ') {
//            continue;
//        }
//        // Operators And Brackets.
//        if ((isOperator(st[i]) || isLeftParentheses(st[i]) || isRightParentheses(st[i])) && !gersh) {
//            if (st.length() != i + 1 && ' ' != st[i + 1]) {
//                string rep = " ";
//                rep.append(1, st[i + 1]);
//                st.replace(i + 1, 1, rep);
//            }
//            continue;
//        }
//        // Numbers.
//        if (ifNumber(st[i])) {
//            while (++i != st.length()) {
//                if (!ifNumber(st[i]) && st[i] != '.' && !gersh) {
//                    if (st[i] != ' ') {
//                        string rep = " ";
//                        rep.append(1, st[i]);
//                        st.replace(i, 1, rep);
//                    }
//                    break;
//                }
//            }
//            continue;
//        }
//            // Vars.
//        else {
//            while (++i != st.length()) {
//                if (((isOperator(st[i]) || st[i] == ' ' || isRightParentheses(st[i]))
//                     || isLeftParentheses(st[i]))&& !gersh || (st[i] == '\"' && gersh)) {
//                    if (st[i] == '\"' && gersh) {
//                        i++;
//                        gersh = false;
//                    }
//                    if (st[i] != ' ') {
//                        string rep = " ";
//                        rep.append(1, st[i]);
//                        st.replace(i, 1, rep);
//                    }
//                    break;
//                }
//            }
//            continue;
//        }
//    }
//}
//
//vector<string> Lexer::splitLine(const string &line) {
//    //function to split the line by spaces.
//    stringstream splitter(line);
//    istream_iterator<string> begin(splitter);
//    istream_iterator<string> end;
//    vector<string> vstrings(begin, end);
//    int j = 0;
//    for (auto i = vstrings.begin(); i != vstrings.end(); ++i) {
//        if (i == vstrings.end() -1) {
//            break;
//        }
//        if (((vstrings[j] == "-") && (vstrings[j + 1] == ">"))
//            || ((vstrings[j] == "<") && (vstrings[j + 1] == "-"))
//            || ((vstrings[j] == "+") && (vstrings[j + 1] == "="))
//            || ((vstrings[j] == "-") && (vstrings[j + 1] == "="))
//            || ((vstrings[j] == "*") && (vstrings[j + 1] == "="))
//            || ((vstrings[j] == "/") && (vstrings[j + 1] == "="))
//            || ((vstrings[j] == "<") && (vstrings[j + 1] == "="))
//            || ((vstrings[j] == ">") && (vstrings[j + 1] == "="))) {
//            vstrings[j] = vstrings[j] + vstrings[j + 1];
//            vstrings.erase(i + 1);
//        }
//        if (regex_match(vstrings[j], regex("\".*")) && !regex_match(vstrings[j], regex(".*\""))) {
//
//            j++;
//            while (!regex_match(vstrings[j], regex(".*\""))) {
//                vstrings[j - 1] = vstrings[j - 1] + " " + vstrings[j];
//                vstrings.erase(i + 1);
//            }
//            vstrings[j - 1] = vstrings[j - 1] + " " + vstrings[j];
//            vstrings.erase(i + 1);
//            j--;
//        }
//
//        if (vstrings[j - 1] == "=") {
//            j++;
//            bool flag = false;
//            while (vstrings[j] != "@") //((isStrOp(vstrings[j])) && !isStrOp(vstrings[j+1])) ||
////                  ((isStrOp(vstrings[j+1])) && !isStrOp(vstrings[j])) ||
////                  (isStrOp(vstrings[j]) && vstrings[j+1] == "(" && !isStrOp(vstrings[j+2]))
////                  || !(isStrOp(vstrings[j+1]) && vstrings[j+2] == ")"
////                  && isStrOp(vstrings[j]))
////                  )
//            {
//                vstrings[j - 1] = vstrings[j - 1] + vstrings[j];
//                vstrings.erase(i + 1);
//                flag = true;
//            }
////            if(flag){
////                vstrings[j - 1] = vstrings[j - 1] + vstrings[j];
////                vstrings.erase(i + 1); }
////                j--;
////            }
//            j--;
//        }
//        if (vstrings[j + 1] == "," || vstrings[j + 1] == "@") { // there is ,
//            vstrings.erase(i + 1);
//        }
//        j++;
//    }
//    for (auto i = vstrings.begin(); i != vstrings.end(); ++i)
//        std::cout << *i + ','<< ' ';
//    return vstrings;
//
//}
