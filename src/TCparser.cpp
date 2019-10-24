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
#include "ASstatement.h"
#include "ASexpr.h"

#include "ASassignState.h"
#include "ASbinaryExpr.h"
#include "ASgotoState.h"
#include "ASifState.h"
#include "ASlabelState.h"
#include "ASreadState.h"
#include "ASsimpleExpr.h"
#include "ASskipState.h"
#include "ASunaryExpr.h"
#include "ASwriteState.h"

#include "ASbinaryExpr.h"

namespace toyc
{

	static void checkIfAllLabelTargetsAreDefined(ASprogram*);

	static bool targetLabelExists(std::string, ASprogram*);

	TCparser::TCparser(TClexer* s) { scanner = s; }

	ASabstractSyntax* TCparser::parse()
	{
		buff = scanner->getToken();
		try
		{
			ASabstractSyntax* p = program();
			checkIfAllLabelTargetsAreDefined((ASprogram*)p);
			return p;
		}
		catch (int t)
		{
			std::string error = "Expected token number " + std::to_string(t);
			reportSYNTAX_ERROR(scanner, error);
			exit(EXIT_FAILURE);
		}

	}

	void enteringDEBUG(std::string s) { if (verbose) reportDEBUG("    ", "PARSER", "entering " + s); }

	void tokenDEBUG(std::string s)    { if (verbose) reportDEBUG("       ", "INFO", " " + s); }

	void exitingDEBUG(std::string s)  { if (verbose) reportDEBUG("    ", "PARSER", "exiting " + s); }

	ASabstractSyntax* TCparser::program()
	{
		enteringDEBUG("Program");
		while (true)
		{
			try
			{
				Definition();
			}
			catch (int t)
			{
				accept(EOFILE);
				break;
			}
	}
	exitingDEBUG("Program");
	return 0;
	}

	int TCparser::Definition() // DONE
	{
		// Definition --> Type ID ( FunctionDefinition | SEMICOLON )
		enteringDEBUG("Definition");
		Type();
		accept(ID);
		try
		{
			if (buff->getTokenType() == SEMICOLON) {
				exitingDEBUG("Definition");
			}
			accept(SEMICOLON);
		}
		catch (int t)
		{
			FunctionDefinition();
			exitingDEBUG("Definition");
		}
		return 0;
	}

	int TCparser::Type() // Functional Needs testing
	{
		// Type --> INT | CHAR
		enteringDEBUG("Type");
		try
		{
			accept(INT);
			exitingDEBUG("Type");
		}
		catch (int t)
		{
			accept(CHAR);
			exitingDEBUG("Type");
		}
		// Error and Handling not done
		return 0;
	}

	int TCparser::FunctionDefinition() // DONE NEED TO TEST MORE
	{
		// FunctionDefinition  --> FunctionHeader FunctionBody
		enteringDEBUG("Function Definition");
		FunctionHeader();
		FunctionBody();
		exitingDEBUG("Function Definition");
		accept(SEMICOLON); // Accept is here so that parser output will be correct================================================================
		return 0;
	}

	int TCparser::FunctionHeader() // DONE
	{
		//FunctionHeader --> LPAREN [ FormalParamList ] RPAREN
		enteringDEBUG("Function Header");
		accept(LPAREN);
		if (buff->getTokenType() == INT || buff->getTokenType() == CHAR)
		{
			FormalParamList();
			exitingDEBUG("Function Header");
			accept(RPAREN);
		}
		else if (buff->getTokenType() == RPAREN)
		{
			reportSYNTAX_ERROR(scanner,"FormalParamList expected");
			exit(EXIT_FAILURE);
		}
		return 0;
	}

	int TCparser::FunctionBody()  // DONE NEED TO TEST MORE
	{
		// FunctionBody --> CompoundStatement
		enteringDEBUG("FunctionBody");
		CompoundStatement();
		accept(SEMICOLON);
		exitingDEBUG("FunctionBody");
		return 0;
	}

	int TCparser::FormalParamList() // DONE
	{
		// FormalParamList --> Type ID { COMMA Type ID }
		enteringDEBUG("Formal Param List");
		Type();
		accept(ID);
		if (buff->getTokenType() != RPAREN)
		{
			enteringDEBUG("Formal Param List Additional");
			while (buff->getTokenType() != RPAREN)
			{
				accept(COMMA);
				Type();
				accept(ID);
			}
			exitingDEBUG("Formal Param List Additional");
		}
		exitingDEBUG("Formal Param List");
		return 0;
	}

