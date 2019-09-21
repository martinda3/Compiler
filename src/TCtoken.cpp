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
    case DO:	    	str += "DO";         	 			break;
    case IF: 			str += "IF";	          			break;
    case FOR: 			str += "FOR";	          			break;
    case INT: 			str += "INT";	          			break;
    case ELSE: 			str += "ELSE";          			break;
    case CHAR: 			str += "CHAR";          			break;
    case CASE: 			str += "CASE";          			break;
    case READ: 			str += "READ";          			break;
    case WHILE: 		str += "WHILE";          			break;
    case SWITCH: 		str += "SWITCH";          			break;
    case RETURN: 		str += "RETURN";          			break;
    case BREAK: 		str += "BREAK";          			break;
    case WRITE: 		str += "WRITE";        		  		break;
    case DEFAULT: 		str += "DEFAULT";    	      		break;
    case CONTINUE: 		str += "CONTINUE";          		break;
    case NEWLINE: 		str += "NEWLINE";          			break;
    case NUMBER:       	str += "(NUMBER, "+lexeme+")";   	break;
    case ADDOP:     	str += "(ADDOP, "+lexeme+")"; 		break;
    case MULOP:     	str += "(MULOP, "+lexeme+")"; 		break;
    case RELOP:     	str += "(RELOP, "+lexeme+")"; 		break;
    case DIVOP:     	str += "(DIVOP, "+lexeme+")"; 		break;
    case ASSIGNOP: 		str += "ASSIGNOP";		        	break;
    case ID:       		str += "(ID, "+lexeme+")";    		break;
    case CHARLITERAL:	str += "(CHARLITERAL, "+lexeme+")";	break;
    case STRING: 		str += "(STRING, "+lexeme+")";     	break;
    case COMMENT: 		str += "COMMENT";          			break;
    case BLOCK: 		str += "BLOCK";         			break;
    case LPAREN: 		str += "LPAREN";       	   			break;
    case RPAREN: 		str += "RPAREN";      	    		break;
    case NOT: 			str += "NOT";          				break;
    case COLON: 		str += "COLON";          			break;
    case LCURLY: 		str += "LCURLY";         	 		break;
    case RCURLY: 		str += "RCURLY";          			break;
    case LBRACKET: 		str += "LBRACKET";          		break;
    case RBRACKET: 		str += "RBRACKET";          		break;
    case COMMA: 		str += "COMMA";          			break;
    case SEMICOLON: 	str += "SEMICOLON";          		break;
    case AND: 		str += "AND";   	       		break;
    case OR: 		str += "OR";  	        		break;
    case GOTO: 		str += "GOTO";          		break;
    case SKIP: 		str += "SKIP";          		break;
    case NONE: 		str += "NONE";          		break;
    case EOFILE: 	str += "EOFILE";          		break;
    case THEN:      	str += "THEN";               		break;
    default:        	str += "[error token]";        		break; 
    }
    return str;
  }
  
}
