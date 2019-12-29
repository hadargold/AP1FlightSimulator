//
// Created by hadar on 12/29/19.
//

#include "Condition.h"

void Condition::execute(int &it){
    if(condition.size() == 1)
    {
        this->result = (condition[0] == "1") ? true : false;
    }
    else {
        int i = 0;
        int conditionLocation;
        string left = "";
        string right = "";
        Expression *sideA, *sideB;
        while (condition[i] != "<" && condition[i] != ">"
        && condition[i] != "<=" && condition[i] != ">="
        && condition[i] != "!=" && condition[i] != "==")
        {
            left += condition[i];
            i++;
        }
        conditionLocation = i;
        while(i < condition.size()){
            right += condition[i];
        }
        Variable a = new Variable("", )
        BinaryOperator b = new BinaryOperator(sideA->calculate(), sideB->calculate());


        if(condition[conditionLocation] == ">")
            result = sideA.calculate() > sideB ? true : false;

    }

}