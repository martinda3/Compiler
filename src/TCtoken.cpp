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
    case DO:	    	str += "(<DO>, \""+lexeme+"\")";    	break;
    case IF: 			str += "(<IF>, \""+lexeme+"\")";	    break;
    case FOR: 			str += "(<FOR>, \""+lexeme+"\")";	    break;
    case INT: 			str += "(<INT>, \""+lexeme+"\")";	    break;
    case ELSE: 			str += "(<ELSE>, \""+lexeme+"\")";      break;
    case CHAR: 			str += "(<CHAR>, \""+lexeme+"\")";      break;
    case CASE: 			str += "(<CASE>, \""+lexeme+"\")";      break;
    case READ: 			str += "(<READ>, \""+lexeme+"\")";      break;
    case WHILE: 		str += "(<WHILE>, \""+lexeme+"\")";     break;
    case SWITCH: 		str += "(<SWITCH>, \""+lexeme+"\")";    break;
    case RETURN: 		str += "(<RETURN>, \""+lexeme+"\")";    break;
    case BREAK: 		str += "(<BREAK>, \""+lexeme+"\")";     break;
    case WRITE: 		str += "(<WRITE>, \""+lexeme+"\")";     break;
    case DEFAULT: 		str += "(<DEFAULT>, \""+lexeme+"\")";   break;
    case CONTINUE: 		str += "(<CONTINUE>, \""+lexeme+"\")";  break;
    case NEWLINE: 		str += "(<NEWLINE>, \""+lexeme+"\")";   break;
    case NUMBER:       	str += "(<NUMBER>, \""+lexeme+"\")";   	break;
    case ADDOP:     	str += "(<ADDOP>, \""+lexeme+"\")"; 	break;
    case MULOP:     	str += "(<MULOP>, \""+lexeme+"\")"; 	break;
    case RELOP:     	str += "(<RELOP>, \""+lexeme+"\")"; 	break;
    case DIVOP:     	str += "(<DIVOP>, \""+lexeme+"\")"; 	break;
    case ASSIGNOP: 		str += "(<ASSIGNOP>, \""+lexeme+"\")";	break;
    case ID:       		str += "(<ID>, \""+lexeme+"\")";    	break;
    case CHARLITERAL:	str += "(<CHARLITERAL, \""+lexeme+"\")";break;
    case STRING: 		str += "(<STRING>, \""+lexeme+"\")";    break;
    case COMMENT: 		str += "(<COMMENT>)";          			break;
    case BLOCK: 		str += "(<BLOCK>)";         			break;
    case LPAREN: 		str += "(<LPAREN>, \""+lexeme+"\")";    break;
    case RPAREN: 		str += "(<RPAREN>, \""+lexeme+"\")";    break;
    case NOT: 			str += "(<NOT>, \""+lexeme+"\")";       break;
    case COLON: 		str += "(<COLON>, \""+lexeme+"\")";     break;
    case LCURLY: 		str += "(<LCURLY>, \""+lexeme+"\")";    break;
    case RCURLY: 		str += "(<RCURLY>, \""+lexeme+"\")";    break;
    case LBRACKET: 		str += "(<LBRACKET>, \""+lexeme+"\")";  break;
    case RBRACKET: 		str += "(<RBRACKET>, \""+lexeme+"\")";  break;
    case COMMA: 		str += "(<COMMA>, \""+lexeme+"\")";     break;
    case SEMICOLON: 	str += "(<SEMICOLON>, \""+lexeme+"\")"; break;
    case AND: 		str += "(<AND>, \""+lexeme+"\")";   	    break;
    case OR: 		str += "(<OR>, \""+lexeme+"\")";  	        break;
    case GOTO: 		str += "(<GOTO>, \""+lexeme+"\")";          break;
    case SKIP: 		str += "(<SKIP>, \""+lexeme+"\")";          break;
    case NONE: 		str += "(<NONE>, \""+lexeme+"\")";          break;
    case EOFILE: 	str += "(<EOFILE>)";          				break;
    case THEN:      	str += "(<THEN>, \""+lexeme+"\")";      break;
    default:        	str += "[error token]";        			break; 
    }
    return str;
  }
  
}
