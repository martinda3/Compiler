#include <iostream>
#include <fstream>

#include "TCtoken.h"
#include "TClexer.h"
#include "TCglobals.h"
#include "TCtokens.h"
#include "TCoutput.h"

namespace toycalc {

  static char charBuff;
  static std::string line;
  static int pos;
  static int lineNum = 0;
  static std::string lexeme = ""; 
  static char EOFCHAR = '\0'; // arbitrary non-printing char
  static std::ifstream infile;
  
  char getChar();
  std::string getNextLine();
  bool isInAlphabet(char);
  bool equalIgnoreCase(std::string, std::string);
    
  TClexer::TClexer(std::string fname) {
    inputFileName = fname;
    line = ""; pos = 0;
    infile.open(inputFileName);
    if(infile.fail()) {
      std::cerr << "ERROR: input file not found" << std::endl;
      exit (EXIT_FAILURE);
    }
    charBuff = getChar(); 
  }
  
  TCtoken* TClexer::getToken() {
    lexeme = ""; TCtoken* t;

    while (isspace(charBuff) && (charBuff != EOFCHAR)) charBuff = getChar();
    if (charBuff == EOFCHAR) {
            t = new TCtoken(EOFILE); 
            if (verbose) reportDEBUG("  ","scanner",t->toString());
            return t;
    } else if (isdigit(charBuff)) {
      do {
        lexeme += charBuff; charBuff = getChar();
      } while(isdigit(charBuff));
      if (charBuff == '.') {
        lexeme += charBuff; charBuff = getChar();
        if (!isdigit(charBuff))
          reportWARNING("","illegal character ignored 1");
        //          reportWARNING("","illegal character '"+charBuff+"' ignored");
          do {
            lexeme += charBuff; charBuff = getChar();
          } while(isdigit(charBuff));
      }
      t = new TCtoken(NUM,lexeme);
    } else if (isalpha(charBuff)) {
      do {
        lexeme += charBuff; charBuff = getChar();
      } while(isalpha(charBuff) || isdigit(charBuff));
   
      if (equalIgnoreCase(lexeme,std::string("WRITE")))
        t = new TCtoken(WRITE);
      else if (equalIgnoreCase(lexeme,"READ"))
        t = new TCtoken(READ);
      else if (equalIgnoreCase(lexeme,"IF"))
        t = new TCtoken(IF);
      else if (equalIgnoreCase(lexeme,"THEN"))
        t = new TCtoken(THEN);
      else if (equalIgnoreCase(lexeme,"GOTO"))
        t = new TCtoken(GOTO);
      else if (equalIgnoreCase(lexeme,"SKIP"))
        t = new TCtoken(SKIP);
      else if (equalIgnoreCase(lexeme,"AND"))
        t = new TCtoken(AND);
      else if (equalIgnoreCase(lexeme,"OR"))
        t = new TCtoken(OR);
      else {
        t = new TCtoken(ID,lexeme);
      }
    } else {
      lexeme += charBuff;
      switch (charBuff) {
            case '+': t = new TCtoken(ADDOP,"+"); charBuff = getChar(); break;
            case '-': t = new TCtoken(ADDOP,"-"); charBuff = getChar(); break;
            case '*': t = new TCtoken(MULOP,"*"); charBuff = getChar(); break;
            case '/': t = new TCtoken(MULOP,"/"); charBuff = getChar(); break;
            case '<': charBuff = getChar();
                      if (charBuff == '=') {
                          t = new TCtoken(RELOP,"<="); charBuff = getChar();
                      } else if (charBuff == '>') {
                          t = new TCtoken(RELOP,"<>"); charBuff = getChar();
                      } else
                          t = new TCtoken(RELOP,"<");
                      break;
            case '>': charBuff = getChar();
                      if (charBuff == '=') {
                          t = new TCtoken(RELOP,">="); charBuff = getChar();
                      } else
                          t = new TCtoken(RELOP,">");
                      break;
            case '(': t = new TCtoken(LPAREN); charBuff = getChar(); break;
            case ')': t = new TCtoken(RPAREN); charBuff = getChar(); break;
            case '=': charBuff = getChar();
                      if (charBuff == '=') {
                          t = new TCtoken(RELOP,"=="); charBuff = getChar();
                      } else
                          t = new TCtoken(ASSIGN);
                      break;
            case ';': t = new TCtoken(SEMICOLON); charBuff = getChar(); break;
            case ':': t = new TCtoken(COLON);     charBuff = getChar(); break;
            default: // shouldn't happen!
              t = new TCtoken(NONE);
            }
        }
        if (verbose) reportDEBUG("  ","scanner",t->toString());
        return t;
  }

  std::string TClexer::getLine() { return line; }
  std::string TClexer::getLexeme() { return lexeme; }
  int TClexer::getPos() { return pos; }
  int TClexer::getLineNum() { return lineNum; }
  
  char getChar() {
    do {
      if (infile.eof()) return EOFCHAR;
      if (line.empty() || pos > line.length()) line = getNextLine();
      char ch = line[pos];
      if ( ((ch == '/') && (line[pos+1] == '/')) || (ch == '\0') ) {
        line = getNextLine();
        ch = line[pos];
      }
      if (isInAlphabet(ch) || isspace(ch)) break;
        
      reportWARNING("","illegal character ignored 2");
      //      reportWARNING("","illegal character '"+line[pos]+"' ignored")
      pos++;
      
    } while (true);
    return line[pos++];
  }
   
std::string getNextLine() {
  std::string line;
  std::getline(infile,line);
  line = line + " ";
  pos = 0; lineNum++;
  // if (verbose) reportDEBUG("","input",lineNum+": "+line);
  return line;
}

bool isInAlphabet(char ch) {
  return ( isalpha(ch) || isdigit(ch) ||
  	 (ch == '+') || (ch == '-') || (ch == '*') || (ch == '/') ||
  	 (ch == '<') || (ch == '>') || (ch == '(') || (ch == ')') || 
         (ch == '=') || (ch == ';') || (ch == ':') ); 
}

bool compareChar(char& c1, char& c2){
  if (c1 == c2) return true;
  else if (std::toupper(c1) == std::toupper(c2)) return true;
  return false;
}

bool equalIgnoreCase(std::string str1, std::string str2){
  return ( (str1.size() == str2.size() ) &&
           std::equal(str1.begin(), str1.end(), str2.begin(), &compareChar) );
}
  
}
