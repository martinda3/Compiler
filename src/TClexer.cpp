#include <iostream>
#include <fstream>

#include "TCtoken.h"
#include "TClexer.h"
#include "TCglobals.h"
#include "TCtokens.h"
#include "TCoutput.h"

namespace toyc {

  static char charBuff;
  static std::string line;
  static int pos;
  static int lineNum = 0;
  static std::string lexeme = ""; 
  static char EOFCHAR = '\0'; 		// arbitrary non-printing char
  static std::ifstream infile;
 
  static int t_tokens = 0;			// Total token count

  char getChar();
  std::string getNextLine();
  bool isInAlphabet(char);
  bool tokenChecker(std::string, std::string);
    
  TClexer::TClexer(std::string fname) {
	inputFileName = fname;
    line = ""; pos = 0;
    infile.open(inputFileName);
    if(infile.fail()) {
    	std::cerr << "ERROR: input file not found" << std::endl;
    	exit (EXIT_FAILURE);}
    charBuff = getChar(); 
  }
  
  TCtoken* TClexer::getToken() {
	t_tokens++;
    lexeme = ""; TCtoken* t;

    while (isspace(charBuff) && (charBuff != EOFCHAR)) charBuff = getChar();
    if (charBuff == EOFCHAR) {
    	t = new TCtoken(EOFILE); 
        if (verbose) reportDEBUG("  ","SCANNER",t->toString());
        if (verbose) reportDEBUG("  ","SCANNER"," Total tokens: " + std::to_string(t_tokens));
        return t;} 
	else if (isdigit(charBuff)) {
      	do { lexeme += charBuff; charBuff = getChar(); } 
		while(isdigit(charBuff));
			if (charBuff == '.') {
				lexeme += charBuff; charBuff = getChar();
        		if (!isdigit(charBuff))
					reportWARNING("  ","illegal character ignored 1");
        			//reportWARNING("","illegal character '"+charBuff+"' ignored");
        		do { lexeme += charBuff; charBuff = getChar(); } 
				while(isdigit(charBuff));}
      	t = new TCtoken(NUMBER,lexeme);} 
	else if (isalpha(charBuff)) {
      	do { lexeme += charBuff; charBuff = getChar(); } 
		while(isalpha(charBuff) || isdigit(charBuff));
   			if (tokenChecker(lexeme,std::string("WRITE")))
        		t = new TCtoken(WRITE, lexeme);
    		else if (tokenChecker(lexeme,"READ"))
        		t = new TCtoken(READ, lexeme);
      		else if (tokenChecker(lexeme,"IF"))
        		t = new TCtoken(IF, lexeme);
      		else if (tokenChecker(lexeme,"THEN"))
        		t = new TCtoken(THEN, lexeme);
      		else if (tokenChecker(lexeme,"GOTO"))
       	 		t = new TCtoken(GOTO, lexeme);
      		else if (tokenChecker(lexeme,"SKIP"))
        		t = new TCtoken(SKIP, lexeme);
		    else if (tokenChecker(lexeme,"AND"))
		       	t = new TCtoken(AND, lexeme);
		    else if (tokenChecker(lexeme,"OR"))
		       	t = new TCtoken(OR, lexeme);
		    else if (tokenChecker(lexeme,"DO"))
		       	t = new TCtoken(DO, lexeme);
		    else if (tokenChecker(lexeme,"FOR"))
		        t = new TCtoken(FOR, lexeme);
		    else if (tokenChecker(lexeme,"INT"))
		        t = new TCtoken(INT, lexeme);
		    else if (tokenChecker(lexeme,"ELSE"))
		        t = new TCtoken(ELSE, lexeme);
    		else if (tokenChecker(lexeme,"CHAR"))
   			    t = new TCtoken(CHAR, lexeme);
		    else if (tokenChecker(lexeme,"CASE"))
        		t = new TCtoken(CASE, lexeme);
    		else if (tokenChecker(lexeme,"WHILE"))
        		t = new TCtoken(WHILE, lexeme);
      		else if (tokenChecker(lexeme,"SWITCH"))
        		t = new TCtoken(SWITCH, lexeme);
      		else if (tokenChecker(lexeme,"RETURN"))
        		t = new TCtoken(RETURN, lexeme);
      		else if (tokenChecker(lexeme,"BREAK"))
        		t = new TCtoken(BREAK, lexeme);
      		else if (tokenChecker(lexeme,"DEFAULT"))
        		t = new TCtoken(DEFAULT, lexeme);
      		else if (tokenChecker(lexeme,"CONTINUE"))
        		t = new TCtoken(CONTINUE, lexeme);
      		else if (tokenChecker(lexeme,"STRING"))
        		t = new TCtoken(STRING, lexeme);
      		else if (tokenChecker(lexeme,"SKIP"))
        		t = new TCtoken(SKIP, lexeme);
      		else if (tokenChecker(lexeme,"NONE"))
        		t = new TCtoken(NONE, lexeme);
      		else if (tokenChecker(lexeme,"THEN"))
        		t = new TCtoken(THEN, lexeme);
      		else { 
				t = new TCtoken(ID,lexeme); }} 
	else {
      	lexeme += charBuff;
      	switch (charBuff) {
			case '+': 	t = new TCtoken(ADDOP, lexeme); charBuff = getChar(); break;
			case '[': 	t = new TCtoken(LBRACKET, lexeme);	 charBuff = getChar(); break;
			case ']': 	t = new TCtoken(RBRACKET, lexeme);	 charBuff = getChar(); break;
			case '{': 	t = new TCtoken(LCURLY, lexeme);	 charBuff = getChar(); break;
			case '}': 	t = new TCtoken(RCURLY, lexeme);	 charBuff = getChar(); break;
		    case '-': 	t = new TCtoken(ADDOP, lexeme); charBuff = getChar(); break;
		    case '*': 	t = new TCtoken(MULOP, lexeme); charBuff = getChar(); break;
    		case '/':	charBuff = getChar(); 
						if (charBuff == '/'){
							int temp = lineNum;
							while (temp == lineNum) {
								charBuff = getChar();}
							t = new TCtoken(COMMENT); charBuff = getChar(); break;}
		      			else if (charBuff == '*'){
							while (true) {
								charBuff = getChar();
								if (charBuff == EOFCHAR) {
		      						reportWARNING("  ","Block Comment Error");
    								exit (EXIT_FAILURE);}
								if (charBuff == '*') {
									charBuff = getChar();
									if (charBuff == '/') {
										t = new TCtoken(BLOCK); charBuff = getChar(); break;}
									else { continue; } } }
							break;}
		      			else { 
			      			t = new TCtoken(DIVOP, lexeme); charBuff = getChar(); break;}
		      			break;
        	case '<': 	charBuff = getChar();
            		    if (charBuff == '=') {
							lexeme += charBuff; 
            		    	t = new TCtoken(RELOP, lexeme); charBuff = getChar(); break;} 
						else
            		        t = new TCtoken(RELOP, lexeme);
            		    break;
        	case '|': 	charBuff = getChar();
            		    if (charBuff == '|') {
							lexeme += charBuff; 
            		    	t = new TCtoken(OR, lexeme); charBuff = getChar(); break;} 
						else {
		      				reportWARNING("  ","Missing an |");
    						exit (EXIT_FAILURE);}
        	case '&': 	charBuff = getChar();
            		    if (charBuff == '&') {
							lexeme += charBuff; 
            		    	t = new TCtoken(AND, lexeme); charBuff = getChar(); break;} 
						else {
		      				reportWARNING("  ","Missing an &");
    						exit (EXIT_FAILURE);}
        	case '>': 	charBuff = getChar();
            		    if (charBuff == '=') {
							lexeme += charBuff; 
                 			t = new TCtoken(RELOP, lexeme); charBuff = getChar(); break;} 
						else {
                		    t = new TCtoken(RELOP, lexeme); charBuff = getChar(); break;}
                   		break;
    		case '!': 	charBuff = getChar();
               		 	if (charBuff == '=') {
							lexeme += charBuff; 
                      		t = new TCtoken(NOT, lexeme); charBuff = getChar(); break;} 
						else {
		      				reportWARNING("  ","Missing an &");
    						exit (EXIT_FAILURE);}
     		case '(': 	t = new TCtoken(LPAREN, lexeme); charBuff = getChar(); break;
    		case ')': 	t = new TCtoken(RPAREN, lexeme); charBuff = getChar(); break;
       		case '=': 	charBuff = getChar();
                 		if (charBuff == '=') {
							lexeme += charBuff;
                   			t = new TCtoken(RELOP, lexeme); charBuff = getChar();} 
						else
                       		t = new TCtoken(ASSIGNOP, lexeme);
                		break;
      		case '\"': 	charBuff = getChar();
                   		if (charBuff == '\"') {
							lexeme = "IS_EMPTY";
                    		t = new TCtoken(STRING,lexeme); charBuff = getChar(); break;}
						else {
							while (charBuff != '\"') {
		      					lexeme += charBuff;
		      					charBuff = getChar();
		      					if (charBuff == EOFCHAR){
		      						reportWARNING("  ","String Error");
    								exit (EXIT_FAILURE);}}
							lexeme += charBuff;
                    		t = new TCtoken(STRING,lexeme); charBuff = getChar(); break;}
      		case '\'': 	charBuff = getChar(); 
                   		if (charBuff == '\'') {
							lexeme = "IS_EMPTY";
                    		t = new TCtoken(CHARLITERAL,lexeme); charBuff = getChar(); break;} 
        	    		else { 
							lexeme += charBuff;
		   					charBuff = getChar();
			  				if (charBuff != '\'') {
		      					reportWARNING("  ","Char literal Error");
    							exit (EXIT_FAILURE);}
							else {
								lexeme += charBuff;
                   				t = new TCtoken(CHARLITERAL,lexeme); charBuff = getChar(); break;}}
      		case '\\': 	charBuff = getChar();
               		  	if (charBuff == 'n') {
							lexeme += charBuff;
               				t = new TCtoken(NEWLINE, lexeme); charBuff = getChar(); break;} 
						else {
		      				reportWARNING("  ","\\ Error");
    						exit (EXIT_FAILURE);}
    		case ';': 	t = new TCtoken(SEMICOLON, lexeme); charBuff = getChar(); break;
    		case ':': 	t = new TCtoken(COLON, lexeme);     charBuff = getChar(); break;
    		default: 	// shouldn't happen!
          				t = new TCtoken(NONE, lexeme);}}
    if (verbose) reportDEBUG("  ","SCANNER",t->toString());
    return t;}


