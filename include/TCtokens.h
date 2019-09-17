#ifndef TCTOKENS_H
#define TCTOKENS_H

namespace toycalc {
  
   enum tokens{ DO, IF, FOR, INT, ELSE, CHAR,	// Keywords
	   	CASE, READ, WHILE, SWITCH,	//
		RETURN, BREAK, WRITE, DEFAULT,	//
		CONTINUE, NEWLINE,		//
	   	NUMBER, RELOP, ADDOP, MULOP	// Math
		ASSIGNOP, 			// 
		ID, CHARLITERAL, STRING,	// Strings
	   	COMMENT, LCOMMENT, RCOMMENT	// Comments 
		LPAREN, RPAREN, NOT, COLON,	// Symbols
		LCURLY, RCURLY, LBRACKET,	//
		RBRACKET, COMMA, SEMICOLON, 	//
		AND, OR, GOTO, SKIP, NONE,	// Other 
		EOFILE };			//

}

#endif
