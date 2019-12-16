/*

   EGRE 591 Compiler Construction
   Created By: Dan Relser
   Mostly unmodified

 */

#include <iostream>
#include <string>
#include "TCoutput.h"
#include "CGtargetCode.h"

namespace toyc {

    void reportDEBUG(std::string prefix, std::string type, std::string message) {
        std::cerr << prefix + "[" + type + "]" + message << std::endl;
    }

    void reportWARNING(std::string prefix, std::string message) {
        std::cerr << prefix + "[WARNING]" + message << std::endl;
    }

    void reportSEMANTIC_ERROR(TClexer *l, std::string message) {
        int ln;
        std::string lnstr;
        std::string sep = ": ";
        std::cerr << (ln = l->getLineNum()) << sep << l->getLine() << std::endl;
        lnstr += ln;
        std::cerr <<
                  pad(lnstr.length()) <<
                  pad(l->getPos() + sep.length() - (l->getLexeme().length()) + 1) <<
                  "^ %error: " << message << std::endl;
    }

    void reportSYNTAX_ERROR(TClexer *l, std::string message) {
        int ln;
        std::string lnstr;
        std::string sep = ": ";
        std::cerr << (ln = l->getLineNum()) << sep << l->getLine() << std::endl;
        lnstr += ln;
        std::cerr <<
                  pad(lnstr.length()) <<
                  pad(l->getPos() + sep.length() - (l->getLexeme().length()) - 1) <<
                  "^ %error: " << message << std::endl;
    }

    void reportSYNTAX_ERROR(std::string message) {
        std::cerr << ("%error: " + message) << std::endl;
    }

    void dumpAST(ASabstractSyntax *ast) {
        std::cout << std::endl << ast->toString() << std::endl;
    }

    void dumpST(TCsymTable *st) {
        std::cout << "\nSymbol Table:" << std::endl << st->toString() << std::endl;
    }

    void dumpCode(CGtargetCode *code) {
        std::cout << "Code:" << std::endl;
        for(int i = 0; i < code->getSize(); i++)
            std::cout << code->getLineOfCode(i)->toString() << std::endl;
    }

    std::string pad(int n) {
        std::string s = "";
	    for (int i = 1; i <= n; i++) s += " ";
        // for (int i = 1; i <= n; i++) s += ".";   // For easy visiol debugging
        return s;
    }

    int _pos = 0;
    int _INDENTSIZE = 1;

    std::string spaces() { return pad(_pos); }

    void indent() { _pos += _INDENTSIZE; }

    void outdent() { _pos -= _INDENTSIZE; }
}
