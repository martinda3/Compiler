/*
   EGRE 591 Compiler Construction
   Created By: Charles Dieztel & Dajion Martin 
 */

#include <iostream>
#include <sstream>
#include <vector>
#include <ctime>

#include "TCtoken.h"
#include "TClexer.h"
#include "TCparser.h"
#include "TCglobals.h"
#include "TCtokens.h"
#include "TCoutput.h"
#include "ASabstractSyntax.h"
#include "CGcodeGenerator.h"
#include "CGtargetCode.h"
#include "JVMcodeGenerator.h"
#include "JVMtargetCode.h"


using namespace toyc;
using namespace std;

void processCommandLine(int, char *[], std::string);


void printUsageMessage();

int main(int argc, char *argv[]) {
    time_t rawtime;
    struct tm * timeinfo;
    char buffer[80];

    time (&rawtime);
    timeinfo = localtime(&rawtime);

    strftime(buffer,sizeof(buffer),"%H:%M:%S",timeinfo);
    std::string ffile(buffer);

    TClexer *scanner;
    TCparser * parser;
    ASabstractSyntax *ast;
    CGcodeGenerator *cg;
    CGtargetCode* tc;
    // Better for error checking (UNGLY)
    try { processCommandLine(argc, argv, ffile); }
    catch (...) { std::cerr << "ERROR: processCommandLine" << std::endl; exit(EXIT_FAILURE); }

    try { scanner = new TClexer(inputFileName); }
    catch (...) { std::cerr << "ERROR: TClexer" << std::endl; exit(EXIT_FAILURE); }

    try { parser = new TCparser(scanner); }
    catch (...) { std::cerr << "ERROR: TCparser" << std::endl; exit(EXIT_FAILURE); }

    try { ast = parser->parse(); }
    catch (...) { std::cerr << "ERROR: ASabstractSyntax" << std::endl; exit(EXIT_FAILURE); }

    try { cg = new JVMcodeGenerator(); }
    catch (...) { std::cerr << "ERROR: CGcodeGenerator" << std::endl; exit(EXIT_FAILURE); }

    try { tc = cg->generateCode(ast); }
    catch (...) { std::cerr << "ERROR: CGtargetCode" << std::endl; exit(EXIT_FAILURE); }

    try { tc->writeCode(tc,targetFileName); }
    catch (...) { std::cerr << "ERROR: writeCode" << std::endl; exit(EXIT_FAILURE); }

    if (v_code_gen)
    {
        dumpAST(ast);
        dumpST(symTable);
        dumpCode(tc);
    }
}

void processCommandLine(int argc, char *argv[], std::string filename) {
    string outing, keeper, classs; int chop;
    try
    {
        outing = argv[2];
        chop = outing.length();
        for (int i = 0; i < chop; i++)
        {
            if (outing[i] != '.')
            {
                keeper += outing[i];
            }
            else
            {
                keeper += outing[i];
                break;
            }
        }
        keeper += "j";
        classs = outing.substr(5, (outing.length() - 5)-3);
        outputClassFileName = classs;
    }
    catch (...) {}
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
                targetFileName = keeper;
                //targetFileName = "test/test" + filename + ".j";
            }
			else
			{
				inputFileName = argv[2];

                targetFileName = keeper;
                //targetFileName = "test/test" + filename + ".j";;
			}	
			break;
        default:
			if (argv[3][0] == '-' && argv[3][1] == 'd') 
			{
                if (argv[4] == std::to_string(0))
				{
					inputFileName = argv[2];
                    targetFileName = keeper;
                    //targetFileName = "test/test" + filename + ".j";;

					turnVerboseOn();
					turnParserOff();
					turnScannerOff();
					turnCodeGenOff();
				}
                else if (argv[4] == std::to_string(1))
				{
					turnScannerOn();
					inputFileName = argv[2];

                    targetFileName = keeper;
                    //targetFileName = "test/test" + filename + ".j";;
					turnCodeGenOff();
					turnParserOff();
					turnVerboseOff();
				}
                else if (argv[4] == std::to_string(2))
				{
					inputFileName = argv[2];
                    targetFileName = keeper;
                    //targetFileName = "test/test" + filename + ".j";;
					turnParserOn();
					turnVerboseOff();
					turnCodeGenOff();
					turnScannerOff();
				}
                else if (argv[4] == std::to_string(3))
				{
					inputFileName = argv[2];
                    targetFileName = keeper;
                    //targetFileName = "test/test" + filename + ".j";;
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

vector<string> split (const string &s, char delim)
{
    vector<string> result;
    stringstream ss (s);
    string item;
    while (getline (ss, item, delim)) {
        result.push_back (item);
    }
    return result;
}

std::string getProgramName(std::string s)
{
    vector<string> strs = split(s,'/');
    return split(strs[strs.size()-1],'.')[0];
}

void printUsageMessage() {
    std::cout << "\nUsage: tc [-v] <input_file> [-d] <level>" << std::endl;
	std::cout << "     -debug <level>     -d <l>   display messages that aid in tracing the" << std::endl;
	std::cout << "                                 compilation process. If level is:" << std::endl;
	std::cout << "                                    0 - all messages" << std::endl;
	std::cout << "                                    1 - scanner messages only" << std::endl;
	std::cout << "                                    2 - parser messages onlys" << std::endl;
	std::cout << "     -verbose           -v        display all information" << std::endl;
}

