/*

   EGRE 591 Compiler Construction
   Created By: Dan Resler

 */

#include <iostream>

#ifndef TCSYMBOL_H
#define TCSYMBOL_H

namespace toyc {

    enum symType { VAR, FUNC, NO_TYPE };
    extern int _nextOffset;

    class TCsymbol {
    public:
        TCsymbol();

        TCsymbol(std::string, enum symType);

        std::string getId();

        void setId(std::string);

        enum symType getType();

        void setType(enum symType);

        std::string toString();
        int getNextOffset();
        int getOffset();
        void setOffset(int);

    private:
        std::string id;
        int offset;
        enum symType type;
    };

}

#endif

