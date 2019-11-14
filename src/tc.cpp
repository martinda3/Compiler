/*
   EGRE 591 Compiler Construction
   Created By: Charles Dieztel & Dajion Martin 
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
        int loc;
        processCommandLine(argc, argv);
        TClexer *scanner = new TClexer(inputFileName);
    	//int tok;
    	//while ((tok=scanner->getToken()->getTokenType()) != EOFILE) ;
        TCparser *parser = new TCparser(scanner);
        ASabstractSyntax *ast = parser->parse();
        if (v_code_gen) dumpAST(ast);
        loc = symTable->getSize();
        for (int i = 0; i < loc; i++){ cout << symTable->getSym(i)->toString() << endl << i << endl; }
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
        case 3:
			if (argv[1][0] == '-' && argv[1][1] == 'v') 
			{
                turnVerboseOn();
				turnScannerOn();
				turnCodeGenOn();
				turnParserOn();
				inputFileName = argv[2];
            }
			else
			{
				inputFileName = argv[2];
			}	
			break;
        default:
			if (argv[3][0] == '-' && argv[3][1] == 'd') 
			{
                if (argv[4] == std::to_string(0))
				{
					inputFileName = argv[2];
					turnVerboseOn();
					turnParserOff();
					turnScannerOff();
					turnCodeGenOff();
				}
                else if (argv[4] == std::to_string(1))
				{
					turnScannerOn();
					inputFileName = argv[2];
					turnCodeGenOff();
					turnParserOff();
					turnVerboseOff();
				}
                else if (argv[4] == std::to_string(2))
				{
					inputFileName = argv[2];
					turnParserOn();
					turnVerboseOff();
					turnCodeGenOff();
					turnScannerOff();
				}
                else if (argv[4] == std::to_string(3))
				{
					inputFileName = argv[2];
					turnVerboseOff();
					turnParserOff();
					turnScannerOff();
					turnCodeGenOn();
				}
            }
			else { }
            break;
    }
}

void printUsageMessage() {
    std::cout << "\nUsage: tc [-v] <input_file> [-d] <level>" << std::endl;
    //std::cout << "Where options include: Note: XX == WIP" << std::endl;
	//std::cout << "XX   -help              -h       display this usage message" << std::endl;
	//std::cout << "XX   -output <file>     -o <f>   specifies target file name" << std::endl;
	//std::cout << "XX   -class <file>      -c <l>   specifies class file name" << std::endl;
	std::cout << "     -debug <level>     -d <l>   display messages that aid in tracing the" << std::endl;
	std::cout << "                                 compilation process. If level is:" << std::endl;
	std::cout << "                                    0 - all messages" << std::endl;
	std::cout << "                                    1 - scanner messages only" << std::endl;
	std::cout << "                                    2 - parser messages onlys" << std::endl;
	//std::cout << "XX   -abstract          -a        dump the abstract syntax tree" << std::endl;
	//std::cout << "XX   -symbol            -s        dump the symbol table(s)" << std::endl;
	//std::cout << "XX   -code              -cc       dump the generated program" << std::endl;
	std::cout << "     -verbose           -v        display all information" << std::endl;
	//std::cout << "XX   -version           -vv       display the program version" << std::endl;
}

