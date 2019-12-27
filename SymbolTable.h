//
// Created by hadar on 12/26/19.
//

#ifndef FLIGHTSIMULATOR_SYMBOLTABLE_H
#define FLIGHTSIMULATOR_SYMBOLTABLE_H

#include <string>
#include <map>
#include <mutex>
#include <string>
#include "ex1.h"
#include "unordered_map"


class SymbolTable {
    unordered_map <string, Variable> symbolMap;
    unordered_map <string, string> simToVal = {
            {"/instrumentation/airspeed-indicator/indicated-speed-kt", "airspeed"},
            {"/sim/time/warp",""},
            {"controls/switches/magnetos",""},
            {" /instrumentation/heading-indicator/offset-deg",""},
            {"instrumentation/altimeter/indicated-altitude-ft",""},
            {"",""},
            {"",""},
            {"",""},
            {"",""},
            {"",""},
            {"",""},
    };
};



#endif //FLIGHTSIMULATOR_SYMBOLTABLE_H
