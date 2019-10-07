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

namespace toyc
{

	static char charBuff;
	static char EOFCHAR = '\0';
	static unsigned int pos;                                                // Modified to compiletime warning
	static int lineNum = 0;
	static int t_tokens = 0;                                                // Counts Total number to tokens DM
	static std::string line;
	static std::string lexeme = "";
	static std::ifstream infile;
	int lineTemp;

	char getChar();

	std::string getNextLine();

	bool isInAlphabet(char);

	bool tokenChecker(std::string, std::string);


	TClexer::TClexer(std::string fname)
	{
		inputFileName = fname;
		line = "";
		pos = 0;
		infile.open(inputFileName);											// Opens the file to be compiled
		if (infile.fail())
		{												// Checks for an error opening the file
			std::cerr << "ERROR: input file not found" << std::endl;
			exit(EXIT_FAILURE);
		}
		charBuff = getChar();
	}

	TCtoken* TClexer::getToken()
	{
		bool tokenFound = false;
		t_tokens++;                                                         // Token counter DM
		lexeme = "";
		TCtoken* t;
		while (!tokenFound)														// This constantly checks to see if a valid token was found by the lexer.
		{
			// If not, then it continues scanning for one. CD
//reportWARNING("lexeme: ", lexeme);
			if (t_tokens > 1000)
			{                                              // Breaks on infinite loops DM
				reportWARNING("  ", " System: More than 100 tokens.");          // Returns problematic token DM
				//reportDEBUG("  ", "SCANNER", t->toString());					// Used for debugging
				exit(EXIT_FAILURE);
			}

			while (isspace(charBuff) && (charBuff != EOFCHAR)) charBuff = getChar();	// Ignore space charachters that are not at the end of the file
			if (charBuff == EOFCHAR)
			{											// If it is the EOF, report that and return an EOFILE token
				t = new TCtoken(EOFILE);
				tokenFound = true;
				if (verbose) reportDEBUG("  ", "SCANNER", t->toString());
				if (verbose) reportDEBUG("  ", "COUNTER", " Total tokens: " + std::to_string(t_tokens));	// Returns token count DM
				return t;
			}
			else if (isdigit(charBuff))											// TODO: add error handling for cases with more than one consecutive '.' or 'E'
			{																	// Code for detecting NUMBER Tokens CD
				int dot = 0;                                                    // Counter for '.' DM
				int EEE = 0;                                                    // Counter for 'E' DM
				int ender = 0;                                                  // Trigger for exiting state DM
				do
				{																// Following was added by DM
					lexeme += charBuff;                                         // Previous character is good
					charBuff = getChar();                                       // Load charater into lookahead
					switch (charBuff)
					{                                         // Testing the lookahead buffer
						case '.':
							if (dot > 0)
							{                                      // There has been a '.' in current token
								dot++;                                          // Update counter for number of '.'
								ender++;                                        // Triggers Error: token is complete DM
								reportWARNING("  ", " Semantic: A number cannot have two .'s");    // Soft Exception DM
								t = new TCtoken(NUMBER, lexeme);                // New token
								tokenFound = true;
							}
							else
							{                                            // First '.' in current token
								dot++;                                          // Update counter for number of '.'
								lexeme += charBuff;                             // Lookahead buffer is safe; Continue
							}                                                   // Before exiting, make sure next char safe
							charBuff = getChar();                               // Load next char into lookahead
							if (isalpha(charBuff))
							{                            // If lookahead is not safe
								lexeme += '0';                                  // Add '0' after '.'
								ender = 1;                                      // Exit current state
							}
							break;
						case 'E':                                               // The following is the same approch as '.'
							if (EEE > 0)
							{
								EEE++;
								ender++;
								reportWARNING("  ", " Semantic: A number cannot have two E's");
								t = new TCtoken(NUMBER, lexeme);
								tokenFound = true;
							}
							else
							{
								EEE++;
								lexeme += charBuff;
							}
							charBuff = getChar();
							if (!isdigit(charBuff))
							{
								if (charBuff == '+' || charBuff == '-')
								{
									lexeme += charBuff;
									charBuff = getChar();
								}
								else if (!isdigit(charBuff))
								{
									lexeme += '1';                              // Add a '1' after the 'E' for correctness
									charBuff = getChar();
									ender = 1;
								}
							}
							break;
					}
				}
				while (ender != 1 && isdigit(charBuff));                      // TODO Fix this. It is functional but ugly
				t = new TCtoken(NUMBER, lexeme);
				tokenFound = true;
			}
			else if (isalpha(charBuff))
			{
				do
				{
					lexeme += charBuff;
					charBuff = getChar();                                       // New/Modified keywords added by DM
				}
				while (isalpha(charBuff) || isdigit(charBuff));               // Largely unchanged; Added/Modified tokens
				if (tokenChecker(lexeme, std::string("WRITE")))					// The way this works is that the text for some tokens is 
				{
					t = new TCtoken(WRITE, lexeme);								// the uppercase version of the lexeme corresponding to that
					tokenFound = true;
				}
				else if (tokenChecker(lexeme, "READ"))							// token. So to determine the correct token to return, simply
				{
					t = new TCtoken(READ, lexeme);								// convert the token name to lowercase and check if it is
					tokenFound = true;
				}
				else if (tokenChecker(lexeme, "IF"))							// equal to the lexeme. If it is, then return that token.
				{
					t = new TCtoken(IF, lexeme);								// otherwise it is an ID, so return that token instead. CD
					tokenFound = true;
				}
				else if (tokenChecker(lexeme, "THEN"))
				{
					t = new TCtoken(THEN, lexeme);
					tokenFound = true;
				}
				else if (tokenChecker(lexeme, "GOTO"))
				{
					t = new TCtoken(GOTO, lexeme);
					tokenFound = true;
				}
				else if (tokenChecker(lexeme, "SKIP"))
				{
					t = new TCtoken(SKIP, lexeme);
					tokenFound = true;
				}
				else if (tokenChecker(lexeme, "AND"))
				{
					t = new TCtoken(AND, lexeme);
					tokenFound = true;
				}
				else if (tokenChecker(lexeme, "OR"))
				{
					t = new TCtoken(OR, lexeme);
					tokenFound = true;
				}
				else if (tokenChecker(lexeme, "DO"))
				{
					t = new TCtoken(DO, lexeme);
					tokenFound = true;
				}
				else if (tokenChecker(lexeme, "FOR"))
				{
					t = new TCtoken(FOR, lexeme);
					tokenFound = true;
				}
				else if (tokenChecker(lexeme, "INT"))
				{
					t = new TCtoken(INT, lexeme);
					tokenFound = true;
				}
				else if (tokenChecker(lexeme, "ELSE"))
				{
					t = new TCtoken(ELSE, lexeme);
					tokenFound = true;
				}
				else if (tokenChecker(lexeme, "CHAR"))
				{
					t = new TCtoken(CHAR, lexeme);
					tokenFound = true;
				}
				else if (tokenChecker(lexeme, "CASE"))
				{
					t = new TCtoken(CASE, lexeme);
					tokenFound = true;
				}
				else if (tokenChecker(lexeme, "WHILE"))
				{
					t = new TCtoken(WHILE, lexeme);
					tokenFound = true;
				}
				else if (tokenChecker(lexeme, "SWITCH"))
				{
					t = new TCtoken(SWITCH, lexeme);
					tokenFound = true;
				}
				else if (tokenChecker(lexeme, "RETURN"))
				{
					t = new TCtoken(RETURN, lexeme);
					tokenFound = true;
				}
				else if (tokenChecker(lexeme, "BREAK"))
				{
					t = new TCtoken(BREAK, lexeme);
					tokenFound = true;
				}
				else if (tokenChecker(lexeme, "DEFAULT"))
				{
					t = new TCtoken(DEFAULT, lexeme);
					tokenFound = true;
				}
				else if (tokenChecker(lexeme, "CONTINUE"))
				{
					t = new TCtoken(CONTINUE, lexeme);
					tokenFound = true;
				}
				else if (tokenChecker(lexeme, "STRING"))
				{
					t = new TCtoken(STRING, lexeme);
					tokenFound = true;
				}
				else if (tokenChecker(lexeme, "NONE"))
				{
					t = new TCtoken(NONE, lexeme);
					tokenFound = true;
				}
				else
				{
					t = new TCtoken(ID, lexeme);
					tokenFound = true;
				}
			}
			else
			{
				switch (charBuff)
				{                                             // Largely unchaged; Added other symbols DM
					case '+':
						lexeme += charBuff;
						t = new TCtoken(ADDOP, lexeme);
						tokenFound = true;
						charBuff = getChar();
						break;
					case '%':                                                   // New DM
						lexeme += charBuff;
						t = new TCtoken(MODOP, lexeme);
						tokenFound = true;
						charBuff = getChar();
						break;
					case '[':                                                   // New
						lexeme += charBuff;
						t = new TCtoken(LBRACKET, lexeme);
						tokenFound = true;
						charBuff = getChar();
						break;
					case ']':                                                   // New
						lexeme += charBuff;
						t = new TCtoken(RBRACKET, lexeme);
						tokenFound = true;
						charBuff = getChar();
						break;
					case '{':                                                   // New DM
						lexeme += charBuff;
						t = new TCtoken(LCURLY, lexeme);
						tokenFound = true;
						charBuff = getChar();
						break;
					case '}':                                                   // New DM
						lexeme += charBuff;
						t = new TCtoken(RCURLY, lexeme);
						tokenFound = true;
						charBuff = getChar();
						break;
					case '-':
						lexeme += charBuff;
						t = new TCtoken(ADDOP, lexeme);
						tokenFound = true;
						charBuff = getChar();
						break;
					case '*':
						lexeme += charBuff;
						t = new TCtoken(MULOP, lexeme);
						tokenFound = true;
						charBuff = getChar();
						break;
					case '/':                                                   // New symbol DM
						//reportWARNING("lexeme1: ", lexeme);
						charBuff = getChar();
						if (charBuff == '/')
						{                                  // If lookahead has a '/' -> inline comment
							int temp = lineNum;                                 // Save value of current line
							while (temp == lineNum)
							{                           // Wait till stare of newline
								//reportWARNING("lexeme2: ", lexeme);
								charBuff = getChar();
							}
							break;						// TODO Check if comment should happen before or after a newline
						}
						else if (charBuff == '*')
						{                           // Block Comment
							int commentDepth = 1;		// One block comment has started, so begin scanning for more nested comments or a closing comment CD
							while (commentDepth > 0)	// Continue scanning while each block comment does not have a matching closing pair CD
							{
								//reportWARNING("lexeme3: ", lexeme);
								charBuff = getChar();
								if (charBuff == EOFCHAR)
								{                      // Error handling for EOF
									//reportWARNING("  ", " Syntax: Missing */ for Block Comment");
								}
								else if (charBuff == '/')	// If more nested comments are found, block comment depth increases CD
								{
									//reportWARNING("lexeme4: ", lexeme);
									charBuff = getChar();
									if (charBuff == '*')
									{
										commentDepth++;
									}
								}
								else if (charBuff == '*')	// If more nested comment closures are found, block comment depth decreases CD
								{                          // If '*'
									//reportWARNING("lexeme5: ", lexeme);
									charBuff = getChar();                       // Load lookahead again
									if (charBuff == '/')
									{                      // If '/' then Block Comment
										commentDepth--;
									}
								}
							}
							break;
						}
						else
						{
							lexeme += charBuff;
							t = new TCtoken(DIVOP, lexeme);                     // If not Comment or Block Comment, DIVOP
							tokenFound = true;
							//reportWARNING("lexeme6: ", lexeme);
							charBuff = getChar();
							break;
						}
						break;
					case '<':													// Checks for < or <= CD 
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
						else
						{
							t = new TCtoken(RELOP, lexeme);
							tokenFound = true;
						}
						break;
					case '|':                                                   // Checks for ||, ignores |
						lexeme += charBuff;
						charBuff = getChar();
						if (charBuff == '|')
						{
							lexeme += charBuff;
							t = new TCtoken(OR, lexeme);
							tokenFound = true;
							charBuff = getChar();
							break;
						}
						else
						{
							reportWARNING("  ", " Syntax:  Missing | for OR operator");
							lexeme = "";
							charBuff = getChar();
							break;
						}
						break;
					case '&':													// Checks for &&, ignores &
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
						else
						{
							reportWARNING("  ", " Syntax:  Missing & for AND operator");
							charBuff = getChar();
						}
						break;
					case '>':													// Checks for > or >= CD
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
						else
						{
							t = new TCtoken(RELOP, lexeme);
							tokenFound = true;
							charBuff = getChar();
							break;
						}
						break;
					case '!':													// Checks for ! CD
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
						else
						{
							t = new TCtoken(NOT, lexeme);
							tokenFound = true;
							charBuff = getChar();
							break;
						}
						break;
					case '(':													// Checks for ( CD
						lexeme += charBuff;
						t = new TCtoken(LPAREN, lexeme);
						tokenFound = true;
						charBuff = getChar();
						break;
					case ')':													// Checks for ) CD
						lexeme += charBuff;
						t = new TCtoken(RPAREN, lexeme);
						tokenFound = true;
						charBuff = getChar();
						break;
					case '=':													// Checks for = or == CD
						lexeme += charBuff;
						charBuff = getChar();
						if (charBuff == '=')
						{
							lexeme += charBuff;
							t = new TCtoken(RELOP, lexeme);
							tokenFound = true;
							charBuff = getChar();
						}
						else
						{
							t = new TCtoken(ASSIGNOP, lexeme);
							tokenFound = true;
						}
						break;
					case '\"':													// Checks for strings and empty strings CD
						lexeme += charBuff;
						lineTemp = lineNum;
						charBuff = getChar();
						if (charBuff == '\"')
						{
							lexeme = "IS_EMPTY";
							t = new TCtoken(STRING, lexeme);
							tokenFound = true;
							charBuff = getChar();
							break;
						}
						else
						{
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
					case '\'':													// Checks for chars and empty chars CD
						lexeme += charBuff;
						charBuff = getChar();
						if (charBuff == '\'')
						{
							lexeme = "IS_EMPTY";
							t = new TCtoken(CHARLITERAL, lexeme);
							tokenFound = true;
							charBuff = getChar();
							break;
						}
						else
						{
							lexeme += charBuff;
							charBuff = getChar();
							if (charBuff != '\'')
							{
								reportWARNING("  ", "Char literal Error");
								charBuff = getChar();
							}
							else
							{
								lexeme += charBuff;
								t = new TCtoken(CHARLITERAL, lexeme);
								tokenFound = true;
								charBuff = getChar();
								break;
							}
						}
						break;
					case '\\':													// Checks for newline characters CD
						lexeme += charBuff;
						charBuff = getChar();
						if (charBuff == 'n')
						{
							lexeme += charBuff;
							t = new TCtoken(NEWLINE, lexeme);
							tokenFound = true;
							charBuff = getChar();
							break;
						}
						else
						{
							reportWARNING("  ", " Scanner: Illegal Character. Ignoring");
							charBuff = getChar();
							break;
						}
						break;
					case ';':													// Checks for semicolons CD
						lexeme += charBuff;
						t = new TCtoken(SEMICOLON, lexeme);
						tokenFound = true;
						charBuff = getChar();
						break;
					case ':':													// Checks for colons CD
						lexeme += charBuff;
						t = new TCtoken(COLON, lexeme);
						tokenFound = true;
						charBuff = getChar();
						break;
					case ',':													// Checks for commas CD
						lexeme += charBuff;
						t = new TCtoken(COMMA, lexeme);
						tokenFound = true;
						charBuff = getChar();
						break;
					default:													// Should not happen
						lexeme += charBuff;
						t = new TCtoken(NONE, lexeme);							//TODO: Possibly add report here for if default case is reached (for debug purposes)?
						tokenFound = true;
						break;

				}
			}
		}
		if (verbose) reportDEBUG("  ", "SCANNER", t->toString());			// In verbose mode, reports each scanned lexeme and token CD
		return t;
	}


	std::string TClexer::getLine() { return line; }

	std::string TClexer::getLexeme() { return lexeme; }

	int TClexer::getPos() { return pos; }

	int TClexer::getLineNum() { return lineNum; }

	char getChar()
	{														// Handles getting the next character
		do
		{
			if (infile.eof()) return EOFCHAR;
			if (line.empty() || pos > line.length()) line = getNextLine();
			char ch = line[pos];
			if ((ch == '.'))
			{
				if (isspace(line[pos + 1]))
				{
					reportWARNING("  ", " Scanner: Illegal Character. Ignoring");
					pos++;
				}
			}
			if (ch == '\0')
			{
				line = getNextLine();
				ch = line[pos];
			}
			if (isInAlphabet(ch) || isspace(ch)) break;
			//reportWARNING("  ", " Scanner: Illegal Character. Ignoring3"); NOTE: This is commented, because in a comment
			pos++;	// Any character is valid, so you can't rely on this simple sort of error logic.
		}
		while (true);
		//reportWARNING("getChar: ", std::string(1, line[pos + 1]));
		return line[pos++];
	}

	std::string getNextLine()
	{												// Gets the next line in *.tc file
		std::string line;
		std::getline(infile, line);
		pos = 0;
		lineNum++;
		line = line + " ";
		//if (verbose) reportDEBUG("  ", " INPUT ",lineNum+ "" +line);		// Usure what this does DM
		return line;
	}

	bool isInAlphabet(char ch)
	{											// Handles the input stream DM
		return (isalpha(ch) || isdigit(ch) || (ch == '%') ||				// Added other symboles that are allowable DM
			(ch == '+') || (ch == '-') || (ch == '*') || (ch == '/') || // TODO: Make an issymble(char) fuction
				(ch == '<') || (ch == '>') || (ch == '(') || (ch == ')') ||
				(ch == '=') || (ch == ';') || (ch == ':') || (ch == '!') ||
				(ch == '[') || (ch == ']') || (ch == '{') || (ch == '}') ||
				(ch == ',') || (ch == '|') || (ch == '&') || (ch == '.') ||
				(ch == '\\') || (ch == '\"') || (ch == '\''));
	}

	bool compareChar(char& c1, char& c2)
	{									// Compares individual chars, takes into account
		if (isupper(c1)) return false;										// if a char is Uppercase or Lowercase DM
		else if (c1 == tolower(c2)) return true;
		return false;
	}

	bool tokenChecker(std::string str1, std::string str2)
	{					//  Compares lexeme to token DM
		return ((str1.size() == str2.size()) &&
				std::equal(str1.begin(), str1.end(), str2.begin(), &compareChar)); // How does this function reference thing work CD
	}

}