  std::string TClexer::getLine() 	{ return line; }
  std::string TClexer::getLexeme() 	{ return lexeme; }
  int TClexer::getPos() 			{ return pos; }
  int TClexer::getLineNum() 		{ return lineNum; }
  
  char getChar() {
    do {
      if (infile.eof()) return EOFCHAR;
      if (line.empty() || pos > line.length()) line = getNextLine();
      char ch = line[pos];
      if ( ((ch == '/') && (line[pos+1] == '/')) || (ch == '\0') ) {
        line = getNextLine();
        ch = line[pos];}
      if (isInAlphabet(ch) || isspace(ch)) break;
        reportWARNING("  ","illegal character ignored 2");
      	//reportWARNING("","illegal character '"+line[pos]+"' ignored")
      pos++;} 
    while (true);
    return line[pos++];}
   
std::string getNextLine() {
  std::string line;
  std::string buff;
  pos = 0; lineNum++;
  if (lineNum <= 9) {
  	buff = "  ";}
  else if (lineNum < 1000) {
    buff = " ";}
  buff = buff + std::to_string(lineNum) + ": ";
  std::getline(infile,line);
  line = line + " ";
  buff = buff + line;
  //if (verbose) reportDEBUG("  ", " input ",lineNum+ "" +buff);
  return line;
}

bool isInAlphabet(char ch) {
  return ( isalpha(ch) || isdigit(ch) ||
  	 	(ch == '+')  || (ch == '-')  || (ch == '*') || (ch == '/') ||
  	 	(ch == '<')  || (ch == '>')  || (ch == '(') || (ch == ')') || 
    	(ch == '=')  || (ch == ';')  || (ch == ':') || (ch == '!') ||
    	(ch == '[')  || (ch == ']')  || (ch == '{') || (ch == '}') ||
    	(ch == ',')  || (ch == '|')  || (ch == '&') || (ch == '.') ||
	 	(ch == '\\') || (ch == '\"') || (ch == '\'')); 
}

bool compareChar(char& c1, char& c2){
  if (isupper(c1)) return false;
  else if (c1 == tolower(c2)) return true;
  //else if (std::toupper(c1) == std::toupper(c2)) return true;
  return false;
}

bool tokenChecker(std::string str1, std::string str2){
  return ( (str1.size() == str2.size() ) &&
           std::equal(str1.begin(), str1.end(), str2.begin(), &compareChar) );
}
  
}
