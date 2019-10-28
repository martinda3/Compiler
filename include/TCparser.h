#ifndef TCPARSER_H
#define TCPARSER_H

#include "TClexer.h"
#include "TCtoken.h"
#include "ASabstractSyntax.h"
#include "ASstatement.h"
#include "ASdefinition.h"
#include "ASprogram.h"
#include "AStype.h"
#include "ASexpr.h"

namespace toyc {

    class TCparser {
    public:
        TCparser(TClexer *s);

        ASabstractSyntax *parse();

    private:
        TClexer *scanner;
        TCtoken *buff;

        ASprogram* program();

        int DefinitionList(ASdefinition *[], int);

		ASstatement* Statement();
		ASdefinition* Definition();
		AStype* Type();
		ASstatement* FunctionDefinition(ASdefinition* [], int*);
		int FunctionHeader(ASdefinition* []);
		ASstatement* FunctionBody();
		int FormalParamList(ASdefinition* []);
		ASstatement* BreakStatement();
		ASexpression* FunctionCall();
		ASstatement* ExpressionStatement();
		ASstatement* CompoundStatement();
		ASstatement* IfStatement();
		ASstatement* NullStatement();
		ASstatement* ReturnStatement();
		ASstatement* WhileStatement();
		ASstatement* ReadStatement();
		ASstatement* WriteStatement();
		ASstatement* NewLineStatement();
		ASexpression* Expression();
		ASexpression* RelopExpression();
		ASexpression* SimpleExpression();
		ASexpression* Term();
		ASexpression* Primary();
		ASexpression* ActualParameters();

		//ASabstractSyntax* expr();

       // ASexpr *term();

		//ASabstractSyntax* element();

		//ASabstractSyntax* factor();

        TCtoken* accept(int);
    };

}
#endif