	int TCparser::ExpressionStatement() // WIP
	{
		// ExpressionStatement --> Expression
		enteringDEBUG("ExpressionStatement");
		Expression();
		exitingDEBUG("ExpressionStatement");
		accept(SEMICOLON);
		return 0;
	}

	int TCparser::CompoundStatement() // Need statment and error handling
	{
		// CompoundStatement --> LCURLY { Type ID SEMICOLON } { Statement } RCURLY
		enteringDEBUG("CompoundStatement");
		accept(LCURLY);
		while (buff->getTokenType() == INT || buff->getTokenType() == CHAR) // { Type ID SEMICOLON }
		{
			try
			{
				Type();
				accept(ID);
				accept(SEMICOLON);
			}
			catch (int t)
			{
				break;
			}
		}
		if (buff->getTokenType() != RCURLY)
		{
			enteringDEBUG("Statement");
		//}
		while (true)
		{
			if (buff->getTokenType() != RCURLY)
			{
				Statement();
			}
			else
			{
				exitingDEBUG("Statement");
				accept(RCURLY);
				exitingDEBUG("CompoundStatement");
				accept(SEMICOLON);
				break;
			}
		}
		}
		// Need to add error handling
		return 0;
	}

	int TCparser::IfStatement() // WIP
	{
		// IfStatement --> IF LPAREN Expression RPAREN Statement [ ELSE Statement ]
		enteringDEBUG("IfStatement");
		accept(IF);
		accept(LPAREN);
		Expression();
		accept(RPAREN);
		Statement();
		if (buff->getTokenType() == ELSE)
		{
			enteringDEBUG("IfStatement Additional");
			accept(ELSE);
			Statement();
			exitingDEBUG("IfStatement Additional");
		}
		exitingDEBUG("IfStatement");
		return 0;
	}

	int TCparser::Statement() // WIP
	{
		// Statement --> ExpressionStatement
		//             | BreakStatement
		//             | CompoundStatement
		//             | IfStatement
		//             | NullStatement
		//             | ReturnStatement
		//             | WhileStatement
		//             | ReadStatement
		//             | WriteStatement
		//             | NewLineStatement
		switch (buff->getTokenType())
		{
			case BREAK:
				BreakStatement();
				accept(SEMICOLON);
				break;

			case SEMICOLON:
				NullStatement();
				break;

			case IF:
				IfStatement();
				break;

			case RETURN:
				ReturnStatement();
				accept(SEMICOLON);
				break;

			case WHILE:
				WhileStatement();
				break;

			case READ:
				ReadStatement();
				break;

			case WRITE:
				WriteStatement();
				break;

			case NEWLINE:
				NewLineStatement();
				break;

			case LCURLY:
				CompoundStatement();
				break;

			default:
				break;
		}
		return 0;
	}

	int TCparser::BreakStatement() // DONE NEED TO TEST
	{
		// BreakStatement --> BREAK SEMICOLON
		enteringDEBUG("BreakStatement");
		exitingDEBUG("BreakStatement");
		accept(BREAK);
		return 0;
	}

	int TCparser::NullStatement() // DONE NEED TO TEST
	{
		// SEMICOLON
		enteringDEBUG("NullStatement");
		exitingDEBUG("NullStatement");
		accept(SEMICOLON);
		return 0;
	}

	int TCparser::ReturnStatement() // WIP
	{
		// RETURN [ Expression ] SEMICOLON
		enteringDEBUG("Return Statement");
		accept(RETURN);
		Expression(); //Not working
		exitingDEBUG("Return Statement");
		return 0;
	}

	int TCparser::WhileStatement() // WIP
	{
		// WHILE LPAREN Expression RPAREN Statement
		enteringDEBUG("While Statement");
		accept(WHILE);
		accept(LPAREN);
		Expression(); //Not working
		accept(RPAREN);
		Statement();
		exitingDEBUG("While Statement");
		return 0;
	}

	int TCparser::ReadStatement() // WIP
	{
		// READ LPAREN ID { COMMA ID } RPAREN SEMICOLON
		enteringDEBUG("ReadStatement");
		accept(READ);
		accept(LPAREN);
		accept(ID);
		if (buff->getTokenType() != RPAREN)
		{
			enteringDEBUG("ReadStatement Additional");
			while (buff->getTokenType() != RPAREN)
			{
				accept(COMMA);
				accept(ID);
			}
			exitingDEBUG("ReadStatement Additional");
		}
		accept(RPAREN);
		exitingDEBUG("ReadStatement");
		accept(SEMICOLON);
		return 0;
	}

