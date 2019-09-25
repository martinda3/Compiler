/*
   EGRE 591 Compiler Construction
   Created By: Dan Relser
   Modifed By: Dajion Martin & Charles Dieztel

 */

#include <iostream>
#include <fstream>

#include "TCtoken.h"
#include "TClexer.h"
#include "TCglobals.h"
#include "TCtokens.h"
#include "TCoutput.h"

namespace toyc {

    static char charBuff;
    static char EOFCHAR = '\0';
    static int pos;
    static int lineNum = 0;
    static int t_tokens = 0;            // Counts Total number to tokens DM
    static std::string line;
    static std::string lexeme = "";
    static std::ifstream infile;

    char getChar();

    std::string getNextLine();

    bool isInAlphabet(char);

    bool tokenChecker(std::string, std::string);


    TClexer::TClexer(std::string fname) {
        inputFileName = fname;
        line = "";
        pos = 0;
        infile.open(inputFileName);
        if (infile.fail()) {
            std::cerr << "ERROR: input file not found" << std::endl;
            exit(EXIT_FAILURE);
        }
        charBuff = getChar();
    }

    TCtoken *TClexer::getToken() {
        t_tokens++;                                                 // Token counter DM
        lexeme = "";
        TCtoken *t;
        if (t_tokens > 100) {                                       // Breaks on infinite loops DM
            reportWARNING("  ", "Check this token");                // Returns problematic token DM
            reportDEBUG("  ", "SCANNER", t->toString());
            exit(EXIT_FAILURE);
        }

        while (isspace(charBuff) && (charBuff != EOFCHAR)) charBuff = getChar();
        if (charBuff == EOFCHAR) {
            t = new TCtoken(EOFILE);
            if (verbose) reportDEBUG("  ", "SCANNER", t->toString());
            reportDEBUG("  ", "SCANNER", " Total tokens: " + std::to_string(t_tokens));     // Returns token count DM
            return t;
        } else if (isdigit(charBuff)) {         // TODO Break up isdigit, isalpha, & issymbol into functions
            int dot = 0;           // Counter for '.' DM
            int EEE = 0;           // Counter for 'E' DM
            int ender = 0;         // Trigger for exiting state DM
            do {                                                            // Following was added by DM
                lexeme += charBuff;                                         // Previous character is good
                charBuff = getChar();                                       // Load charater into lookahead
                switch (charBuff) {                                         // Testing the lookahead buffer
                    case '.':
                        if (dot > 0) {                                      // There has been a '.' in current token
                            dot++;                                          // Update counter for number of '.'
                            ender++;                                        // Triggers Error: token is complete DM
                            reportWARNING("  ", " Two . in one number");    // Soft Exception DM
                            t = new TCtoken(NUMBER, lexeme);                // New token
                        } else {                                            // First '.' in current token
                            dot++;                                          // Update counter for number of '.'
                            lexeme += charBuff;                             // Lookahead buffer is safe; Continue
                        }                                                   // Before exiting, make sure next char safe
                        charBuff = getChar();                               // Load next char into lookahead
                        if (isalpha(charBuff)) {                            // If lookahead is not safe
                            lexeme += '0';                                  // Add '0' after '.'
                            ender = 1;                                      // Exit current state
                        }
                        break;
                    case 'E':                                               // The following is the same approch as '.'
                        if (EEE > 0) {
                            EEE++;
                            ender++;
                            reportWARNING("  ", " Two E in one number");
                            t = new TCtoken(NUMBER, lexeme);
                        } else {
                            EEE++;
                            lexeme += charBuff;
                        }
                        charBuff = getChar();
                        if (!isdigit(charBuff)) {
                            if (charBuff == '+' || charBuff == '-') {
                                lexeme += charBuff;
                                charBuff = getChar();
                            } else if (!isdigit(charBuff)) {
                                lexeme += '1';                              // Add a '1' after the 'E' for correctness
                                charBuff = getChar();
                                ender = 1;
                            }
                        }
                        break;
                }
            } while (ender != 1 && isdigit(charBuff));                      // TODO Fix this. It is functional but ugly
            t = new TCtoken(NUMBER, lexeme);
        } else if (isalpha(charBuff)) {
            do {
                lexeme += charBuff;
                charBuff = getChar();                                       // New/Modified keywords added by DM
            } while (isalpha(charBuff) || isdigit(charBuff));               // Largely unchanged; Added/Modified tokens
            if (tokenChecker(lexeme, std::string("WRITE")))
                t = new TCtoken(WRITE, lexeme);
            else if (tokenChecker(lexeme, "READ"))
                t = new TCtoken(READ, lexeme);
            else if (tokenChecker(lexeme, "IF"))
                t = new TCtoken(IF, lexeme);
            else if (tokenChecker(lexeme, "THEN"))
                t = new TCtoken(THEN, lexeme);
            else if (tokenChecker(lexeme, "GOTO"))
                t = new TCtoken(GOTO, lexeme);
            else if (tokenChecker(lexeme, "SKIP"))
                t = new TCtoken(SKIP, lexeme);
            else if (tokenChecker(lexeme, "AND"))
                t = new TCtoken(AND, lexeme);
            else if (tokenChecker(lexeme, "OR"))
                t = new TCtoken(OR, lexeme);
            else if (tokenChecker(lexeme, "DO"))
                t = new TCtoken(DO, lexeme);
            else if (tokenChecker(lexeme, "FOR"))
                t = new TCtoken(FOR, lexeme);
            else if (tokenChecker(lexeme, "INT"))
                t = new TCtoken(INT, lexeme);
            else if (tokenChecker(lexeme, "ELSE"))
                t = new TCtoken(ELSE, lexeme);
            else if (tokenChecker(lexeme, "CHAR"))
                t = new TCtoken(CHAR, lexeme);
            else if (tokenChecker(lexeme, "CASE"))
                t = new TCtoken(CASE, lexeme);
            else if (tokenChecker(lexeme, "WHILE"))
                t = new TCtoken(WHILE, lexeme);
            else if (tokenChecker(lexeme, "SWITCH"))
                t = new TCtoken(SWITCH, lexeme);
            else if (tokenChecker(lexeme, "RETURN"))
                t = new TCtoken(RETURN, lexeme);
            else if (tokenChecker(lexeme, "BREAK"))
                t = new TCtoken(BREAK, lexeme);
            else if (tokenChecker(lexeme, "DEFAULT"))
                t = new TCtoken(DEFAULT, lexeme);
            else if (tokenChecker(lexeme, "CONTINUE"))
                t = new TCtoken(CONTINUE, lexeme);
            else if (tokenChecker(lexeme, "STRING"))
                t = new TCtoken(STRING, lexeme);
            else if (tokenChecker(lexeme, "SKIP"))
                t = new TCtoken(SKIP, lexeme);
            else if (tokenChecker(lexeme, "NONE"))
                t = new TCtoken(NONE, lexeme);
            else if (tokenChecker(lexeme, "THEN"))
                t = new TCtoken(THEN, lexeme);
            else { t = new TCtoken(ID, lexeme); }
        } else {
            lexeme += charBuff;
            switch (charBuff) {                                             // Largely unchaged; Added other symbols DM
                case '+':
                    t = new TCtoken(ADDOP, lexeme);
                    charBuff = getChar();
                    break;
                case '%':                                                   // New DM
                    t = new TCtoken(MODOP, lexeme);
                    charBuff = getChar();
                    break;
                case '[':                                                   // New
                    t = new TCtoken(LBRACKET, lexeme);
                    charBuff = getChar();
                    break;
                case ']':                                                   // New
                    t = new TCtoken(RBRACKET, lexeme);
                    charBuff = getChar();
                    break;
                case '{':                                                   //
                    t = new TCtoken(LCURLY, lexeme);
                    charBuff = getChar();
                    break;
                case '}':                                                    //
                    t = new TCtoken(RCURLY, lexeme);
                    charBuff = getChar();
                    break;
                case '-':
                    t = new TCtoken(ADDOP, lexeme);
                    charBuff = getChar();
                    break;
                case '*':
                    t = new TCtoken(MULOP, lexeme);
                    charBuff = getChar();
                    break;
                case '/':                                                   // New DM
                    charBuff = getChar();
                    if (charBuff == '/') {                                  // If lookahead has a '/' -> inline comment
                        int temp = lineNum;                                 // Save value of current line
                        while (temp == lineNum) {                           // Wait till stare of newline
                            charBuff = getChar();                           // TODO Check if irrelevant
                        }
                        t = new TCtoken(COMMENT);                           // after succesfull newline return token
                        charBuff = getChar();       // TODO Check if comment should happen before or after a newline
                        break;
                    } else if (charBuff == '*') {                           // Block c
                        while (true) {
                            charBuff = getChar();
                            if (charBuff == EOFCHAR) {
                                reportWARNING("  ", "Block Comment Error");
                                exit(EXIT_FAILURE);
                            }
                            if (charBuff == '*') {
                                charBuff = getChar();
                                if (charBuff == '/') {
                                    t = new TCtoken(BLOCK);
                                    charBuff = getChar();
                                    break;
                                } else { continue; }
                            }
                        }
                        break;
                    } else {
                        t = new TCtoken(DIVOP, lexeme);
                        charBuff = getChar();
                        break;
                    }
                    break;
                case '<':
                    charBuff = getChar();
                    if (charBuff == '=') {
                        lexeme += charBuff;
                        t = new TCtoken(RELOP, lexeme);
                        charBuff = getChar();
                        break;
                    } else
                        t = new TCtoken(RELOP, lexeme);
                    break;
                case '|':
                    charBuff = getChar();
                    if (charBuff == '|') {
                        lexeme += charBuff;
                        t = new TCtoken(OR, lexeme);
                        charBuff = getChar();
                        break;
                    } else {
                        reportWARNING("  ", "Missing an |");
                        exit(EXIT_FAILURE);
                    }
                case '&':
                    charBuff = getChar();
                    if (charBuff == '&') {
                        lexeme += charBuff;
                        t = new TCtoken(AND, lexeme);
                        charBuff = getChar();
                        break;
                    } else {
                        reportWARNING("  ", "Missing an &");
                        exit(EXIT_FAILURE);
                    }
                case '>':
                    charBuff = getChar();
                    if (charBuff == '=') {
                        lexeme += charBuff;
                        t = new TCtoken(RELOP, lexeme);
                        charBuff = getChar();
                        break;
                    } else {
                        t = new TCtoken(RELOP, lexeme);
                        charBuff = getChar();
                        break;
                    }
                    break;
                case '!':
                    charBuff = getChar();
                    if (charBuff == '=') {
                        lexeme += charBuff;
                        t = new TCtoken(NOTEQUAL, lexeme);
                        charBuff = getChar();
                        break;
                    } else {
                        t = new TCtoken(NOT, lexeme);
                        charBuff = getChar();
                        break;
                    }
                case '(':
                    t = new TCtoken(LPAREN, lexeme);
                    charBuff = getChar();
                    break;
                case ')':
                    t = new TCtoken(RPAREN, lexeme);
                    charBuff = getChar();
                    break;
                case '=':
                    charBuff = getChar();
                    if (charBuff == '=') {
                        lexeme += charBuff;
                        t = new TCtoken(RELOP, lexeme);
                        charBuff = getChar();
                    } else
                        t = new TCtoken(ASSIGNOP, lexeme);
                    break;
                case '\"':
                    charBuff = getChar();
                    if (charBuff == '\"') {
                        lexeme = "IS_EMPTY";
                        t = new TCtoken(STRING, lexeme);
                        charBuff = getChar();
                        break;
                    } else {
                        while (charBuff != '\"') {
                            lexeme += charBuff;
                            charBuff = getChar();
                            if (charBuff == EOFCHAR) {
                                reportWARNING("  ", "String Error");
                                exit(EXIT_FAILURE);
                            }
                        }
                        lexeme += charBuff;
                        t = new TCtoken(STRING, lexeme);
                        charBuff = getChar();
                        break;
                    }
                case '\'':
                    charBuff = getChar();
                    if (charBuff == '\'') {
                        lexeme = "IS_EMPTY";
                        t = new TCtoken(CHARLITERAL, lexeme);
                        charBuff = getChar();
                        break;
                    } else {
                        lexeme += charBuff;
                        charBuff = getChar();
                        if (charBuff != '\'') {
                            reportWARNING("  ", "Char literal Error");
                            exit(EXIT_FAILURE);
                        } else {
                            lexeme += charBuff;
                            t = new TCtoken(CHARLITERAL, lexeme);
                            charBuff = getChar();
                            break;
                        }
                    }
                case '\\':
                    charBuff = getChar();
                    if (charBuff == 'n') {
                        lexeme += charBuff;
                        t = new TCtoken(NEWLINE, lexeme);
                        charBuff = getChar();
                        break;
                    } else {
                        reportWARNING("  ", "\\ Error");
                        exit(EXIT_FAILURE);
                    }
                case ';':
                    t = new TCtoken(SEMICOLON, lexeme);
                    charBuff = getChar();
                    break;
                case ':':
                    t = new TCtoken(COLON, lexeme);
                    charBuff = getChar();
                    break;
                case ',':
                    t = new TCtoken(COMMA, lexeme);
                    charBuff = getChar();
                    break;
                case '.':
                    reportWARNING("  ", "Bad symble");
                    charBuff = getChar(); //exit(EXIT_FAILURE);
                default:    // shouldn't happen!
                    t = new TCtoken(NONE, lexeme);
            }
        }
        if (verbose) reportDEBUG("  ", "SCANNER", t->toString());
        return t;
    }


