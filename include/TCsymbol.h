/*

   EGRE 591 Compiler Construction
   Created By: Dan Resler

 */

#include <iostream>


#ifndef TCSYMBOL_H
#define TCSYMBOL_H

namespace toyc {

    enum symType { VAR, FUNC, OFFSET, NO_TYPE };
    extern int _nextOffset;

    class TCsymbol {
    public:
        TCsymbol();

        TCsymbol(std::string, enum symType);

        std::string getId();

        void setId(std::string);

        enum symType getType();
        std::string getValue();

        void setValue(std::string setThis);
        void setType(enum symType);

        std::string toString();
        //int getNextOffset();
        void getNextOffset();
        int getOffset();
        void setOffset(int);

    private:
        std::string id;
        std::string value;
        int offset;
        enum symType type;
    };

}

#endif

