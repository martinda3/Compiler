/*

   EGRE 591 Compiler Construction
   Created By: Dan Resler
   Unmodified

 */

#include <iostream>

#include "TCsymTable.h"



namespace toyc {

    std::string inputFileName;
    std::string outputClassFileName;
    std::string targetFileName;
    std::string ASM_FILE_EXSTENTION = "j";
    TCsymTable *symTable = NULL;


    std::string COMPILER = "toyc";
    std::string VERSION = "v 1.0.0";
    std::string AUTHOR = "Dajion Martin, Charles Dietzel";

    bool verbose = false;

    void turnVerboseOn() { verbose = true; }

    void turnVerboseOff() { verbose = false; }
}
