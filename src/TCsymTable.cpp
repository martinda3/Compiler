/*

   EGRE 591 Compiler Construction
   Created By: Dan Relser

 */

#include "TCsymbol.h"
#include "TCsymTable.h"

namespace toyc {

    TCsymTable::TCsymTable() { size = 0; }

    int TCsymTable::add(TCsymbol *sym) {
        if (size >= MAX_SYMS) {
            std::cerr << "Error: symbol table overflow" << std::endl;
            exit(EXIT_FAILURE);
        } else {
            symTable[size++] = sym;
            return (size - 1);
        }
    }

    int TCsymTable::find(std::string str) {
        for (int i = 0; i < size; i++)
            if (symTable[i]->getId() == str) return i;
        return -1;
    }

    int TCsymTable::find(TCsymbol *t) {
        for (int i = 0; i < size; i++)
            if (symTable[i] == t) return i;
        return -1;
    }

    TCsymbol *TCsymTable::getSym(int index) {
        return ((index < 0 || index >= MAX_SYMS) ? NULL : symTable[index]);
    }

    TCsymbol *TCsymTable::getSym(TCtoken *t) {
        int loc = find(t->getLexeme());
        if (loc == -1) loc = add(new TCsymbol(t->getLexeme(), NO_TYPE));
        return getSym(loc);
    }

    int TCsymTable::getSize() { return size; }

    std::string TCsymTable::toString() {
        std::string str = "[";
        for (int i = 0; i < size; i++) {
            if (i == 0) str += "\n";
            str += "  ";
            str += (symTable[i]->getId() + ",");
            str += (symTable[i]->getType() == VAR ? "VAR" :
                    symTable[i]->getType() == FUNC ? "FUNC" :
                    symTable[i]->getType() == NO_TYPE ? "NO_TYPE" : "ERROR");
            str += "\n";
        }
        return (str + "]");
    }
}
