/*

   EGRE 591 Compiler Construction
   Created By: Dan Resler
   Unmodified

 */

#include "TCsymTable.h"

namespace toyc {

    extern std::string inputFileName;
    extern std::string outputClassFileName;
    extern std::string targetFileName;
    extern std::string ASM_FILE_EXTENSION;
    extern TCsymTable *symTable;
    //extern (AbstractSyntax type) ast;
	// extern (TargetCode type) objectcode;

    extern std::string COMPILER;
    extern std::string VERSION;
    extern std::string AUTHOR;

    extern bool verbose;
    extern bool v_scanner;
    extern bool v_parser;
    extern bool v_code_gen;

    void turnVerboseOn();

    void turnVerboseOff();

    void turnScannerOn();

    void turnScannerOff();

    void turnParserOn();

    void turnParserOff();

    void turnCodeGenOn();

    void turnCodeGenOff();

}


//#endif
