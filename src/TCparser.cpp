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

	/*
   Concrete syntax
   ---------------
   program --> statementList
   statementList --> statement ; statementList | epsilon
   statement --> ID : statement |
				 ID = expr |
				 WRITE expr |
				 READ ID |
				 IF expr THEN GOTO ID |
				 GOTO ID |
				 SKIP
   expr --> term | term RELOP expr
   term --> element | element ADDOP term | element OR term
   element --> factor | factor MULOP element | factor AND element
   factor --> NUMBER | ID | - expr | ( expr )

   Abstract syntax
   ---------------
   Program --> prog(Id,(Statement*))
   Statement --> labeled(Id,Statement)
			   | assign(Id,Expression)
			   | write(Expression)
			   | read(Id)
			   | if(Expression,Id)
			   | goto(Id)
			   | skip()
   Expression --> Number | Id
				| binaryExpr(Operator, Expression, Expression)
				| unaryExpr(Operator, Expression)
  */

	static void checkIfAllLabelTargetsAreDefined(ASprogram*);

	static bool targetLabelExists(std::string, ASprogram*);

	TCparser::TCparser(TClexer* s) { scanner = s; }

	ASabstractSyntax* TCparser::parse()
	{
		buff = scanner->getToken();
		ASabstractSyntax* p = program();
		checkIfAllLabelTargetsAreDefined((ASprogram*)p);
		return p;
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

	int TCparser::Definition()
	{
		enteringDEBUG("Definition");
		Type();
		accept(ID);
		try
		{
			FunctionDefinition();
		}
		catch (int t)
		{
			accept(SEMICOLON);
		}
		exitingDEBUG("Definition");
		return 0;
	}

	int TCparser::Type()
	{
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

		return 0;
	}

	int TCparser::FunctionDefinition()
	{
		// FunctionDefinition  --> FunctionHeader FunctionBody
		enteringDEBUG("Function Definition");
		FunctionHeader();
		exitingDEBUG("Function Definition");
		FunctionBody();
		return 0;
	}

	int TCparser::FunctionHeader()
	{
		//FunctionHeader --> LPAREN [ FormalParamList ] RPAREN
		enteringDEBUG("FunctionHeader");
		accept(LPAREN);
		FormalParamList();
		accept(RPAREN);
		exitingDEBUG("FunctionHeader");
		return 0;
	}

	int TCparser::FunctionBody()
	{
		// FunctionBody --> CompoundStatement
		enteringDEBUG("FunctionBody");
		CompoundStatement();
		exitingDEBUG("FunctionBody");
		return 0;
	}

	int TCparser::FormalParamList()
	{
		// FormalParamList --> Type ID { COMMA Type ID }
		enteringDEBUG("FormalParamList");
		Type();
		accept(ID);
		while (true){
		try
		{
			enteringDEBUG("FormalParamList Additional");
			accept(COMMA);
			Type();
			accept(ID);
		}
		catch (int t)
		{
			exitingDEBUG("FormalParamList Additional");
			break;
		}
		}
		exitingDEBUG("FormalParamList");
		return 0;
	}

	int TCparser::ExpressionStatement()
	{
		// ExpressionStatement --> Expression
		enteringDEBUG("ExpressionStatement");
		exitingDEBUG("ExpressionStatement");
		return 0;
	}

	int TCparser::CompoundStatement()
	{
		// CompoundStatement --> LCURLY { Type ID SEMICOLON } { Statement } RCURLY
		enteringDEBUG("CompoundStatement");
		if (buff->getTokenType() == LCURLY)
		{
			buff = scanner->getToken();
			Type();
			accept(ID);
			accept(SEMICOLON);
			accept(RCURLY);
			accept(SEMICOLON);
			exitingDEBUG("CompoundStatement");
		}
		else
		{
			reportSEMANTIC_ERROR(scanner, "{ expected");
			exit(EXIT_FAILURE);
		}
		return 0;
	}

	int TCparser::IfStatement()
	{
		// IfStatement --> IF LPAREN Expression RPAREN Statement [ else Statement ]
		enteringDEBUG("IfStatement");
		buff = scanner->getToken();
		exitingDEBUG("IfStatement");
		return 0;
	}

	int TCparser::NullStatement()
	{
		// SEMICOLON
		enteringDEBUG("NullStatement");
		buff = scanner->getToken();
		exitingDEBUG("NullStatement");
		return 0;
	}

	int TCparser::ReturnStatement()
	{
		// RETURN [ Expression ] SEMICOLON
		enteringDEBUG("ReturnStatement");
		buff = scanner->getToken();
		exitingDEBUG("ReturnStatement");
		return 0;
	}


	int TCparser::WhileStatement()
	{
		// WHILE LPAREN Expression RPAREN Statement
		enteringDEBUG("WhileStatement");
		buff = scanner->getToken();
		exitingDEBUG("WhileStatement");
		return 0;
	}


	int TCparser::ReadStatement()
	{
		// READ LPAREN ID { COMMA ID } RPAREN SEMICOLON
		enteringDEBUG("ReadStatement");
		buff = scanner->getToken();
		exitingDEBUG("ReadStatement");
		return 0;
	}


	int TCparser::WriteStatement()
	{
		// WRITE LPAREN ActualParameters RPAREN SEMICOLON
		enteringDEBUG("WriteStatement");
		buff = scanner->getToken();
		exitingDEBUG("WriteStatement");
		return 0;
	}

	int TCparser::NewLineStatement()
	{
		// NewLineStatement --> NEWLINE SEMICOLON
		enteringDEBUG("NewLineStatement");
		buff = scanner->getToken();
		exitingDEBUG("NewLineStatement");
		return 0;
	}


	int TCparser::Expression()
	{
		// Expression --> RelopExpression { ASSIGNOP RelopExpression }
		enteringDEBUG("Expression");
		buff = scanner->getToken();
		exitingDEBUG("Expression");
		return 0;
	}


	int TCparser::RelopExpression()
	{
		// RelopExpression --> SimpleExpression { RELOP SimpleExpression }
		enteringDEBUG("RelopExpression");
		buff = scanner->getToken();
		exitingDEBUG("RelopExpression");
		return 0;
	}

	int TCparser::SimpleExpression()
	{
		// SimpleExpression --> Term { ADDOP Primary }
		enteringDEBUG("SimpleExpression");
		buff = scanner->getToken();
		exitingDEBUG("SimpleExpression");
		return 0;
	}

	int TCparser::Term()
	{
		// Term --> Primary { MULOP Primary }
		enteringDEBUG("Term");
		buff = scanner->getToken();
		exitingDEBUG("Term");
		return 0;
	}

	int TCparser::Primary()
	{
		// Primary --> ID [ FunctionCall }
		//           | NUMBER
		//           | STRING
		//           | CHARLITERAL
		//           | LPAREN Expression RPAREN
		//           | MINUS | NOT Primary
		enteringDEBUG("Primary");
		buff = scanner->getToken();
		exitingDEBUG("Primary");
		return 0;
	}
	int TCparser::FunctionCall()
	{
		// FunctionCall -- > LPAREN ActualParameters RPAREN
		enteringDEBUG("FunctionCall");
		exitingDEBUG("FunctionCall");
	}
	int TCparser::ActualParameters()
	{
		// Expression { COMMA Expression }
		enteringDEBUG("ActualParameters");
		buff = scanner->getToken();
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
					reportSEMANTIC_ERROR("target label '" + str + "' not found");
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
			buff = scanner->getToken();
		else
		{
			throw t;
			//reportSYNTAX_ERROR(scanner, str + " expected");
			//exit(EXIT_FAILURE);
		}
	}

}
