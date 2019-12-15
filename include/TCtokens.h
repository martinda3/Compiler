/*

   EGRE 591 Compiler Construction
   Created By: Dajion Martin

 */

#ifndef TCTOKENS_H
#define TCTOKENS_H

namespace toyc {

    enum tokens {
        DO, IF, FOR, INT, ELSE, CHAR,
        CASE, READ, WHILE, SWITCH,
        RETURN, BREAK, WRITE, DEFAULT,
        CONTINUE, NEWLINE,
        NUMBER, MINUS, RELOP, ADDOP, MULOP,
        ASSIGNOP, DIVOP, NOTEQUAL,
        ID, CHARLITERAL, STRING,
        COMMENT, BLOCK,
        LPAREN, RPAREN, NOT, COLON,
        LCURLY, RCURLY, LBRACKET,
        RBRACKET, COMMA, SEMICOLON,
        AND, OR, GOTO, SKIP, NONE,
        EOFILE, THEN
    };

}

#endif
