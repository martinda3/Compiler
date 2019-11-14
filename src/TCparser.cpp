/*

   EGRE 591 Compiler Construction
   Concrete Syntax: Dajion Martin
   Modified By: Charles Dieztel

 */

#include <iostream>
#include <string>
#include <typeinfo>

#include "TClexer.h"
#include "TCparser.h"
#include "TCoutput.h"
#include "TCglobals.h"
#include "TCtokens.h"
#include "TCsymbol.h"
#include "TCsymTable.h"

#include "ASprogram.h"
#include "ASdefinition.h"
#include "ASstatement.h"
#include "ASexpression.h"
#include "ASoperator.h"

#include "ASprog.h"

#include "ASfuncDef.h"
#include "ASvarDef.h"

#include "ASexprState.h"
#include "ASbreakState.h"
#include "ASblockState.h"
#include "ASifState.h"
#include "ASnullState.h"
#include "ASreturnState.h"
#include "ASwhileState.h"
#include "ASreadState.h"
#include "ASwriteState.h"
#include "ASnewLineState.h"

#include "ASsimpleExpr.h"
#include "ASfuncCall.h"
#include "ASexpr.h"
#include "ASminus.h"
#include "ASnot.h"

#define MAX_STATEMENTS 500 // arbitrary

namespace toyc
{

	//static void checkIfAllLabelTargetsAreDefined(ASprogram*);

	//static bool targetLabelExists(std::string, ASprogram*);

	TCparser::TCparser(TClexer* s) { scanner = s; }

	ASabstractSyntax* TCparser::parse()
	{
		buff = scanner->getToken();
		ASabstractSyntax* p = program();
		//checkIfAllLabelTargetsAreDefined((ASprogram*)p);
		return p;
	}

	void enteringDEBUG(std::string s) { if (v_parser) reportDEBUG("    ", "PARSER", "entering " + s); }

	void tokenDEBUG(std::string s) { if (verbose) reportDEBUG("       ", "INFO", " " + s); }

	void exitingDEBUG(std::string s) { if (v_parser) reportDEBUG("    ", "PARSER", "exiting  " + s); }

	ASprogram* TCparser::program()
	{
		enteringDEBUG("Program");   //  Need to call DefinitionList to recirsivly repeat
		ASdefinition* definitionList[MAX_STATEMENTS];
		symTable = new TCsymTable();
		int num = DefinitionList(definitionList, 0);
		exitingDEBUG("Program");
		return new ASprog(inputFileName, definitionList, num);
	}

	int TCparser::DefinitionList(ASdefinition* l[], int n)
	{
		int num = 0;

		enteringDEBUG("Definition List");
		if (!(buff->getTokenType() == EOFILE))
		{
			l[n] = Definition();
			num = DefinitionList(l, n + 1);
		}
		else
		{
			num = n;

		}
		exitingDEBUG("Definition List");
		return num;
	}

	ASdefinition* TCparser::Definition()
	{
		// Definition --> Type ID ( FunctionDefinition | SEMICOLON )
		enteringDEBUG("Definition");
        int loc; TCsymbol *sym;
		AStype* operand2 = NULL;
		ASdefinition* operand3[MAX_STATEMENTS];
		int operand4 = 0;
		int* num = new int;
		*num = 0;
		ASstatement* operand5 = NULL;
		operand2 = Type();
        if (buff->getTokenType() == ID)
        {
            sym = symTable->getSym(buff);
            loc = symTable->find(buff->getLexeme());
            if (loc == -1) loc = symTable->add(new TCsymbol(buff->getLexeme(),NO_TYPE));

        }
		accept(ID);
		if (buff->getTokenType() == SEMICOLON)
		{
			operand5 = new ASstatement();
            symTable->getSym(loc)->setType(VAR);
           // std::cout << symTable->getSym(loc)->toString() << std::endl << loc << std::endl;
		}
		else if (buff->getTokenType() == LPAREN)
		{
			operand5 = FunctionDefinition(operand3, num);
			operand4 = *num;
            symTable->getSym(loc)->setType(FUNC);
            //std::cout << symTable->getSym(loc)->toString() << std::endl << loc << std::endl;
		}
		exitingDEBUG("Definition");
		return new ASfuncDef(operand2, operand3, operand4, operand5);
	}

