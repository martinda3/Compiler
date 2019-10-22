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

        int Definition();

        int Type();

        int FunctionDefinition();

        int functionheader();

        int functionbody();

        int formalparamlist();

        int breakstatment();

        int expressionstatment();
		int compoundstantment();
		int ifstatment();
		int nullstatment();
		int returnstatment();
		int whilestatment();
		int readstatment();
		int writestatment();
		int newlinestatment();
		int expression();
		int relopexpression();
		int simpleexpression();
		int term();
		int primary();
		int functioncall();
		int actualparameters();

        ASexpr *expr();

       // ASexpr *term();

        ASexpr *element();

        ASexpr *factor();

        void accept(int);
    };

}
#endif
