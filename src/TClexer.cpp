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
	static char lastChar;
	static char EOFCHAR = '\0';

	static unsigned int pos;
	static int lineNum = 0;
	static int t_tokens = 0;
	int lineTemp;
	int commentDepth = 0;

	static std::string line;
	static std::string lexeme = "";

	static std::ifstream infile;

	//char getChar();
	//char commenter();
	//std::string getNextLine();
	//bool isInAlphabet(char);
	//bool tokenChecker(std::string, std::string);
	//void BlockComments();

	/// Opens file exits if file DNE
	TClexer::TClexer(std::string fname) {
		inputFileName = fname;
		line = ""; pos = 0;
		infile.open(inputFileName);
		if (infile.fail()) {
			std::cerr << "ERROR: input file not found" << std::endl;
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
		t_tokens++;
		lexeme = "";
		TCtoken *t;
		while (!tokenFound) {
			/// Stops endless loops
			if (t_tokens > 1000) { reportWARNING("  ", " System: More than 1000 tokens."); exit(EXIT_FAILURE); }
			/// Ignores white space
			while (isspace(charBuff) && (charBuff != EOFCHAR)) { charBuff = getChar(); }
			if (charBuff == EOFCHAR) {
				t = new TCtoken(EOFILE);
				tokenFound = true;
				if (v_scanner) reportDEBUG("  ", "SCANNER", t->toString()  + " " + std::to_string(t_tokens) + " tokens");
				return t;
			} /// NUMBER Tokens CD
			else if (isdigit(charBuff)) {
				int DECIMALS = 0;                                               // Counter for '.' DM
				int EXPONENTS = 0;                                              // Counter for 'E' DM
				int FLAG = 0;                                                   // Trigger for exiting state DM
				do {
					lexeme += charBuff;                                         // Previous character is good
					charBuff = getChar();                                       // Load charater into lookahead
					switch (charBuff) {                                         // Testing the lookahead buffer
						case '.':
							if (DECIMALS > 0) {                                 // There has been a '.' in current token
								DECIMALS++;                                     // Update counter for number of '.'
								FLAG++;                                         // Triggers Error: token is complete DM
								reportWARNING("  ", " Semantic: cannot have two .");
								t = new TCtoken(NUMBER, lexeme);                // New token
								tokenFound = true;
							}
							else {                                              // First '.' in current token
								DECIMALS++; lexeme += charBuff;                 // Update counter & load lookahead
							}                                                   // Before exiting, make sure next char safe
							charBuff = getChar();                               // Load next char into lookahead
							if (isalpha(charBuff)) {                            // If lookahead is not safe
								lexeme += '0'; FLAG = 1;                        // Add '0' after '.' & Exit state
							}
							break;
						case 'E':                                               // The following is the same approch as '.'
							if (EXPONENTS > 0) {
								EXPONENTS++;
								FLAG++;
								reportWARNING("  ", " Semantic: A number cannot have two E's");
								t = new TCtoken(NUMBER, lexeme);
								tokenFound = true;
							}
							else {
								EXPONENTS++; lexeme += charBuff;
							}
							charBuff = getChar();
							if (!isdigit(charBuff)) {
								if (charBuff == '+' || charBuff == '-') {
									lexeme += charBuff; charBuff = getChar();
								}
								else if (!isdigit(charBuff)) {                    // Add a '1' after the 'E' Sementics
									lexeme += '1'; charBuff = getChar(); FLAG = 1;
								}
							}
							break;
					}
				} while (FLAG != 1 && isdigit(charBuff));                         // TODO Fix this: functional but ugly
				t = new TCtoken(NUMBER, lexeme);
				tokenFound = true;
			}
			else if (isalpha(charBuff)) {
				do {
					lexeme += charBuff; charBuff = getChar();
				} while (isalpha(charBuff) || isdigit(charBuff));

				if (tokenChecker(lexeme, "WRITE"))         { t = new TCtoken(WRITE, lexeme);    tokenFound = true; }
				else if (tokenChecker(lexeme, "READ"))     { t = new TCtoken(READ, lexeme);     tokenFound = true; }
				else if (tokenChecker(lexeme, "IF"))       { t = new TCtoken(IF, lexeme);       tokenFound = true; }
				else if (tokenChecker(lexeme, "THEN"))     { t = new TCtoken(THEN, lexeme);     tokenFound = true; }
				else if (tokenChecker(lexeme, "GOTO"))     { t = new TCtoken(GOTO, lexeme);     tokenFound = true; }
				else if (tokenChecker(lexeme, "SKIP"))     { t = new TCtoken(SKIP, lexeme);     tokenFound = true; }
				else if (tokenChecker(lexeme, "AND"))      { t = new TCtoken(AND, lexeme);      tokenFound = true; }
				else if (tokenChecker(lexeme, "OR"))       { t = new TCtoken(OR, lexeme);       tokenFound = true; }
				else if (tokenChecker(lexeme, "DO"))       { t = new TCtoken(DO, lexeme);       tokenFound = true; }
				else if (tokenChecker(lexeme, "FOR"))      { t = new TCtoken(FOR, lexeme);      tokenFound = true; }
				else if (tokenChecker(lexeme, "INT"))      { t = new TCtoken(INT, lexeme);      tokenFound = true; }
				else if (tokenChecker(lexeme, "NEWLINE"))  { t = new TCtoken(NEWLINE, lexeme);  tokenFound = true; }
				else if (tokenChecker(lexeme, "ELSE"))     { t = new TCtoken(ELSE, lexeme);     tokenFound = true; }
				else if (tokenChecker(lexeme, "CHAR"))     { t = new TCtoken(CHAR, lexeme);     tokenFound = true; }
				else if (tokenChecker(lexeme, "CASE"))     { t = new TCtoken(CASE, lexeme);     tokenFound = true; }
				else if (tokenChecker(lexeme, "WHILE"))    { t = new TCtoken(WHILE, lexeme);    tokenFound = true; }
				else if (tokenChecker(lexeme, "SWITCH"))   { t = new TCtoken(SWITCH, lexeme);   tokenFound = true; }
				else if (tokenChecker(lexeme, "RETURN"))   { t = new TCtoken(RETURN, lexeme);   tokenFound = true; }
				else if (tokenChecker(lexeme, "BREAK"))    { t = new TCtoken(BREAK, lexeme);    tokenFound = true; }
				else if (tokenChecker(lexeme, "DEFAULT"))  { t = new TCtoken(DEFAULT, lexeme);  tokenFound = true; }
				else if (tokenChecker(lexeme, "CONTINUE")) { t = new TCtoken(CONTINUE, lexeme); tokenFound = true; }
				else if (tokenChecker(lexeme, "STRING"))   { t = new TCtoken(STRING, lexeme);   tokenFound = true; }
				else if (tokenChecker(lexeme, "NONE"))     { t = new TCtoken(NONE, lexeme);     tokenFound = true; }
				else                                       { t = new TCtoken(ID, lexeme);       tokenFound = true; }
			}
			else {
				switch (charBuff) {
					case '+':
						lexeme += charBuff;
						t = new TCtoken(ADDOP, lexeme);
						tokenFound = true;
						charBuff = getChar();
						break;
					case '%':
						lexeme += charBuff;
						t = new TCtoken(MODOP, lexeme);
						tokenFound = true;
						charBuff = getChar();
						break;
					case '[':
						lexeme += charBuff;
						t = new TCtoken(LBRACKET, lexeme);
						tokenFound = true;
						charBuff = getChar();
						break;
					case ']':
						lexeme += charBuff;
						t = new TCtoken(RBRACKET, lexeme);
						tokenFound = true;
						charBuff = getChar();
						break;
					case '{':
						lexeme += charBuff;
						t = new TCtoken(LCURLY, lexeme);
						tokenFound = true;
						charBuff = getChar();
						break;
					case '}':
						lexeme += charBuff;
						t = new TCtoken(RCURLY, lexeme);
						tokenFound = true;
						charBuff = getChar();
						break;
					case '-':
						lexeme += charBuff;
						t = new TCtoken(MINUS, lexeme);
						tokenFound = true;
						charBuff = getChar();
						break;
					case '*':
						char hold;
						hold = getChar();
						if (hold == '/')
						{
							charBuff = getChar();
							break;
						}
						else
						{
							lexeme += charBuff;
							t = new TCtoken(MULOP, lexeme);
							tokenFound = true;
							charBuff = getChar();
							break;
						}
						break;
					case '(':
						lexeme += charBuff;
						t = new TCtoken(LPAREN, lexeme);
						tokenFound = true;
						charBuff = getChar();
						break;
					case ')':
						lexeme += charBuff;
						t = new TCtoken(RPAREN, lexeme);
						tokenFound = true;
						charBuff = getChar();
						break;
					case ';':
						lexeme += charBuff;
						t = new TCtoken(SEMICOLON, lexeme);
						tokenFound = true;
						charBuff = getChar();
						break;
					case ':':
						lexeme += charBuff;
						t = new TCtoken(COLON, lexeme);
						tokenFound = true;
						charBuff = getChar();
						break;
					case ',':
						lexeme += charBuff;
						t = new TCtoken(COMMA, lexeme);
						tokenFound = true;
						charBuff = getChar();
						break;
					case '<':
						lexeme += charBuff;
						charBuff = getChar();
						if (charBuff == '=')
						{
							lexeme += charBuff;
							t = new TCtoken(RELOP, lexeme);
							tokenFound = true;
							charBuff = getChar();
							break;
						}
						else {
							t = new TCtoken(RELOP, lexeme);
							tokenFound = true;
							break;
						}
						break;

					case '|':
						lexeme += charBuff;
						charBuff = getChar();
						if (charBuff == '|')
						{
							lexeme += charBuff;
							t = new TCtoken(OR, lexeme);
							tokenFound = true;
							charBuff = getChar();
							break;
						} else
						{
							reportWARNING("  ", " Syntax:  Missing | for OR operator");
							lexeme = "";
							charBuff = getChar();
							break;
						}
						break;

					case '&':
						lexeme += charBuff;
						charBuff = getChar();
						if (charBuff == '&')
						{
							lexeme += charBuff;
							t = new TCtoken(AND, lexeme);
							tokenFound = true;
							charBuff = getChar();
							lexeme = "";
							break;
						}
						else {
							reportWARNING("  ", " Syntax:  Missing & for AND operator");
							charBuff = getChar();
							break;
						}
						break;

					case '>':
						lexeme += charBuff;
						charBuff = getChar();
						if (charBuff == '=')
						{
							lexeme += charBuff;
							t = new TCtoken(RELOP, lexeme);
							tokenFound = true;
							charBuff = getChar();
							break;
						}
						else {
							t = new TCtoken(RELOP, lexeme);
							tokenFound = true;
							charBuff = getChar();
							break;
						}
						break;

					case '!':
						lexeme += charBuff;
						charBuff = getChar();
						if (charBuff == '=')
						{
							lexeme += charBuff;
							t = new TCtoken(NOTEQUAL, lexeme);
							tokenFound = true;
							charBuff = getChar();
							break;
						}
						else {
							t = new TCtoken(NOT, lexeme);
							tokenFound = true;
							break;
						}
						break;

					case '=':
						lexeme += charBuff;
						charBuff = getChar();
						if (charBuff == '=')
						{
							lexeme += charBuff;
							t = new TCtoken(RELOP, lexeme);
							tokenFound = true;
							charBuff = getChar();
							break;
						}
						else {
							t = new TCtoken(ASSIGNOP, lexeme);
							tokenFound = true;
							break;
						}
						break;

					case '\"':
						lexeme += charBuff;
						lineTemp = lineNum;
						charBuff = getChar();
						if (charBuff == '\"')
						{
							lexeme = "\"\"";
							t = new TCtoken(STRING, lexeme);
							tokenFound = true;
							charBuff = getChar();
							break;
						}
						else {
							while (charBuff != '\"')
							{
								lexeme += charBuff;
								charBuff = getChar();
								if (lineNum != lineTemp)
								{
									reportWARNING("  ", " Syntax:  Missing \" for STRING");
									charBuff = getChar();
									break;
								}
							}
							lexeme += charBuff;
							t = new TCtoken(STRING, lexeme);
							tokenFound = true;
							charBuff = getChar();
							break;
						}
						break;

					case '\'':
						lexeme += charBuff;
						charBuff = getChar();
						if (charBuff == '\'')
						{
							lexeme = "\'\'";
							t = new TCtoken(CHARLITERAL, lexeme);
							tokenFound = true;
							charBuff = getChar();
							break;
						} else
						{
							lexeme += charBuff;
							charBuff = getChar();
							if (charBuff != '\'')
							{
								reportWARNING("  ", "Char literal Error");
								charBuff = getChar();
								break;
							} else
							{
								lexeme += charBuff;
								t = new TCtoken(CHARLITERAL, lexeme);
								tokenFound = true;
								charBuff = getChar();
								break;
							}
						}
						break;
						/// Block Comments
					case '/':
						int temp;
						lexeme = charBuff;
						charBuff = getChar();
						switch (charBuff)
						{
							case '/':
								lexeme = "";
								temp = lineNum;
								while (temp == lineNum) {charBuff = commenter();}
								charBuff = getChar();
								break;

							case '*':
								lexeme = "";
								bool quit = true;
								int blocks = 0;
								char last;
								blocks++;
								while (blocks != 0)
								{
									while (quit)
									{
										charBuff = commenter();

										if (charBuff == '/')
										{
											last = charBuff;
											charBuff = commenter();
											lexeme = "";
											if (charBuff == '*')
											{
												blocks++;
												lexeme = "";
											}
										} else if (charBuff == '*')
										{
											last = charBuff;
											charBuff = commenter();
											lexeme = "";
											if (charBuff == '/')
											{
												blocks--;
												lexeme = "";
												quit = false;
											}
										}
									}
									if (blocks != 0)
									{
										quit = true;
										lexeme = "";
									}
									else
									{
										lexeme = "";
										break;
									}
								}
								lexeme = "";
								break;
						}
						if (lexeme == "/") { t = new TCtoken(DIVOP, lexeme); tokenFound = true; break; }
						charBuff = getChar();
						break;
					default:
						lexeme += charBuff; t = new TCtoken(NONE, lexeme); tokenFound = true; break;
				}
			}
		}
		if (v_scanner) { reportDEBUG("  ", "SCANNER", t->toString()); }
		return t;
		}

	std::string TClexer::getLine() { return line; }

	std::string TClexer::getLexeme() { return lexeme; }

	int TClexer::getPos() { return pos; }

	int TClexer::getLineNum() { return lineNum; }

    /// Loads the lookahead buffer
	char getChar() {
		std::string holder;
		do {
			if (infile.eof()) { return EOFCHAR; }
			if (line.empty() || pos > line.length()) { line = getNextLine(); }
			char ch = line[pos]; holder = ch; lastChar = charBuff;
			if ((ch == '.')) {
				if (isspace(line[pos + 1])) {
					reportWARNING("  ", " Scanner: '.' Illegal Character. Ignoring"); pos++;
				}
			}
			if (ch == '\0') { line = getNextLine(); ch = line[pos]; }
			if (isInAlphabet(ch) || isspace(ch))  { break; }
			reportWARNING("  ", " Scanner: \'" + holder + "\' Illegal Character. Ignoring"); pos++;
			break;
		} while (true);
		return line[pos++];
		}

	///	Used for comments, does not return an illegal character warning
	char commenter() {
		do {
			if (infile.eof()) { return EOFCHAR; }
			if (line.empty() || pos > line.length())  { line = getNextLine(); }
			char ch = line[pos]; lastChar = charBuff;
			if (isInAlphabet(ch) || isspace(ch)) { break; }
			pos++;
		} while (true);
		return line[pos++];
	}

	/// Called by getChar, reads inputFile one line at a time.
	/// Returns a string, and resets the position.
	/// Also used to for debugging by printing string to terminal. if (Verbose)
	std::string getNextLine() {
		std::string line, num;
		std::getline(infile, line);
		line = line + " ";
		pos = 0;
		lineNum++;
		if (lineNum < 10) {num = "  ";}
		else if (lineNum < 99) {num = " ";}
		else if (lineNum < 999) {num = "";}
		num += std::to_string(lineNum);
		if (verbose) reportDEBUG(" ", "INPUT", " " + num + ": " + line);
		return line;
	}

	/// Is called by getChar to determain if character is legal.
	/// TODO: Make an issymble(char) fuction
	bool isInAlphabet(char ch) {

		return (isalpha(ch) || isdigit(ch) || (ch == '%') || (ch == '+') || (ch == '-') || (ch == '*') || (ch == '/') ||
		        (ch == '<') || (ch == '>') || (ch == '(') || (ch == ')') || (ch == '=') || (ch == ';') || (ch == ':') ||
		        (ch == '!') || (ch == '[') || (ch == ']') || (ch == '{') || (ch == '}') || (ch == ',') || (ch == '|') ||
		        (ch == '&') || (ch == '.') || (ch == '\\') || (ch == '\"') || (ch == '\''));
	}

	/// Is called by tokenChecker. Compares individual characters.
	/// Takes the characters case into account
	bool compareChar(char &c1, char &c2) {

		if (isupper(c1)) { return false; }
		else if (c1 == tolower(c2)) { return true; }
		return false;
		}

	///  Compares contents of the lexeme to the given token
	bool tokenChecker(std::string str1, std::string str2) {

		return ((str1.size() == str2.size()) && std::equal(str1.begin(), str1.end(), str2.begin(), &compareChar));
	}

}