	int TCparser::WriteStatement() // WIP
	{
		// WRITE LPAREN ActualParameters RPAREN SEMICOLON
		enteringDEBUG("WriteStatement");
		accept(WRITE);
		accept(LPAREN);
		ActualParameters();
		accept(RPAREN);
		exitingDEBUG("WriteStatement");
		accept(SEMICOLON);
		return 0;
	}

	int TCparser::NewLineStatement() // WIP
	{
		// NewLineStatement --> NEWLINE SEMICOLON
		enteringDEBUG("NewLineStatement");
		accept(NEWLINE);
		exitingDEBUG("NewLineStatement");
		accept(SEMICOLON);
		return 0;
	}

	int TCparser::Expression()  // WIP
	{
		// Expression --> RelopExpression { ASSIGNOP RelopExpression }
		enteringDEBUG("Expression");
		RelopExpression();
		if (buff->getTokenType() == ASSIGNOP)
		{
			enteringDEBUG("Expression Additional");
			accept(ASSIGNOP);
			RelopExpression();
			exitingDEBUG("Expression Additional");
		}
		else if (buff->getTokenType() == NOTEQUAL)
		{
			enteringDEBUG("Expression Additional");
			accept(NOTEQUAL);
			RelopExpression();
			exitingDEBUG("Expression Additional");
		}
		exitingDEBUG("Expression");
		return 0;
	}

	int TCparser::RelopExpression() // WIP
	{
		// RelopExpression --> SimpleExpression { RELOP SimpleExpression }
		enteringDEBUG("RelopExpression");
		SimpleExpression();
		if (buff->getTokenType() == RELOP)
		{
			enteringDEBUG("RelopExpression Additional");
			accept(RELOP);
			SimpleExpression();
			exitingDEBUG("RelopExpression Additional");
		}
		exitingDEBUG("RelopExpression");
		return 0;
	}

	int TCparser::SimpleExpression() // WIP
	{
		// SimpleExpression --> Term { ADDOP Primary }
		enteringDEBUG("SimpleExpression");
		Term();
		if (buff->getTokenType() == ADDOP)
		{
			enteringDEBUG("SimpleExpression Additional");
			accept(ADDOP);
			Term();
			exitingDEBUG("SimpleExpression Additional");
		}
		exitingDEBUG("SimpleExpression");
		return 0;
	}

	int TCparser::Term() // WIP
	{
		// Term --> Primary { MULOP Primary }
		enteringDEBUG("Term");
		Primary();
		if (buff->getTokenType() == MULOP)
		{
			enteringDEBUG("Term Additional");
			accept(MULOP);
			Primary();
			exitingDEBUG("Term Additional");
		}
		exitingDEBUG("Term");
		return 0;
	}

	int TCparser::Primary() // WIP
	{
		// Primary --> ID [ FunctionCall ]
		//           | NUMBER
		//           | STRING
		//           | CHARLITERAL
		//           | LPAREN Expression RPAREN
		//           | MINUS | NOT Primary
		enteringDEBUG("Primary");
		switch (buff->getTokenType())
		{
			case ID:
				accept(ID);
				//FunctionCall();
				break;

			case NUMBER:
				accept(NUMBER);
				break;

			case STRING:
				accept(STRING);
				break;

			case CHARLITERAL:
				accept(CHARLITERAL);
				break;

			case LPAREN:
				enteringDEBUG("Primary Additional");
				accept(LPAREN);
				Expression();
				exitingDEBUG("Primary Additional");
				accept(RPAREN);
				break;

			case NOTEQUAL:
				enteringDEBUG("Primary Additional");
				accept(NOTEQUAL);
				Primary();
				exitingDEBUG("Primary Additional");
				break;

			default:
				break;
		}
		exitingDEBUG("Primary");
		return 0;
	}

	int TCparser::FunctionCall() // WIP
	{
		// FunctionCall -- > LPAREN ActualParameters RPAREN
		enteringDEBUG("FunctionCall");
		accept(LPAREN);
		ActualParameters();
		accept(RPAREN);
		exitingDEBUG("FunctionCall");
		return 0;
	}

	int TCparser::ActualParameters() // WIP
	{
		// Expression { COMMA Expression }
		enteringDEBUG("ActualParameters");
		Expression();
		if (buff->getTokenType() != COMMA)
		{
			enteringDEBUG("ActualParameters Additional");
			while (buff->getTokenType() != RPAREN)
			{
				accept(COMMA);
				Expression();
			}
			exitingDEBUG("ActualParameters Additional");
		}
		exitingDEBUG("ActualParameters");
		return 0;
	}

