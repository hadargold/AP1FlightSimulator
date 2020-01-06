//
// Created by yuval on 12/27/19.
//
#include <string>
#include "Run.h"

int main() {
    string text_File = "fly.txt";
    Run interpeter("fly.txt");
    interpeter.run();
    return 0;
}