	AStype* TCparser::Type() // Functional Needs testing
	{
		// Type --> INT | CHAR
		TCtoken *t1, *t2;
		enteringDEBUG("Type");
		AStype* operand = NULL;
		if (buff->getTokenType() == INT)
		{
			t1 = buff;
			accept(INT);
			t2 = buff;
			operand = new AStype(t1, t2);
			exitingDEBUG(operand->toString());
			exitingDEBUG("Type");
		}
		else if (buff->getTokenType() == CHAR)
		{
			t1 = buff;
			accept(CHAR);
			t2 = buff;
			operand = new AStype(t1, t2);
			exitingDEBUG("Type");
		}
		else        // Error Handlding
		{
			reportSEMANTIC_ERROR(scanner, "type expected");
			exit(EXIT_FAILURE);
		}
		return operand;
	}

	ASstatement* TCparser::FunctionDefinition(ASdefinition* list[], int* i) // DONE NEED TO TEST MORE
	{
		// FunctionDefinition  --> FunctionHeader FunctionBody
		enteringDEBUG("Function Definition");
		ASstatement* operand = NULL;
		*i = FunctionHeader(list);
		operand = FunctionBody();
		exitingDEBUG("Function Definition");
		return operand;
	}

	int TCparser::FunctionHeader(ASdefinition* list[]) // DONE
	{
		//FunctionHeader --> LPAREN [ FormalParamList ] RPAREN
		enteringDEBUG("Function Header");
		accept(LPAREN);
		int i;
		if (buff->getTokenType() == INT || buff->getTokenType() == CHAR)
		{
			i = FormalParamList(list);
			accept(RPAREN);
			exitingDEBUG("Function Header");
		}
		else if (buff->getTokenType() == RPAREN)
		{
			i = 0;
			accept(RPAREN);
			exitingDEBUG("Function Header");
		}
		else      // Error Handlding
		{
			reportSEMANTIC_ERROR(scanner, "type or ')' expected");
			exit(EXIT_FAILURE);
		}
		return i;
	}

	ASstatement* TCparser::FunctionBody()  // DONE NEED TO TEST MORE
	{
		// FunctionBody --> CompoundStatement
		enteringDEBUG("Function Body");
		ASstatement* operand = NULL;
		operand = CompoundStatement();
		//CompoundStatement();
		exitingDEBUG("Function Body");
		return operand;
	}

	int TCparser::FormalParamList(ASdefinition* list[]) // DONE
	{
		// FormalParamList --> Type ID { COMMA Type ID }
		enteringDEBUG("Formal Param List");

        int loc; TCsymbol *sym;
		AStype* operand[1];
		operand[0] = Type();
        if (buff->getTokenType() == ID)
        {
            sym = symTable->getSym(buff);
            loc = symTable->find(buff->getLexeme());
            if (loc == -1) loc = symTable->add(new TCsymbol(buff->getLexeme(),NO_TYPE));
            symTable->getSym(loc)->setType(VAR);
            //std::cout << symTable->getSym(loc)->toString() << std::endl << loc << std::endl;

        }
		accept(ID);
		int i = 0;
		list[i] = new ASvarDef(operand, 1);
		i++;
		while (buff->getTokenType() == COMMA)
		{
			enteringDEBUG("Formal Param List Additional");
			accept(COMMA);
			operand[0] = Type();
            if (buff->getTokenType() == ID)
            {
                sym = symTable->getSym(buff);
                loc = symTable->find(buff->getLexeme());
                if (loc == -1) loc = symTable->add(new TCsymbol(buff->getLexeme(),NO_TYPE));
                symTable->getSym(loc)->setType(VAR);
                //std::cout << symTable->getSym(loc)->toString() << std::endl << loc << std::endl;
            }
			accept(ID);
			int i = 0;
			list[i] = new ASvarDef(operand, 1);
			i++;
			exitingDEBUG("Formal Param List Additional");
		}
		exitingDEBUG("Formal Param List");
		return i;
	}

