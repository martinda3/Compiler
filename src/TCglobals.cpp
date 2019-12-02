/*

   EGRE 591 Compiler Construction
   Created By: Dan Resler
   Unmodified

 */

#include <iostream>

#include "CGtargetCode.h"
#include "TCsymTable.h"



namespace toyc {

    int THISISCHEATING = 0;
    std::string inputFileName;
    std::string outputClassFileName;
    std::string targetFileName;
    std::string ASM_FILE_EXSTENTION = "j";
    TCsymTable *symTable = NULL;

    std::string COMPILER = "toyc";
    std::string VERSION = "v 2.0.0";
    std::string AUTHOR = "Dajion Martin, Charles Dietzel";

    bool verbose = false;
    bool v_scanner = false;
    bool v_parser = false;
    bool v_code_gen = false;

    void turnVerboseOn() { verbose = true; }

    void turnVerboseOff() { verbose = false; }

    void turnScannerOn() { v_scanner = true; }

    void turnScannerOff() { v_scanner  = false; }

    void turnParserOn() { v_parser = true; }

    void turnParserOff() {v_parser = false; }

    void turnCodeGenOn() { v_code_gen = true; }

    void turnCodeGenOff() { v_code_gen = false; }
}
