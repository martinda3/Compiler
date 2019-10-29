/*

   EGRE 591 Compiler Construction
   Abstract Syntax: Charles Dieztel

 */

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
        TCtoken* accept(int);

        ASprogram* program();

        int DefinitionList(ASdefinition *[], int);

		ASdefinition* Definition();
		AStype* Type();
		ASstatement* FunctionDefinition(ASdefinition* [], int*);

		int FormalParamList(ASdefinition* []);
		int FunctionHeader(ASdefinition* []);

		ASstatement* Statement();
		ASstatement* FunctionBody();
		ASstatement* BreakStatement();
		ASstatement* ExpressionStatement();
		ASstatement* CompoundStatement();
		ASstatement* IfStatement();
		ASstatement* NullStatement();
		ASstatement* ReturnStatement();
		ASstatement* WhileStatement();
		ASstatement* ReadStatement();
		ASstatement* WriteStatement();
		ASstatement* NewLineStatement();

		ASexpression* FunctionCall();
		ASexpression* Expression();
		ASexpression* RelopExpression();
		ASexpression* SimpleExpression();
		ASexpression* Term();
		ASexpression* Primary();
		ASexpression* ActualParameters();
    };

}
#endif