	ASstatement* TCparser::ExpressionStatement() // WIP
	{
		// ExpressionStatement --> Expression
		enteringDEBUG("Expression Statement");
		ASexpression* operand = NULL;
		operand = Expression();
		exitingDEBUG("Expression Statement");
		accept(SEMICOLON);
		return new ASexprState(operand);
	}

	ASstatement* TCparser::CompoundStatement() // Need statment and error handling
	{
		// CompoundStatement --> LCURLY { Type ID SEMICOLON } { Statement } RCURLY
		enteringDEBUG("Compound Statement");

        int loc; TCsymbol *sym;
		ASdefinition* operand[MAX_STATEMENTS];
		ASstatement* operand2[MAX_STATEMENTS];
		AStype* operand4[1];
		int i1 = 0;
		int i2 = 0;
		accept(LCURLY);
		while (buff->getTokenType() == INT || buff->getTokenType() == CHAR) // { Type ID SEMICOLON }
		{
			operand4[0] = Type();
            if (buff->getTokenType() == ID)
            {
                sym = symTable->getSym(buff);
                loc = symTable->find(buff->getLexeme());
                if (loc == -1) loc = symTable->add(new TCsymbol(buff->getLexeme(),NO_TYPE));
                symTable->getSym(loc)->setType(VAR);
                //std::cout << symTable->getSym(loc)->toString() << std::endl << loc << std::endl;
            }
			accept(ID);
			operand[i1] = new ASvarDef(operand4, 1);
			i1++;
			accept(SEMICOLON);
		}
		try
		{
			enteringDEBUG("Statement");
			while (buff->getTokenType() != RCURLY)
			{
				operand2[i2] = Statement();
				i2++;
			}
		}
		catch (int t) {}
		accept(RCURLY);
		exitingDEBUG("Statement");
		exitingDEBUG("Compound Statement");
		return new ASblockState(operand, i1, operand2, i2);
	}


	ASstatement* TCparser::IfStatement() // WIP
	{
		// IfStatement --> IF LPAREN Expression RPAREN Statement [ ELSE Statement ]
		enteringDEBUG("If Statement");
		ASexpression* operand = NULL;
		ASstatement* operand2 = NULL;
		ASstatement* operand3 = NULL;
		accept(IF);
		accept(LPAREN);
		operand = Expression();
		accept(RPAREN);
		operand2 = Statement();
		if (buff->getTokenType() == ELSE)
		{
			enteringDEBUG("If Statement Additional");
			accept(ELSE);
			operand3 = Statement();
			exitingDEBUG("If Statement Additional");
			exitingDEBUG("If Statement");
			return new ASifState(operand, operand2, operand3);
		}
		exitingDEBUG("If Statement");
		return new ASifState(operand, operand2);
	}

	ASstatement* TCparser::Statement() // WIP
	{
		/* Statement --> ExpressionStatement
					   | BreakStatement
					   | CompoundStatement
					   | IfStatement
					   | NullStatement
					   | ReturnStatement
					   | WhileStatement
					   | ReadStatement
					   | WriteStatement
					   | NewLineStatement */
		ASstatement* operand = NULL;
		switch (buff->getTokenType())
		{
			case BREAK:
				operand = BreakStatement();
				break;

			case SEMICOLON:
				operand = NullStatement();
				break;

			case IF:
				operand = IfStatement();
				break;

			case RETURN:
				operand = ReturnStatement();
				break;

			case WHILE:
				operand = WhileStatement();
				break;

			case READ:
				operand = ReadStatement();
				break;

			case WRITE:
				operand = WriteStatement();
				break;

			case NEWLINE:
				operand = NewLineStatement();
				break;

			case LCURLY:
				operand = CompoundStatement();
				break;

			default:
				operand = ExpressionStatement();
				break;
		}
		return operand;
	}

