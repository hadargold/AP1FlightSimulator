#ifndef EX3_VARIABLEMANAGER_H
#define EX3_VARIABLEMANAGER_H

#include <vector>
#include "ex1.h"

class VariableManager {
private:
    vector<Variable> variablesList;
public:
    void addToVarList(string name, double value);
    vector <Variable> getVarList();
};
#endif //EX3_VARIABLEMANAGER_H