	/*

	  int TCparser::statementList(ASstatement *l[],int n) {
		int num=0;
		// statementList --> statement ; statementList | epsilon
		enteringDEBUG("statementList");
		if (!(buff->getTokenType()==EOFILE)) {
		  l[n] = statement();
		  accept(SEMICOLON);
		  num = statementList(l,n+1);
		} else {
		  num = n;
		}
		exitingDEBUG("statementList");
		return num;
	  }

	  ASstatement *TCparser::statement() {
		ASstatement* s=NULL;
		int loc; TCsymbol *sym;
		enteringDEBUG("statement");
		if (buff->getTokenType() == ID) {
		  sym = symTable->getSym(buff);
		  loc = symTable->find(buff->getLexeme());
		  if (loc == -1) loc = symTable->add(new TCsymbol(buff->getLexeme(),NO_TYPE));
		  enum symType stype = symTable->getSym(loc)->getType();
		  buff = scanner->getToken();
		  if (buff->getTokenType() == COLON) {
			// statement --> ID : statement
			if (stype == NO_TYPE)
				symTable->getSym(loc)->setType(LABEL);
			else if (stype == VAR || stype == OFFSET) {
			  reportSEMANTIC_ERROR(scanner,"label expected");
			  exit(EXIT_FAILURE);
			} // else it's a LABEL - do nothing
			buff = scanner->getToken();
			s = new ASlabelState(loc,statement());
		  } else if (buff->getTokenType() == ASSIGNOP) {
			// statement --> ID = expr
			if (stype == NO_TYPE)
			  symTable->getSym(loc)->setType(VAR);
			else if (stype == LABEL || stype == OFFSET) {
			  reportSEMANTIC_ERROR(scanner,"variable expected");
			  exit(EXIT_FAILURE);
			} // else it's a VAR so do nothing
			buff = scanner->getToken();
			s = new ASassignState(loc,expr());
		   } else {
			reportSYNTAX_ERROR(scanner,"':' or '=' expected");
		exit(EXIT_FAILURE);
		  }
		} else if (buff->getTokenType() == WRITE) {
		  // statement --> WRITE expr
		  buff = scanner->getToken();
		  //            enter_special_id(TCglobals.symtable,TCtoken.Tokens.WRITE);
		  s = new ASwriteState(expr());
		} else if (buff->getTokenType() == READ) {
		  // statement --> READ ID
		  buff = scanner->getToken();
	//            enter_special_id(TCglobals.symtable,TCtoken.Tokens.READ);
		  if (buff->getTokenType() == ID) {
			loc = symTable->find(buff->getLexeme());
			if (loc >= 0) {
			  enum symType stype = symTable->getSym(loc)->getType();
			  if (stype == NO_TYPE)
				symTable->getSym(loc)->setType(VAR);
			  else if (stype == LABEL || stype == OFFSET) {
				reportSEMANTIC_ERROR(scanner,"variable expected");
				exit(EXIT_FAILURE);
			  } // else it's a VAR so do nothing
			} else if (loc == -1) loc = symTable->add(new TCsymbol(buff->getLexeme(),VAR));
			buff = scanner->getToken();
			s = new ASreadState(loc);
		  } else {
			reportSYNTAX_ERROR(scanner,"variable expected");
		exit(EXIT_FAILURE);
		  }
		} else if (buff->getTokenType() == IF) {
		  // statement --> IF expr THEN GOTO ID
		  buff = scanner->getToken();
		  ASexpr *cond = expr();
		  accept(THEN); accept(GOTO);
		  if (buff->getTokenType()!=ID) {
		reportSEMANTIC_ERROR(scanner,"illegal target for GOTO");
			exit(EXIT_FAILURE);
		  }
		  sym = symTable->getSym(buff);
		  loc = symTable->find(sym);
		  if (sym->getType()!=LABEL) {
			  if (sym->getType()==VAR) {
			reportSEMANTIC_ERROR(scanner,"illegal target for GOTO");
			exit(EXIT_FAILURE);
			  } else sym->setType(LABEL);
		  s = new ASifState(cond,loc);
		  buff = scanner->getToken();
		  } else {
			reportSYNTAX_ERROR(scanner,"label expected");
		exit(EXIT_FAILURE);
		  }
		} else if (buff->getTokenType() == GOTO) {
		  // statement --> GOTO ID
		  buff = scanner->getToken();
		  if (buff->getTokenType() == ID) {
			  sym = symTable->getSym(buff);
			  loc = symTable->find(sym);
			  if (sym->getType()!=LABEL) {
				if (sym->getType()==VAR) {
				  reportSEMANTIC_ERROR(scanner,"illegal target for GOTO");
				  exit(EXIT_FAILURE);
				} else sym->setType(LABEL);
			  }
			  s = new ASgotoState(loc);
			  buff = scanner->getToken();
		  } else
			reportSYNTAX_ERROR(scanner,"label expected");
		} else if (buff->getTokenType() == SKIP) {
				//statement --> SKIP
				buff = scanner->getToken();
				s = new ASskipState();
		} else {
		  reportSYNTAX_ERROR(scanner,"statement expected");
		  exit(EXIT_FAILURE);
		}
		exitingDEBUG("statement");
		return s;
	  }*/
	  /*
		ASexpr* TCparser::expr() {
		  // expr --> term | term RELOP expr
		  enteringDEBUG("expr");
		 // ASexpr* op1 = term(), *op2=NULL, *result=NULL;
		  TCtoken* oper = buff;
		  if ( buff->getTokenType() == RELOP ) {
			buff = scanner->getToken();
	  //      op2 = expr();
	   //     result = new ASbinaryExpr(oper,op1,op2);
		   } else
			result = op1;
		  exitingDEBUG("expr");
		  return result;
		  }
	  */
	  /* ASexpr* TCparser::term() {
		 // term --> element | element ADDOP term | element OR term
		 enteringDEBUG("term");
		 ASexpr *op1 = element(), *op2=NULL, *result=NULL;
		 TCtoken *oper = buff;
		 if ( ( buff->getTokenType() == ADDOP) ||
			  ( buff->getTokenType() == OR) ) {
		   buff = scanner->getToken();
		   op2 = term();
		   result = new ASbinaryExpr(oper,op1,op2);
		 } else result = op1;
		 exitingDEBUG("term");
		 return result;
	   }*/
	   /*
		 ASexpr* TCparser::element() {
		   // element --> factor | factor MULOP element | factor AND element
		   enteringDEBUG("element");
		   ASexpr *op1 = factor(), *op2=NULL, *result=NULL;
		   TCtoken *oper = buff;
		   if ( ( buff->getTokenType() == MULOP) ||
				( buff->getTokenType() == AND) ) {
			 buff = scanner->getToken();
			 op2 = element();
			 result = new ASbinaryExpr(oper,op1,op2);
		   } else
			 result = op1;
		   exitingDEBUG("element");
		   return result;
		 }

		 ASexpr* TCparser::factor() {
		   // factor --> NUMBER | ID | - expr | ( expr )
		   enteringDEBUG("factor");
		   ASexpr *operand=NULL;
		   TCtoken *t = buff;
		   TCsymbol *sym;
		   switch (buff->getTokenType()) {
		   case NUMBER:
			 buff = scanner->getToken();
			 operand = new ASsimpleExpr(t);
			 break;
		   case ID:
			 sym = symTable->getSym(buff);
			 if ( sym->getType() == NO_TYPE ) {
		   reportSEMANTIC_ERROR(scanner,"uninitialized variable");
		   exit(EXIT_FAILURE);
			 }
			 if ( sym->getType() == LABEL ) {
		   reportSEMANTIC_ERROR(scanner,"'"+sym->getId()+"' is a label");
		   exit(EXIT_FAILURE);
			 }
			 buff = scanner->getToken();
			 operand = new ASsimpleExpr(t);
			 break;
		   case ADDOP:
			 if (!(buff->getLexeme() == "-")) {
			   reportSYNTAX_ERROR(scanner,"unary - expected");
			   exit(EXIT_FAILURE);
			 }
			 buff = scanner->getToken();
			 operand = new ASunaryExpr(t,expr());
			 break;
		   case LPAREN:
			 buff = scanner->getToken();
			 operand = expr();
			 accept(RPAREN);
			 break;
		   default:
			 reportSYNTAX_ERROR(scanner,"NUM,ID,MINUS,or LPAREN expected");
			 exit(EXIT_FAILURE);
		   }
		   exitingDEBUG("factor");
		   return operand;
		 }
		 */
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

	static void checkIfAllLabelTargetsAreDefined(ASprogram* p)
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

	void TCparser::accept(int t)
	{
		if (t == buff->getTokenType())
		{
			buff = scanner->getToken();
		}
		else if (buff->getTokenType() == EOFILE)
		{
			exit(0);
		}
		else
		{
			throw t;
		}
	}

}
