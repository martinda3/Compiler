/*

   EGRE 591 Compiler Construction
   Created By: Dan Resler

 */

#ifndef TCSYMTABLE_H
#define TCSYMTABLE_H

#include "TCsymbol.h"
#include "TCtoken.h"

#define MAX_SYMS 100 // arbitrary

namespace toyc {
    class TCsymTable {
    public:
        TCsymTable();

        int add(TCsymbol *);

        int find(std::string);

        int find(TCsymbol *);

        TCsymbol *getSym(int);

        TCsymbol *getSym(TCtoken *);

        int getSize();

        std::string toString();

    private:
        TCsymbol *symTable[MAX_SYMS];
        int size;
    };

}

#endif