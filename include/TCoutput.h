/*

   EGRE 591 Compiler Construction
   Created By: Dan Resler
   Unmodified

 */
#ifndef TCOUTPUT_H
#define TCOUTPUT_H

#include <string>

#include "TClexer.h"
#include "CGtargetCode.h"
#include "ASabstractSyntax.h"
#include "TCsymTable.h"

using namespace std;
namespace toyc {

void reportDEBUG(string prefix, string type, string message);

void reportWARNING(string prefix, string message);

void reportSEMANTIC_ERROR(TClexer *, string);

void reportSYNTAX_ERROR(TClexer *, string);

void reportSYNTAX_ERROR(string);

void reportSCANNER(string prefix, string message);

void dumpAST(ASabstractSyntax *ast);

void dumpST(TCsymTable *st);

void dumpCode(CGtargetCode *code);

string pad(int);

string spaces();

void indent();

void outdent();
}

#endif