    std::string TClexer::getLine() { return line; }

    std::string TClexer::getLexeme() { return lexeme; }

    int TClexer::getPos() { return pos; }

    int TClexer::getLineNum() { return lineNum; }

    char getChar() {                            // Handles getting the next character
        do {
            if (infile.eof()) return EOFCHAR;
            if (line.empty() || pos > line.length()) line = getNextLine();
            char ch = line[pos];
            if (((ch == '/') && (line[pos + 1] == '/')) || (ch == '\0')) {
                line = getNextLine();
                ch = line[pos];
            }
            if (isInAlphabet(ch) || isspace(ch)) break;
            reportWARNING("  ", "illegal character ignored 2");
            pos++;
        } while (true);
        return line[pos++];
    }

    std::string getNextLine() {                                     // Gets the next line in *.tc file
        std::string line;
        std::getline(infile, line);
        pos = 0;
        lineNum++;
        line = line + " ";
        //if (verbose) reportDEBUG("  ", " INPUT ",lineNum+ "" +line);          // Usure what this does DM
        return line;
    }

    bool isInAlphabet(char ch) {                                    // Handles the input stream DM
        return (isalpha(ch) || isdigit(ch) || (ch == '%') ||        // Added other symboles that are allowable DM
                (ch == '+') || (ch == '-') || (ch == '*') || (ch == '/') ||     // TODO: Make an issymble(char) fuction
                (ch == '<') || (ch == '>') || (ch == '(') || (ch == ')') ||
                (ch == '=') || (ch == ';') || (ch == ':') || (ch == '!') ||
                (ch == '[') || (ch == ']') || (ch == '{') || (ch == '}') ||
                (ch == ',') || (ch == '|') || (ch == '&') || (ch == '.') ||
                (ch == '\\') || (ch == '\"') || (ch == '\''));
    }

    bool compareChar(char &c1, char &c2) {                          // Compares individual chars, takes into account
        if (isupper(c1)) return false;                              // if a char is Uppercase or Lowercase DM
        else if (c1 == tolower(c2)) return true;
        return false;
    }

    bool tokenChecker(std::string str1, std::string str2) {         //  Compares lexeme to token DM
        return ((str1.size() == str2.size()) &&
                std::equal(str1.begin(), str1.end(), str2.begin(), &compareChar));
    }

}