	ASstatement* TCparser::BreakStatement() // DONE NEED TO TEST
	{
		// BreakStatement --> BREAK SEMICOLON
		enteringDEBUG("Break Statement");
		accept(BREAK);
		accept(SEMICOLON);
		exitingDEBUG("Break Statement");
		return new ASbreakState();
	}

	ASstatement* TCparser::NullStatement() // DONE NEED TO TEST
	{
		// SEMICOLON
		enteringDEBUG("Null Statement");
		exitingDEBUG("Null Statement");
		accept(SEMICOLON);
		return new ASnullState();
	}

	ASstatement* TCparser::ReturnStatement() // WIP
	{
		// RETURN [ Expression ] SEMICOLON
		enteringDEBUG("Return Statement");
		ASexpression* operand = NULL;
		accept(RETURN);
		try
		{
			operand = Expression();
			accept(SEMICOLON);
			exitingDEBUG("Return Statement");
			return new ASreturnState(operand);
		}
		catch (int t)
		{
			accept(SEMICOLON);
			exitingDEBUG("Return Statement");
			return new ASreturnState();
		}
	}

	ASstatement* TCparser::WhileStatement() // Testing
	{
		// WHILE LPAREN Expression RPAREN Statement
		enteringDEBUG("While Statement");
		ASexpression* operand = NULL;
		ASstatement* operand2 = NULL;
		accept(WHILE);
		accept(LPAREN);
		operand = Expression();
		accept(RPAREN);
		operand2 = Statement();
		exitingDEBUG("While Statement");
		return new ASwhileState(operand, operand2);
	}

	ASstatement* TCparser::ReadStatement() // WIP
	{
		// READ LPAREN ID { COMMA ID } RPAREN SEMICOLON
		enteringDEBUG("Read Statement");
		ASexpression* operand[MAX_STATEMENTS];
		accept(READ);
		accept(LPAREN);
		operand[0] = new ASsimpleExpr(accept(ID));
		int i = 1;
		while (buff->getTokenType() == COMMA)
		{
			enteringDEBUG("Read Statement Additional");
			accept(COMMA);
			operand[i] = new ASsimpleExpr(accept(ID));
			i++;
			exitingDEBUG("Read Statement Additional");
		}
		accept(RPAREN);
		exitingDEBUG("Read Statement");
		accept(SEMICOLON);
		return new ASreadState(operand, i);
	}

	ASstatement* TCparser::WriteStatement() // WIP
	{
		// WriteStatement -> WRITE LPAREN ActualParameters RPAREN SEMICOLON
		enteringDEBUG("Write Statement");
		ASexpression* operand = NULL;
		ASexpression* operand2[MAX_STATEMENTS];
		accept(WRITE);
		accept(LPAREN);
		operand = ActualParameters();
		operand2[0] = operand;
		accept(RPAREN);
		exitingDEBUG("Write Statement");
		accept(SEMICOLON);
		return new ASwriteState(operand2, 1);
	}

	ASstatement* TCparser::NewLineStatement() // WIP
	{
		// NewLineStatement --> NEWLINE SEMICOLON
		enteringDEBUG("NewLine Statement");
		accept(NEWLINE);
		exitingDEBUG("NewLine Statement");
		accept(SEMICOLON);
		return new ASnewLineState();
	}

	ASexpression* TCparser::Expression()  // WIP
	{
		// Expression --> RelopExpression { ASSIGNOP RelopExpression }
		enteringDEBUG("Expression");
		ASexpression* operand = NULL;
		ASexpression* operand2 = NULL;
		ASoperator* operand3 = NULL;
		operand = RelopExpression();
		while (buff->getTokenType() == ASSIGNOP)
		{
			enteringDEBUG("Expression Additional");
			operand3 = new ASoperator(accept(ASSIGNOP));
			operand2 = RelopExpression();
			operand = new ASexpr(operand3, operand2, operand);
			exitingDEBUG("Expression Additional");
		}
		exitingDEBUG("Expression");
		return operand;
	}

