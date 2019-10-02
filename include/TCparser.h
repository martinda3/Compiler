#ifndef TCPARSER_H
#define TCPARSER_H

#include "TClexer.h"
#include "TCtoken.h"
#include "ASabstractSyntax.h"
#include "ASstatement.h"
#include "ASexpr.h"

namespace toyc {

    class TCparser {
    public:
        TCparser(TClexer *s);

        ASabstractSyntax *parse();

    private:
        TClexer *scanner;
        TCtoken *buff;

        ASabstractSyntax *program();

        int statementList(ASstatement *[], int);

        ASstatement *statement();

        ASexpr *expr();

        ASexpr *term();

        ASexpr *element();

        ASexpr *factor();

        void accept(int);
    };

}
#endif
