#ifndef TCPARSER_H
#define TCPARSER_H

#include "TClexer.h"
#include "TCtoken.h"
#include "ASabstractSyntax.h"
#include "ASstatement.h"
#include "ASdefinition.h"
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

        int DefinitionList(ASdefinition *[], int);

        int Statement();

        ASdefinition* Definition();

        int Type();

        int FunctionDefinition();

        int FunctionHeader();

        int FunctionBody();

        int FormalParamList();

        int BreakStatement();
		int FunctionCall();
        int ExpressionStatement();
		int CompoundStatement();
		int IfStatement();
		int NullStatement();
		int ReturnStatement();
		int WhileStatement();
		int ReadStatement();
		int WriteStatement();
		int NewLineStatement();
		int Expression();
		int RelopExpression();
		int SimpleExpression();
		int Term();
		int Primary();
		int ActualParameters();

        ASexpr *expr();

       // ASexpr *term();

        ASexpr *element();

        ASexpr *factor();

        void accept(int);
    };

}
#endif
