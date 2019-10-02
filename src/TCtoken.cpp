/*

   EGRE 591 Compiler Construction
   Created By: Dan Relser
   Modified By: Dajion Martin & Charles Dieztel

 */

#include <iostream>

#include "TCtoken.h"
#include "TCtokens.h"

namespace toyc {

    TCtoken::TCtoken() { tokenType = NONE; }                   // Returns if Error

    TCtoken::TCtoken(int t) {                                   // Returns token without lexeme
        tokenType = t;
        lexeme = "";
    }

    TCtoken::TCtoken(int t, std::string s) {                    // Returns token with lexeme
        tokenType = t;
        lexeme = s;
    }

    int TCtoken::getTokenType() { return tokenType; }           // Returns token object

    std::string TCtoken::getLexeme() { return lexeme; }         // Returns token object's lexeme

    std::string TCtoken::toString() {                           // These are the unquie token objects & token's type
        std::string str = "";
        switch (tokenType) {
            case DO:
                str += " token DO " + lexeme;
                break;
            case NOTEQUAL:
                str += " token NOTEQUAL> ,\"" + lexeme;
                break;
            case IF:
                str += " token IF " + lexeme;
                break;
            case FOR:
                str += " token FOR " + lexeme;
                break;
            case INT:
                str += " token INT " + lexeme;
                break;
            case ELSE:
                str += " token ELSE " + lexeme;
                break;
            case CHAR:
                str += " token CHAR " + lexeme;
                break;
            case CASE:
                str += " token CASE " + lexeme;
                break;
            case READ:
                str += " token READ " + lexeme;
                break;
            case WHILE:
                str += " token WHILE " + lexeme;
                break;
            case SWITCH:
                str += " token SWITCH " + lexeme;
                break;
            case RETURN:
                str += " token RETURN " + lexeme;
                break;
            case BREAK:
                str += " token BREAK " + lexeme;
                break;
            case WRITE:
                str += " token WRITE " + lexeme;
                break;
            case DEFAULT:
                str += " token DEFAULT " + lexeme;
                break;
            case CONTINUE:
                str += " token CONTINUE " + lexeme;
                break;
            case NEWLINE:
                str += " token NEWLINE " + lexeme;
                break;
            case NUMBER:
                str += " token NUMBER " + lexeme;
                break;
            case ADDOP:
                str += " token ADDOP " + lexeme;
                break;
            case MODOP:
                str += " token MODOP " + lexeme;
                break;
            case MULOP:
                str += " token MULOP " + lexeme;
                break;
            case RELOP:
                str += " token RELOP " + lexeme;
                break;
            case DIVOP:
                str += " token DIVOP " + lexeme;
                break;
            case ASSIGNOP:
                str += " token ASSIGNOP " + lexeme;
                break;
            case ID:
                str += " token ID " + lexeme;
                break;
            case CHARLITERAL:
                str += " token CHARLITERAL " + lexeme;
                break;
            case STRING:
                str += " token STRING " + lexeme;
                break;
            case COMMENT:
                str += " token COMMENT";                               // Does not return a lexeme
                break;
            case BLOCK:
                str += " token BLOCK";                                 // Does not return a lexeme
                break;
            case LPAREN:
                str += " token LPAREN " + lexeme;
                break;
            case RPAREN:
                str += " token RPAREN " + lexeme;
                break;
            case NOT:
                str += " token NOT " + lexeme;
                break;
            case COLON:
                str += " token COLON " + lexeme;
                break;
            case LCURLY:
                str += " token LCURLY " + lexeme;
                break;
            case RCURLY:
                str += " token RCURLY " + lexeme;
                break;
            case LBRACKET:
                str += " token LBRACKET " + lexeme;
                break;
            case RBRACKET:
                str += " token RBRACKET " + lexeme;
                break;
            case COMMA:
                str += " token COMMA " + lexeme;
                break;
            case SEMICOLON:
                str += " token SEMICOLON " + lexeme;
                break;
            case AND:
                str += " token AND " + lexeme;
                break;
            case OR:
                str += " token OR " + lexeme;
                break;
            case GOTO:
                str += " token GOTO " + lexeme;
                break;
            case SKIP:
                str += " token SKIP " + lexeme;
                break;
            case NONE:
                str += " token NONE " + lexeme;
                break;
            case EOFILE:
                str += " token EOFILE";
                break;
            case THEN:
                str += " token THEN " + lexeme;
                break;
            default:
                str += "[error token]";
                break;
        }
        return str;
    }

}
