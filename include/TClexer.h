#ifndef TCLEXER_H
#define TCLEXER_H

#include "TCtoken.h"

namespace toyc {

    class TClexer {
    public:
        TClexer(std::string);

        TCtoken* getToken();

        std::string getLine();

        std::string getLexeme();

        int getLineNum();

        int getPos();
    };

}
#endif
