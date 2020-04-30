/*

   EGRE 591 Compiler Construction
   Created By: Dan Relser
   Mostly unmodified

 */

#include <iostream>
#include <string>
#include "TCoutput.h"
#include "TCglobals.h"
#include "CGtargetCode.h"

using namespace std;
namespace toyc {

void reportDEBUG(string prefix, string type, string message) {
    cerr << prefix + "[" + type + "]" + message << endl;
}

void reportSCANNER(string prefix, string message) {
    if (v_scanner) {
        cerr << prefix + "[SCANNER]" + message << endl;
    }
}

void reportWARNING(string prefix, string message) {
    cerr << prefix + "[WARNING]" + message << endl;
}

void reportSEMANTIC_ERROR(TClexer *l, string message) {
    int ln;
    string instruction;
    string sep = ": ";
    cerr << (ln = l->getLineNum()) << sep << l->getLine() << endl;
    instruction += ln;
    cerr <<
         pad(instruction.length()) <<
         pad(l->getPos() + sep.length() - (l->getLexeme().length()) + 1) <<
         "^ %error: " << message << endl;
}

void reportSYNTAX_ERROR(TClexer *l, string message) {
    int ln;
    string instruction;
    string sep = ": ";
    cerr << (ln = l->getLineNum()) << sep << l->getLine() << endl;
    instruction += ln;
    cerr <<
         pad(instruction.length()) <<
         pad(l->getPos() + sep.length() - (l->getLexeme().length()) - 1) <<
         "^ %error: " << message << endl;
}

void reportSYNTAX_ERROR(string message) {
    cerr << ("%error: " + message) << endl;
}

void dumpAST(ASabstractSyntax *ast) {
    cout << endl << ast->toString() << endl;
}

void dumpST(TCsymTable *st) {
    cout << "\nSymbol Table:" << endl << st->toString() << endl;
}

void dumpCode(CGtargetCode *code) {
    cout << "Code:" << endl;
    for (int i = 0; i < code->getSize(); i++)
        cout << code->getLineOfCode(i)->toString() << endl;
}

string pad(int n) {
    string s = "";
    for (int i = 1; i <= n; i++) s += " ";
    return s;
}

int _pos = 0;
int _INDENTSIZE = 1;

string spaces() { return pad(_pos); }

void indent() { _pos += _INDENTSIZE; }

void outdent() { _pos -= _INDENTSIZE; }
}
