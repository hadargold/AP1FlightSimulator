//
// Created by yuval on 12/27/19.
//
#include <string>
#include "Run.h"

int main(int argc, char **argv) {
    string flyText = argv[1];
    //string text_File = "fly.txt";
    Run interpeter(flyText);
    interpeter.run();
    return 0;
}