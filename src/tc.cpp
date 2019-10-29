/*
   EGRE 591 Compiler Construction
   Created By: Dan Resler
   Unmodified

 */
#include <iostream>

#include "TCtoken.h"
#include "TClexer.h"
#include "TCparser.h"
#include "TCglobals.h"
#include "TCtokens.h"
#include "TCoutput.h"
#include "ASabstractSyntax.h"

using namespace toyc;
using namespace std;

void processCommandLine(int, char *[]);

void printUsageMessage();

int main(int argc, char *argv[]) {
    try {
        processCommandLine(argc, argv);
        TClexer *scanner = new TClexer(inputFileName);
        TCparser *parser = new TCparser(scanner);
        //turnVerboseOn();
        ASabstractSyntax *ast = parser->parse();
        if (verbose) dumpAST(ast);
    } catch (...) {
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
    std::cout << "Where options include: Note: XX == WIP" << std::endl;
	std::cout << "XX   -help              -h       display this usage message" << std::endl;
	std::cout << "XX   -output <file>     -o <f>   specifies target file name" << std::endl;
	std::cout << "XX   -class <file>      -c <l>   specifies class file name" << std::endl;
	std::cout << "XX   -debug <level>     -d <l>   display messages that aid in tracing the" << std::endl;
	std::cout << "XX                               compilation process. If level is:" << std::endl;
	std::cout << "XX                                  0 - all messages" << std::endl;
	std::cout << "XX                                  1 - scanner messages only" << std::endl;
	std::cout << "XX                                  2 - parser messages onlys" << std::endl;
	std::cout << "XX   -abstract          -a        dump the abstract syntax tree" << std::endl;
	std::cout << "XX   -symbol            -s        dump the symbol table(s)" << std::endl;
	std::cout << "XX   -code              -cc       dump the generated program" << std::endl;
	std::cout << "   -verbose           -v        display all information" << std::endl;
	std::cout << "XX   -version           -vv       display the program version" << std::endl;
}

