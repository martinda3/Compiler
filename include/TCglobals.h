namespace toyc {
    extern std::string inputFileName;

    extern std::string COMPILER;
    extern std::string VERSION;
    extern std::string AUTHOR;

    extern bool debug_scanner; // Set to False
//	extern bool debug_parser;
//	extern bool debug_codeGen;

    extern bool verbose;

//	extern bool dump_abstractCode;
//	extern bool dump_objectCode;
//	extern booldump_symbolTable;

    void turnVerboseOn();

    void turnVerboseOff();
}
