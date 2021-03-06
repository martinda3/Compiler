/*

   EGRE 591 Compiler Construction
   Created By: Dan Relser
   Modifed By: Dajion Martin & Charles Dieztel

 */

#include <iostream>
#include <fstream>
#include <string>

#include "TCtoken.h"
#include "TClexer.h"
#include "TCglobals.h"
#include "TCtokens.h"
#include "TCoutput.h"

using namespace std;
namespace toyc {

const int MAX_TOKENS {1000};
static char charBuff;
static char EOFCHAR {'\0'};
static unsigned int pos;
static int lineNum {0};
static int totalTokens {0};
int lineTemp; // May remove
int commentDepth {0};

bool commentFlag {false};
static string line {""};
static string lexeme {""};

static ifstream infile;

/// Opens file and begins the to iterates through input file
TClexer::TClexer(string fileName) {
    inputFileName = fileName;
    line = "";
    pos = 0;
    infile.open(inputFileName);
    if (infile.fail()) {
        cerr << "ERROR: input file not found" << endl;
        exit(EXIT_FAILURE);
    }
    charBuff = getChar();
}

/// Adds chars to lexeme untill legal token is found
/// If number of tokens greater than 1000 will force exit
/// When a token is found, the tokenFound flag will change.
/// While no new token, Scanner will look for a legal token
TCtoken *TClexer::getToken() {
    bool tokenFound = false;
    totalTokens++;
    lexeme = "";
    TCtoken *t;
    while (!tokenFound) {
        /// Stops endless loops
        tokenOverflow(totalTokens);
        /// Ignores white space
        ignoreWhiteSpaces();

        if (charBuff == EOFCHAR) {
            t = new TCtoken(EOFILE);
            if (!commentFlag) { tokenFound = true; }
            reportSCANNER("  ",
                          t->toString() + " " + to_string(totalTokens)
                                  + " tokens");
            return t;
        } /// NUMBER Tokens
        else if (isdigit(charBuff)) {
            int DECIMALS = 0;
            int EXPONENTS = 0;
            int FLAG = 0;
            do {
                lexeme += charBuff;
                charBuff = getChar();
                switch (charBuff) {
                    case '.':
                        if (DECIMALS > 0) {
                            DECIMALS++;
                            FLAG++;
                            reportWARNING("  ", " Semantic: cannot have two .");
                            t = new TCtoken(NUMBER, lexeme);
                            if (!commentFlag) { tokenFound = true; }
                        } else {
                            DECIMALS++;
                            lexeme += charBuff;
                        }
                        charBuff = getChar();
                        if (isalpha(charBuff)) {
                            lexeme += '0';
                            FLAG = 1;
                        }
                        break;
                    case 'E':
                        if (EXPONENTS > 0) {
                            EXPONENTS++;
                            FLAG++;
                            reportWARNING("  ",
                                          " Semantic: A number cannot have two E's");
                            t = new TCtoken(NUMBER, lexeme);
                            if (!commentFlag) { tokenFound = true; }
                        } else {
                            EXPONENTS++;
                            lexeme += charBuff;
                        }
                        charBuff = getChar();
                        if (!isdigit(charBuff)) {
                            if (charBuff == '+' || charBuff == '-') {
                                lexeme += charBuff;
                                charBuff = getChar();
                            } else if (!isdigit(charBuff)) {
                                lexeme += '1';
                                charBuff = getChar();
                                FLAG = 1;
                            }
                        }
                        break;
                }
            } while (FLAG != 1 && isdigit(charBuff));
            t = new TCtoken(NUMBER, lexeme);
            if (!commentFlag) { tokenFound = true; }
        } else if (isalpha(charBuff)) {
            do {
                lexeme += charBuff;
                charBuff = getChar();
            } while (isalpha(charBuff) || isdigit(charBuff));

            if (tokenChecker(lexeme, "WRITE")) {
                t = new TCtoken(WRITE, lexeme);
                if (!commentFlag) { tokenFound = true; }
            } else if (tokenChecker(lexeme, "READ")) {
                t = new TCtoken(READ,
                                lexeme);
                if (!commentFlag) { tokenFound = true; }
            } else if (tokenChecker(lexeme, "IF")) {
                t = new TCtoken(IF, lexeme);
                if (!commentFlag) { tokenFound = true; }
            } else if (tokenChecker(lexeme, "THEN")) {
                t = new TCtoken(THEN,
                                lexeme);
                if (!commentFlag) { tokenFound = true; }
            } else if (tokenChecker(lexeme, "GOTO")) {
                t = new TCtoken(GOTO,
                                lexeme);
                if (!commentFlag) { tokenFound = true; }
            } else if (tokenChecker(lexeme, "SKIP")) {
                t = new TCtoken(SKIP,
                                lexeme);
                if (!commentFlag) { tokenFound = true; }
            } else if (tokenChecker(lexeme, "AND")) {
                t = new TCtoken(AND,
                                lexeme);
                if (!commentFlag) { tokenFound = true; }
            } else if (tokenChecker(lexeme, "OR")) {
                t = new TCtoken(OR, lexeme);
                if (!commentFlag) { tokenFound = true; }
            } else if (tokenChecker(lexeme, "DO")) {
                t = new TCtoken(DO, lexeme);
                if (!commentFlag) { tokenFound = true; }
            } else if (tokenChecker(lexeme, "FOR")) {
                t = new TCtoken(FOR,
                                lexeme);
                if (!commentFlag) { tokenFound = true; }
            } else if (tokenChecker(lexeme, "INT")) {
                t = new TCtoken(INT,
                                lexeme);
                if (!commentFlag) { tokenFound = true; }
            } else if (tokenChecker(lexeme, "NEWLINE")) {
                t = new TCtoken(NEWLINE,
                                lexeme);
                if (!commentFlag) { tokenFound = true; }
            } else if (tokenChecker(lexeme, "ELSE")) {
                t = new TCtoken(ELSE,
                                lexeme);
                if (!commentFlag) { tokenFound = true; }
            } else if (tokenChecker(lexeme, "CHAR")) {
                t = new TCtoken(CHAR,
                                lexeme);
                if (!commentFlag) { tokenFound = true; }
            } else if (tokenChecker(lexeme, "CASE")) {
                t = new TCtoken(CASE,
                                lexeme);
                if (!commentFlag) { tokenFound = true; }
            } else if (tokenChecker(lexeme, "WHILE")) {
                t = new TCtoken(WHILE,
                                lexeme);
                if (!commentFlag) { tokenFound = true; }
            } else if (tokenChecker(lexeme, "SWITCH")) {
                t = new TCtoken(SWITCH,
                                lexeme);
                if (!commentFlag) { tokenFound = true; }
            } else if (tokenChecker(lexeme, "RETURN")) {
                t = new TCtoken(RETURN,
                                lexeme);
                if (!commentFlag) { tokenFound = true; }
            } else if (tokenChecker(lexeme, "BREAK")) {
                t = new TCtoken(BREAK,
                                lexeme);
                if (!commentFlag) { tokenFound = true; }
            } else if (tokenChecker(lexeme, "DEFAULT")) {
                t = new TCtoken(DEFAULT,
                                lexeme);
                if (!commentFlag) { tokenFound = true; }
            } else if (tokenChecker(lexeme, "CONTINUE")) {
                t = new TCtoken(CONTINUE,
                                lexeme);
                if (!commentFlag) { tokenFound = true; }
            } else if (tokenChecker(lexeme, "STRING")) {
                t = new TCtoken(STRING,
                                lexeme);
                if (!commentFlag) { tokenFound = true; }
            } else if (tokenChecker(lexeme, "NONE")) {
                t = new TCtoken(NONE,
                                lexeme);
                if (!commentFlag) { tokenFound = true; }
            } else {
                t = new TCtoken(ID, lexeme);
                if (!commentFlag) { tokenFound = true; }
            }
        } else {
            switch (charBuff) {
                case '+':
                    lexeme += charBuff;
                    t = new TCtoken(ADDOP, lexeme);
                    if (!commentFlag) { tokenFound = true; }
                    charBuff = getChar();
                    break;
                case '%':
                    lexeme += charBuff;
                    t = new TCtoken(MULOP, lexeme);
                    if (!commentFlag) { tokenFound = true; }
                    charBuff = getChar();
                    break;
                case '[':
                    lexeme += charBuff;
                    t = new TCtoken(LBRACKET, lexeme);
                    if (!commentFlag) { tokenFound = true; }
                    charBuff = getChar();
                    break;
                case ']':
                    lexeme += charBuff;
                    t = new TCtoken(RBRACKET, lexeme);
                    if (!commentFlag) { tokenFound = true; }
                    charBuff = getChar();
                    break;
                case '{':
                    lexeme += charBuff;
                    t = new TCtoken(LCURLY, lexeme);
                    if (!commentFlag) { tokenFound = true; }
                    charBuff = getChar();
                    break;
                case '}':
                    lexeme += charBuff;
                    t = new TCtoken(RCURLY, lexeme);
                    if (!commentFlag) { tokenFound = true; }
                    charBuff = getChar();
                    break;
                case '-':
                    lexeme += charBuff;
                    t = new TCtoken(MINUS, lexeme);
                    if (!commentFlag) { tokenFound = true; }
                    charBuff = getChar();
                    break;
                case '*':
                    if (commentFlag) {
                        char hold;
                        hold = getChar();
                        if (hold == '/') {
                            lexeme = "";
                            commentDepth--;
                            //reportDEBUG("  ", "SUBTR", " " + to_string(commentDepth));
                            charBuff = getChar();
                            break;
                        }
                    } else {
                        //reportDEBUG("  ", "lexi", lexeme);
                        lexeme += charBuff;
                        t = new TCtoken(MULTI, lexeme);
                        if (!commentFlag) {
                            tokenFound = true;
                            charBuff = getChar();
                            break;
                        }
                        break;
                    }
                    if (commentDepth == 0) {
                        commentFlag = false;
                        break;
                    }
                    break;
                case '(':
                    lexeme += charBuff;
                    t = new TCtoken(LPAREN, lexeme);
                    if (!commentFlag) { tokenFound = true; }
                    charBuff = getChar();
                    break;
                case ')':
                    lexeme += charBuff;
                    t = new TCtoken(RPAREN, lexeme);
                    if (!commentFlag) { tokenFound = true; }
                    charBuff = getChar();
                    break;
                case ';':
                    lexeme += charBuff;
                    t = new TCtoken(SEMICOLON, lexeme);
                    if (!commentFlag) { tokenFound = true; }
                    charBuff = getChar();
                    break;
                case ':':
                    lexeme += charBuff;
                    t = new TCtoken(COLON, lexeme);
                    if (!commentFlag) { tokenFound = true; }
                    charBuff = getChar();
                    break;
                case ',':
                    lexeme += charBuff;
                    t = new TCtoken(COMMA, lexeme);
                    if (!commentFlag) { tokenFound = true; }
                    charBuff = getChar();
                    break;
                case '<':
                    lexeme += charBuff;
                    charBuff = getChar();
                    if (charBuff == '=') {
                        lexeme += charBuff;
                        t = new TCtoken(RELOP, lexeme);
                        if (!commentFlag) { tokenFound = true; }
                        charBuff = getChar();
                        break;
                    } else {
                        t = new TCtoken(RELOP, lexeme);
                        if (!commentFlag) { tokenFound = true; }
                        break;
                    }
                case '|':
                    lexeme += charBuff;
                    charBuff = getChar();
                    if (charBuff == '|') {
                        lexeme += charBuff;
                        t = new TCtoken(OR, lexeme);
                        if (!commentFlag) { tokenFound = true; }
                        charBuff = getChar();
                        break;
                    } else {
                        reportWARNING("  ",
                                      " Syntax:  Missing | for OR operator");
                        lexeme = "";
                        charBuff = getChar();
                        break;
                    }
                case '&':
                    lexeme += charBuff;
                    charBuff = getChar();
                    if (charBuff == '&') {
                        lexeme += charBuff;
                        t = new TCtoken(AND, lexeme);
                        if (!commentFlag) { tokenFound = true; }
                        charBuff = getChar();
                        lexeme = "";
                        break;
                    } else {
                        reportWARNING("  ",
                                      " Syntax:  Missing & for AND operator");
                        charBuff = getChar();
                        break;
                    }
                case '>':
                    lexeme += charBuff;
                    charBuff = getChar();
                    if (charBuff == '=') {
                        lexeme += charBuff;
                        t = new TCtoken(RELOP, lexeme);
                        if (!commentFlag) { tokenFound = true; }
                        charBuff = getChar();
                        break;
                    } else {
                        t = new TCtoken(RELOP, lexeme);
                        if (!commentFlag) { tokenFound = true; }
                        charBuff = getChar();
                        break;
                    }
                case '!':
                    lexeme += charBuff;
                    charBuff = getChar();
                    if (charBuff == '=') {
                        lexeme += charBuff;
                        t = new TCtoken(NOTEQUAL, lexeme);
                        if (!commentFlag) { tokenFound = true; }
                        charBuff = getChar();
                        break;
                    } else {
                        t = new TCtoken(NOT, lexeme);
                        if (!commentFlag) { tokenFound = true; }
                        break;
                    }
                case '=':
                    lexeme += charBuff;
                    charBuff = getChar();
                    if (charBuff == '=') {
                        lexeme += charBuff;
                        t = new TCtoken(RELOP, lexeme);
                        if (!commentFlag) { tokenFound = true; }
                        charBuff = getChar();
                        break;
                    } else {
                        t = new TCtoken(ASSIGNOP, lexeme);
                        if (!commentFlag) { tokenFound = true; }
                        break;
                    }
                case '\"':
                    lexeme += charBuff;
                    lineTemp = lineNum;
                    charBuff = getChar();
                    if (charBuff == '\"') {
                        lexeme = "\"\"";
                        t = new TCtoken(STRING, lexeme);
                        if (!commentFlag) { tokenFound = true; }
                        charBuff = getChar();
                        break;
                    } else {
                        while (charBuff != '\"') {
                            lexeme += charBuff;
                            charBuff = getChar();
                            if (lineNum != lineTemp) {
                                reportWARNING("  ",
                                              " Syntax:  Missing \" for STRING");
                                charBuff = getChar();
                                break;
                            }
                        }
                        lexeme += charBuff;
                        t = new TCtoken(STRING, lexeme);
                        if (!commentFlag) { tokenFound = true; }
                        charBuff = getChar();
                        break;
                    }
                case '\'':
                    lexeme += charBuff;
                    charBuff = getChar();
                    if (charBuff == '\'') {
                        lexeme = "\'\'";
                        t = new TCtoken(CHARLITERAL, lexeme);
                        if (!commentFlag) { tokenFound = true; }
                        charBuff = getChar();
                        break;
                    } else {
                        lexeme += charBuff;
                        charBuff = getChar();
                        if (charBuff != '\'') {
                            reportWARNING("  ", "Char literal Error");
                            charBuff = getChar();
                            break;
                        } else {
                            lexeme += charBuff;
                            t = new TCtoken(CHARLITERAL, lexeme);
                            if (!commentFlag) { tokenFound = true; }
                            charBuff = getChar();
                            break;
                        }
                    }
                case '/':
                    lexeme = charBuff;
                    charBuff = getChar();
                    switch (charBuff) {
                        case '*':
                            lexeme += charBuff;
                            commentFlag = true;
                            commentDepth++;
                            //reportDEBUG("  ", "ADDIN", " " + to_string(commentDepth));
                            break;
                        case '/':
                            line = getNextLine();
                            lexeme = "";
                            break;
                    }
                    if (lexeme == "/" && charBuff != '*') {
                        t = new TCtoken(DIVOP, lexeme);
                        if (!commentFlag) { tokenFound = true; }
                        break;
                    }
                    charBuff = getChar();
                    break;
                default:
                    lexeme = "";
                    charBuff = getChar();
                    break;
            }
            if (commentDepth == 0) { commentFlag = false; }
            else { commentFlag = true; }
        }
    }
    reportSCANNER("  ", t->toString());
    //if (commentDepth!=0) { reportDEBUG("  ", "Comment", to_string(commentDepth)); }
    //if (v_scanner) { reportDEBUG("  ", "Lexeme",  lexeme); }
    return t;
}

string TClexer::getLine() { return line; }

string TClexer::getLexeme() { return lexeme; }

int TClexer::getPos() { return pos; }

int TClexer::getLineNum() { return lineNum; }

/// Loads the lookahead buffer
char getChar() {
    string holder;
    while (!infile.eof()) {
        if (line.empty() || pos > line.length()) {
            line = getNextLine();
            pos = 0;
        }
        char ch = line[pos];
        holder = ch;
        if ((ch == '.')) {
            if (isspace(line[pos + 1])) {
                reportWARNING("  ",
                              " Scanner: '.' Illegal Character. Ignoring");
                pos++;
            }
        }
        if (ch == '\0') {
            line = getNextLine();
            ch = line[pos];
        }
        if (isInAlphabet(ch) || isspace(ch)) { break; }
        else {
            reportWARNING("  ",
                          " Scanner: \'" + holder
                                  + "\' Illegal Character. Ignoring");
            break;
        }
        //return EOFCHAR;
        //break;
    }
    return line[pos++];
}

/// Called by getChar, reads inputFile one line at a time.
/// Returns a string, and resets the position.
/// Also used to for debugging by printing string to terminal. if (Verbose)
string getNextLine() {
    string line, num;
    getline(infile, line);
    line = line + " ";
    pos = 0;
    lineNum++;
    if (lineNum < 10) { num = "  "; }
    else if (lineNum < 99) { num = " "; }
    else if (lineNum < 999) { num = ""; }
    num += to_string(lineNum);
    if (verbose) reportDEBUG(" ", "INPUT", " " + num + ": " + line);
    return line;
}

/// Is called by getChar to determain if character is legal.
/// TODO: Make an issymble(char) fuction
bool isInAlphabet(char ch) {
    return (isalpha(ch) || isdigit(ch) || (ch == '%') || (ch == '+')
            || (ch == '-') || (ch == '*') || (ch == '/') ||
            (ch == '<') || (ch == '>') || (ch == '(') || (ch == ')')
            || (ch == '=') || (ch == ';') || (ch == ':') ||
            (ch == '!') || (ch == '[') || (ch == ']') || (ch == '{')
            || (ch == '}') || (ch == ',') || (ch == '|') ||
            (ch == '&') || (ch == '.') || (ch == '\\') || (ch == '\"')
            || (ch == '\''));
}

/// Is called by tokenChecker. Compares individual characters.
/// Takes the characters case into account
bool compareChar(char &c1, char &c2) {
    if (isupper(c1)) { return false; }
    else if (c1 == tolower(c2)) { return true; }
    return false;
}

///  Compares contents of the lexeme to the given token
bool tokenChecker(string str1, string str2) {
    return ((str1.size() == str2.size())
            && equal(str1.begin(), str1.end(), str2.begin(), &compareChar));
}

///  Ensures number of tokens does not exceed MAX_TOKENS
void tokenOverflow(int tokens) {
    if (tokens > MAX_TOKENS) {
        reportWARNING("  ",
                      " Lexer: Number of tokens exceeds "
                              + to_string(MAX_TOKENS) + ".");
        exit(EXIT_FAILURE);
    }

}

void ignoreWhiteSpaces() {
    while (isspace(charBuff) && (charBuff != EOFCHAR)) { charBuff = getChar(); }
}

}
