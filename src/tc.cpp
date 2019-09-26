/*
   EGRE 591 Compiler Construction
   Created By: Dan Resler
   Unmodified

 */

#include <iostream>
#include "TCtoken.h"
#include "TClexer.h"
#include "TCglobals.h"
#include "TCtokens.h"
#include "TCoutput.h"

using namespace toyc;
using namespace std;

void processCommandLine(int, char *[]);

void printUsageMessage();

int main(int argc, char *argv[]) {
    try {
        processCommandLine(argc, argv);
        TClexer *scanner = new TClexer(inputFileName);
        int tok;
        //turnVerboseOn();
        while ((tok = scanner->getToken()->getTokenType()) != EOFILE);
    }
    catch (...) {
        std::cerr << "ERROR: scanning failed" << std::endl;
        exit(EXIT_FAILURE);
    }
}


void processCommandLine(int argc, char *argv[]) {
    switch (argc) {
        case 1:
            printUsageMessage();
            break;
        case 2:
            if (argv[1][0] != '-') {
                inputFileName = argv[1];
                turnVerboseOff();
            } else {
                printUsageMessage();
            }
            break;
        case 3:
            if (argv[1][0] == '-' && argv[1][1] == 'v') {
                turnVerboseOn();
                inputFileName = argv[2];
            } else {
                printUsageMessage();
            }
            break;
        default:
            printUsageMessage();
    }
}

void printUsageMessage() {
    std::cout << "Usage: tc [-v] input_file" << std::endl;
    std::cout << "Where -v means verbose output" << std::endl;
}

