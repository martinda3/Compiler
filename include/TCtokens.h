#ifndef TCTOKENS_H
#define TCTOKENS_H

namespace toyc {
  
   enum tokens{ DO, IF, FOR, INT, ELSE, CHAR,	// Keywords
	   	CASE, READ, WHILE, SWITCH,	//
		RETURN, BREAK, WRITE, DEFAULT,	//
		CONTINUE, NEWLINE,		//
	   	NUMBER, RELOP, ADDOP, MULOP,	// Math
		ASSIGNOP, DIVOP, NOTEQUAL,		// 
		ID, CHARLITERAL, STRING,	// Strings
	   	COMMENT, BLOCK,	// Comments 
		LPAREN, RPAREN, NOT, COLON,	// Symbols
		LCURLY, RCURLY, LBRACKET,	//
		RBRACKET, COMMA, SEMICOLON, 	//
		AND, OR, GOTO, SKIP, NONE,	// Other 
		EOFILE, THEN };			//

}

#endif
