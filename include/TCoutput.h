/*

   EGRE 591 Compiler Construction
   Created By: Dan Resler
   Unmodified

 */
#ifndef TCOUTPUT_H
#define TCOUTPUT_H

#include "TClexer.h"

#include "ASabstractSyntax.h"
#include "TCsymTable.h"

namespace toyc {

    void reportDEBUG(std::string prefix, std::string type, std::string message);

    void reportWARNING(std::string prefix, std::string message);

    void reportSEMANTIC_ERROR(TClexer *, std::string);

    void reportSYNTAX_ERROR(TClexer *, std::string);

    void reportSYNTAX_ERROR(std::string);


    void dumpAST(ASabstractSyntax *ast);

    void dumpST(TCsymTable *st);
    //void dumpCode((TargetCode type)* code);

    std::string pad(int);

    std::string spaces();

    void indent();

    void outdent();
}

#endif

