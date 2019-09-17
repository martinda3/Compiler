#include <iostream>

#include "TCtoken.h"
#include "TCtokens.h"

namespace toyc {

  TCtoken::TCtoken() { tokenType = NONE; }
  TCtoken::TCtoken(int t) { tokenType = t; lexeme = ""; }
  TCtoken::TCtoken(int t, std::string s) { tokenType = t; lexeme = s; }

  int TCtoken::getTokenType() { return tokenType; }
  std::string TCtoken::getLexeme() { return lexeme; }

  std::string TCtoken::toString() {
    std::string str="";
    switch (tokenType) {
    case DO:	    	str += "DO";         	 		break;
    case IF: 		str += "IF";	          		break;
    case FOR: 		str += "FOR";	          		break;
    case INT: 		str += "INT";	          		break;
    case ELSE: 		str += "ELSE";          		break;
    case CHAR: 		str += "CHAR";          		break;
    case CASE: 		str += "CASE";          		break;
    case READ: 		str += "READ";          		break;
    case WHILE: 	str += "WHILE";          		break;
    case SWITCH: 	str += "SWITCH";          		break;
    case RETURN: 	str += "SEMICOLON";          		break;
    case BREAK: 	str += "SEMICOLON";          		break;
    case WRITE: 	str += "SEMICOLON";          		break;
    case DEFAULT: 	str += "SEMICOLON";          		break;
    case CONTINUE: 	str += "SEMICOLON";          		break;
    case NEWLINE: 	str += "SEMICOLON";          		break;
    case NUMBER:       	str += "(NUM,"+lexeme+")";   		break;
    case ADDOP:     	str += "(ADDOP,"+lexeme+")"; 		break;
    case MULOP:     	str += "(MULOP,"+lexeme+")"; 		break;
    case RELOP:     	str += "(RELOP,"+lexeme+")"; 		break;
    case ASSIGNOP: 	str += "(ASSIGNOP,"+lexeme+")";         break;
    case ID:       	str += "(ID,"+lexeme+")";    		break;
    case CHARLITERAL:	str += "(CHARLITERAL,"+lexeme+")";	break;
    case STRING: 	str += "SEMICOLON";          		break;
    case COMMENT: 	str += "SEMICOLON";          		break;
    case LCOMMENT: 	str += "SEMICOLON";          		break;
    case RCOMMENT: 	str += "SEMICOLON";          		break;
    case LPAREN: 	str += "SEMICOLON";          		break;
    case RPAREN: 	str += "SEMICOLON";          		break;
    case NOT: 		str += "SEMICOLON";          		break;
    case COLON: 	str += "SEMICOLON";          		break;
    case LCURLY: 	str += "SEMICOLON";          		break;
    case RCURLY: 	str += "SEMICOLON";          		break;
    case LBRACKET: 	str += "SEMICOLON";          		break;
    case RBRACKET: 	str += "SEMICOLON";          		break;
    case COMMA: 	str += "SEMICOLON";          		break;
    case SEMICOLON: 	str += "SEMICOLON";          		break;
    case AND: 		str += "SEMICOLON";          		break;
    case OR: 		str += "SEMICOLON";          		break;
    case GOTO: 		str += "SEMICOLON";          		break;
    case SKIP: 		str += "SEMICOLON";          		break;
    case NONE: 		str += "SEMICOLON";          		break;
    case EOFILE: 	str += "SEMICOLON";          		break;
    case THEN:      	str += "THEN";               		break;
    default:        	str += "[error token]";        		break; 
    }
    return str;
  }
  
}
