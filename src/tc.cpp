/*
   EGRE 591 Compiler Construction
   Created By: Charles Dieztel & Dajion Martin
 */
/*
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

void processCommandLine(int, char *[], string);

void printUsageMessage();

int main(int argc, char *argv[]) {
    time_t rawtime;
    struct tm * timeinfo;
    char buffer[80];

    time (&rawtime);
    timeinfo = localtime(&rawtime);

    strftime(buffer,sizeof(buffer),"%H:%M:%S",timeinfo);
    string ffile(buffer);

    TClexer *scanner;
    TCparser * parser;
    ASabstractSyntax *ast;
    CGcodeGenerator *cg;
    CGtargetCode* tc;
    // Better for error checking (UNGLY)
    try { processCommandLine(argc, argv, ffile); }
    catch (...) { cerr << "ERROR: processCommandLine" << endl; exit(EXIT_FAILURE); }

    try { scanner = new TClexer(inputFileName); }
    catch (...) { cerr << "ERROR: TClexer" << endl; exit(EXIT_FAILURE); }

    try { parser = new TCparser(scanner); }
    catch (...) { cerr << "ERROR: TCparser" << endl; exit(EXIT_FAILURE); }

    try { ast = parser->parse(); }
    catch (...) { cerr << "ERROR: ASabstractSyntax" << endl; exit(EXIT_FAILURE); }

    try { cg = new JVMcodeGenerator(); }
    catch (...) { cerr << "ERROR: CGcodeGenerator" << endl; exit(EXIT_FAILURE); }

    try { tc = cg->generateCode(ast); }
    catch (...) { cerr << "ERROR: CGtargetCode" << endl; exit(EXIT_FAILURE); }

    try { tc->writeCode(tc,targetFileName); }
    catch (...) { cerr << "ERROR: writeCode" << endl; exit(EXIT_FAILURE); }

    if (v_code_gen)
    {
        dumpAST(ast);
        dumpST(symTable);
        dumpCode(tc);
    }
}

void processCommandLine(int argc, char *argv[], string filename) {
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
                if (argv[4] == to_string(0))
				{
					inputFileName = argv[2];
                    targetFileName = keeper;
                    //targetFileName = "test/test" + filename + ".j";;

					turnVerboseOn();
					turnParserOff();
					turnScannerOff();
					turnCodeGenOff();
				}
                else if (argv[4] == to_string(1))
				{
					turnScannerOn();
					inputFileName = argv[2];

                    targetFileName = keeper;
                    //targetFileName = "test/test" + filename + ".j";;
					turnCodeGenOff();
					turnParserOff();
					turnVerboseOff();
				}
                else if (argv[4] == to_string(2))
				{
					inputFileName = argv[2];
                    targetFileName = keeper;
                    //targetFileName = "test/test" + filename + ".j";;
					turnParserOn();
					turnVerboseOff();
					turnCodeGenOff();
					turnScannerOff();
				}
                else if (argv[4] == to_string(3))
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

string getProgramName(string s)
{
    vector<string> strs = split(s,'/');
    return split(strs[strs.size()-1],'.')[0];
}

void printUsageMessage() {
    cout << "\nUsage: tc [-v] <input_file> [-d] <level>" << endl;
	cout << "     -debug <level>     -d <l>   display messages that aid in tracing the" << endl;
	cout << "                                 compilation process. If level is:" << endl;
	cout << "                                    0 - all messages" << endl;
	cout << "                                    1 - scanner messages only" << endl;
	cout << "                                    2 - parser messages onlys" << endl;
	cout << "     -verbose           -v        display all information" << endl;
}
*/
/* Testing the Scanner */
#include <iostream>
#include "TCtoken.h"
#include "TClexer.h"
#include "TCglobals.h"
#include "TCtokens.h"
#include "TCoutput.h"

using namespace toyc;
using namespace std;

void processCommandLine(int, char* []);
void printUsageMessage();

int main(int argc, char* argv[])
{
    try
    {
        processCommandLine(argc, argv);
        turnVerboseOff();
        turnScannerOn();
        TClexer* scanner = new TClexer(inputFileName);
        int tok;
        while ((tok = scanner->getToken()->getTokenType()) != EOFILE);
    }
    catch (...)
    {
        cerr << "ERROR: scanning failed" << endl;
        exit(EXIT_FAILURE);
    }
}


void processCommandLine(int argc, char* argv[])
{
    switch (argc)
    {
        case 1:
            printUsageMessage();
            break;
        case 2:
            if (argv[1][0] != '-')
            {
                inputFileName = argv[1];
                turnVerboseOff();
            }
            else { printUsageMessage(); }
            break;
        case 3:
            if (argv[1][0] == '-' && argv[1][1] == 'v')
            {
                turnVerboseOn();
                inputFileName = argv[2];
            }
            else { printUsageMessage(); }
            break;
        default:
            printUsageMessage();
    }
}

void printUsageMessage()
{
    cout << "Usage: tc [-v] input_file" << endl;
    cout << "Where -v means verbose output" << endl;
}