	ASexpression* TCparser::RelopExpression() // WIP
	{
		// RelopExpression --> SimpleExpression { RELOP SimpleExpression }
		enteringDEBUG("Relop Expression");
		ASexpression* operand = NULL;
		ASexpression* operand2 = NULL;
		ASoperator* operand3 = NULL;
		operand = SimpleExpression();
		while (buff->getTokenType() == RELOP)
		{
			enteringDEBUG("Relop Expression Additional");
			operand3 = new ASoperator(accept(RELOP));
			operand2 = SimpleExpression();
			operand = new ASexpr(operand3, operand2, operand);
			exitingDEBUG("RelopExpression Additional");
		}
		exitingDEBUG("Relop Expression");
		return operand;
	}

	ASexpression* TCparser::SimpleExpression() // WIP
	{
		// SimpleExpression --> Term { ADDOP Term }
		enteringDEBUG("Simple Expression");
		ASexpression* operand = NULL;
		ASexpression* operand2 = NULL;
		ASoperator* operand3 = NULL;
		operand = Term();
		while (buff->getTokenType() == ADDOP)
		{
			enteringDEBUG("Simple Expression Additional");
			operand3 = new ASoperator(accept(ADDOP));
			operand2 = Term();
			operand = new ASexpr(operand3, operand2, operand);
			exitingDEBUG("SimpleExpression Additional");
		}
		exitingDEBUG("Simple Expression");
		return operand;
	}

	ASexpression* TCparser::Term() // WIP
	{
		// Term --> Primary { MULOP Primary }
		enteringDEBUG("Term");
		ASexpression* operand = NULL;
		ASexpression* operand2 = NULL;
		ASoperator* operand3 = NULL;
		operand = Primary();
		while (buff->getTokenType() == MULOP)
		{
			enteringDEBUG("Term Additional");
			operand3 = new ASoperator(accept(MULOP));
			operand2 = Primary();
			operand = new ASexpr(operand3, operand2, operand);
			exitingDEBUG("Term Additional");
		}
		exitingDEBUG("Term");
		return operand;
	}

	ASexpression* TCparser::Primary() // DONE with AS
	{
		/* Primary --> ID [ FunctionCall ]
					 | NUMBER
					 | STRING
					 | CHARLITERAL
					 | LPAREN Expression RPAREN
					 | MINUS | NOT Primary */
		enteringDEBUG("Primary");
		ASexpression* operand = NULL;
		TCtoken* t = buff;
		//TCsymbol* sym;
		int tok = buff->getTokenType();
		switch (tok)
		{
			case ID:
				operand = new ASsimpleExpr(t);
				accept(ID);
				try
				{
					ASexpression* arr[] = { FunctionCall() };
					operand = new ASfuncCall(operand, arr, 1);
				}
				catch (int t)
				{
				}
				break;

			case NUMBER:
				operand = new ASsimpleExpr(t);
				accept(NUMBER);
				break;

			case STRING:
				operand = new ASsimpleExpr(t);
				accept(STRING);
				break;

			case CHARLITERAL:
				operand = new ASsimpleExpr(t);
				accept(CHARLITERAL);
				break;

			case LPAREN:
				enteringDEBUG("Primary Additional");
				accept(LPAREN);
				operand = Expression();
				exitingDEBUG("Primary Additional");
				accept(RPAREN);
				break;

			case MINUS:
				enteringDEBUG("Primary Additional");
				accept(MINUS);
				operand = new ASminus(Primary());
				exitingDEBUG("Primary Additional");
				break;

			case NOTEQUAL:
				enteringDEBUG("Primary Additional");
				accept(NOTEQUAL);
				operand = new ASnot(Primary());
				exitingDEBUG("Primary Additional");
				break;

			default:
				throw tok;
		}
		exitingDEBUG("Primary");
		return operand;
	}

