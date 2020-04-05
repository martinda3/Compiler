/*

   EGRE 591 Compiler Construction
   Created By: Charles Dieztel & Dajion Martin

 */
#ifndef TCLEXER_H
#define TCLEXER_H

#include "TCtoken.h"
using std::string;

namespace toyc {

    class TClexer {
    public:
        TClexer(string);

        TCtoken *getToken();

        string getLine();

        string getLexeme();

        int getLineNum();

        int getPos();
    };

	string getNextLine();

	char getChar();

	bool isInAlphabet(char);

	bool tokenChecker(string, string);

}
#endif
