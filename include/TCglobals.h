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

    void turnVerboseOn();
    void turnVerboseOff();

}


//#endif