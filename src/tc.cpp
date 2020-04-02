/*
   EGRE 591 Compiler Construction
   Created By: Charles Dieztel & Dajion Martin
 */

#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>

#include "TCfileData.h"
#include "TCtoken.h"
#include "TClexer.h"
#include "TCparser.h"
#include "TCglobals.h"
#include "TCtokens.h"
#include "TCoutput.h"

#include "TCfileData.h"

#include "ASabstractSyntax.h"
#include "CGcodeGenerator.h"
#include "CGtargetCode.h"
#include "JVMcodeGenerator.h"
#include "JVMtargetCode.h"


using namespace toyc;
using namespace std;

int inputFileHandler(string nameoffile);

void processCommandLine(int, char *[], string);

void printUsageMessage();

static std::ifstream inputfile;

int main(int argc, char *argv[]) {
    char buffer[80];
    string ffile(buffer);
    try { processCommandLine(argc, argv, ffile); }
    catch (...) { cerr << "ERROR: processCommandLine" << endl; exit(EXIT_FAILURE); }
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
            // add the argv[2]
			if (argv[1][0] == '-' && argv[1][1] == 's')
			{
                turnVerboseOn();
				turnScannerOn();
				if (argv[1][2] == '0') // add more robust debugging
				{
                    //turnVerboseOff();
                    turnScannerOff();
                    turnScannerOff();
                    turnCodeGenOff();
				}
				inputFileName = argv[2];
                targetFileName = keeper;
                TCfile *test1 = new TCfile(inputFileName, targetFileName, inputFileHandler(inputFileName));
                cout << test1->getFileInfo();
                TClexer* scanner = new TClexer(inputFileName);
                int tok;
                while ((tok = scanner->getToken()->getTokenType()) != EOFILE);
            }
            else if (argv[1][0] == '-' && argv[1][1] == 'c')
            {
                turnVerboseOn();
                turnParserOn();
                turnScannerOn();
                turnCodeGenOn();
                if (argv[1][2] == '0')
                {
                    turnVerboseOff();
                    turnScannerOff();
                    turnScannerOff();
                    turnCodeGenOff();
                }
                TClexer *scanner;
                TCparser * parser;
                ASabstractSyntax *ast;
                CGcodeGenerator *cg;
                CGtargetCode* tc;
                inputFileName = argv[2];

                targetFileName = keeper;
                cout << inputFileHandler(inputFileName);
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
            else if (argv[1][0] == '-' && argv[1][1] == 'p')
            {
                turnVerboseOn();
                turnParserOn();
                //turnScannerOn();
                if (argv[1][2] == '0')
                {
                    turnVerboseOff();
                    turnScannerOff();
                    turnScannerOff();
                    turnCodeGenOff();
                }
                inputFileName = argv[2];
                TClexer *scanner;
                try { scanner = new TClexer(inputFileName); }
                catch (...) { cerr << "ERROR: TClexer" << endl; exit(EXIT_FAILURE); }
                int tok;
                while ((tok = scanner->getToken()->getTokenType()) != EOFILE);
            }
            else if (argv[1][0] == '-' && argv[1][1] == 'a')
            {
                turnVerboseOn();
                turnParserOn();
                turnScannerOn();
                turnCodeGenOn();
                if (argv[1][2] == '0')
                {
                    turnVerboseOff();
                    turnScannerOff();
                    turnScannerOff();
                    turnCodeGenOff();
                }
                TClexer *scanner;
                TCparser * parser;
                ASabstractSyntax *ast;
                inputFileName = argv[2];
                try { scanner = new TClexer(inputFileName); }
                catch (...) { cerr << "ERROR: TClexer" << endl; exit(EXIT_FAILURE); }

                try { parser = new TCparser(scanner); }
                catch (...) { cerr << "ERROR: TCparser" << endl; exit(EXIT_FAILURE); }

                try { ast = parser->parse(); }
                catch (...) { cerr << "ERROR: ASabstractSyntax" << endl; exit(EXIT_FAILURE); }

                if (v_code_gen)
                {
                    dumpAST(ast);
                    dumpST(symTable);
                }
            }
			else
			{
				inputFileName = argv[2];
                targetFileName = keeper;
                cout << inputFileHandler(inputFileName);
			}
			break;
        default:
			printUsageMessage();
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
    cout << "\nUsage: tc [Function] <input_file> " << endl;
	cout << "            -Function      -s        display all Scanner information" << endl;
    cout << "            -Function      -p        display all Parser information" << endl;
    cout << "            -Function      -a        display all abstract information" << endl;
    cout << "            -Function      -c        display all Completed information" << endl;
}


int inputFileHandler(string nameoffile){
    string line;
    int count = 0;
    inputfile.open(nameoffile);
    if (inputfile.fail()) {
        std::cerr << "ERROR: input file not found" << std::endl;
        exit(EXIT_FAILURE);
    }
    while(!inputfile.eof()){
        getline(inputfile,line);
        count++;
    }
    inputfile.close();
    return count;
}