	ASexpression* TCparser::FunctionCall() // WIP
	{
		// FunctionCall -- > LPAREN ActualParameters RPAREN
		enteringDEBUG("Function Call");
		ASexpression* operand = NULL;
		accept(LPAREN);
		try
		{
			operand = ActualParameters();
		}
		catch (int t)
		{
			operand = new ASexpression();
		}
		accept(RPAREN);
		exitingDEBUG("Function Call");
		return operand;
	}

	ASexpression* TCparser::ActualParameters() // WIP
	{
		// ActualParameters -> Expression { COMMA Expression }
		enteringDEBUG("Actual Parameters");
		ASexpression* operand = NULL;
		ASexpression* operand2[MAX_STATEMENTS];
		int i = 0;
		operand = Expression();
		while (buff->getTokenType() == COMMA)
		{
			enteringDEBUG("Actual Parameters Additional");
			accept(COMMA);
			operand2[i] = Expression();
			i++;
			exitingDEBUG("Actual Parameters Additional");
		}
		operand = new ASfuncCall(operand, operand2, i);
		exitingDEBUG("Actual Parameters");
		return operand;
	}

	/*
		   private static void enter_special_id(SymbolTable st, TCtoken.Tokens type) {
			   TCsymbol sym=null;
			   if (type == TCtoken.Tokens.READ)
				   sym = (TCsymbol)st.add("System.in");
			   else if (type == TCtoken.Tokens.WRITE)
				   sym=(TCsymbol)st.add("System.out");
			   sym.setAttribute(TCsymbol.Attributes.offset,new Integer(sym.getNextOffset()));
		   }
		 */

		 /*static void checkIfAllLabelTargetsAreDefined(ASprogram* p)
		 {
			 for (int i = 0; i < p->getNumStatements(); i++)
			 {
				 ASstatement* s = p->getStatement(i);
				 int label =
					 (s->getType() == GOTOstate) ? ((ASgotoState*)s)->getLabel() :
					 (s->getType() == IFstate) ? ((ASifState*)s)->getLabel() : -1;
				 if (label != -1)
				 {
					 std::string str = symTable->getSym(label)->getId();
					 if (!targetLabelExists(str, p))
					 {
						 reportSYNTAX_ERROR("target label '" + str + "' not found");
						 exit(EXIT_FAILURE);
					 }
				 }
			 }
		 }

		 static bool targetLabelExists(std::string str, ASprogram* p)
		 {
			 for (int i = 0; i < p->getNumStatements(); i++)
			 {
				 ASstatement* s = p->getStatement(i);
				 if (s->getType() == LABELstate)
				 {
					 ASlabelState* ls = (ASlabelState*)s;
					 if (str == symTable->getSym(ls->getLabel())->getId())
						 return true;
				 }
			 }
			 return false;
		 }
		 */
		 /*
		   private static void setSymbolAttributes(Lexer s, TCsymbol sym, String expected) {
			   String str;
			   if (sym.getAttributes().containsValue(str=(expected.equals("variable")?"label":"variable")))
				   TCoutput.reportSEMANTIC_ERROR(s,"'"+sym.getId()+"' is a "+str);
			   else
				   sym.setAttribute(TCsymbol.Attributes.type,expected);
			   if (expected.equals("variable") &&
				   !sym.getAttributes().containsKey(TCsymbol.Attributes.offset))
				   sym.setAttribute(TCsymbol.Attributes.offset,new Integer(sym.getNextOffset()));
		   }
		   */

	TCtoken* TCparser::accept(int t)
	{
		TCtoken *token; 
		std::string name;
		if (t == buff->getTokenType())
		{
			token = buff;
			name = token->getLexeme();
			//if (v_parser) {tokenDEBUG(name);}
			buff = scanner->getToken();
			return token;
		}
		else
		{
			throw t;
		}
	}

}
