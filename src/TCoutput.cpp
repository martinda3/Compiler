#include <iostream>

#include "TCoutput.h"

namespace toyc {

  void reportDEBUG(std::string prefix, std::string type, std::string message) {
    std::cerr << prefix+"["+type+"] "+ message << std::endl;
  }

  void reportWARNING(std::string prefix, std::string message) {
    std::cerr << prefix+"[WARNING]: "+ message << std::endl;
  }
  
  void reportSYNTAX_ERROR(TClexer *l, std::string message) {
    int ln; std::string lnstr;
    std::string sep = ": ";
    std::cerr << (ln=l->getLineNum()) << sep << l->getLine() << std::endl;
    lnstr += ln;
    std::cerr <<
      pad(lnstr.length()) << 
      pad(l->getPos()+sep.length()-(l->getLexeme().length())+1) <<
      "^ %error: " <<  message << std::endl;
  }

  void reportSEMANTIC_ERROR(TClexer* l,std::string message) {
    int ln; std::string lnstr;
    std::string sep = ": ";
    std::cerr << (ln=l->getLineNum())<< sep << l->getLine() << std::endl;
    lnstr += ln;    
    std::cerr <<
      pad(lnstr.length()) <<
      pad(l->getPos()+sep.length()-(l->getLexeme().length())-1) <<  
      "^ %error: " << message << std::endl;
    /*
    std::cout << "line number len = " << lnstr.length() << std::endl;
    std::cout << "sep  len = " << sep.length() << std::endl;
    std::cout << "getPos = " << l->getPos() << std::endl;
    std::cout << "lexeme = " << l->getLexeme() << std::endl;
    std::cout << "lexeme length = " << l->getLexeme().length() << std::endl;
    */
  }

  void reportSEMANTIC_ERROR(std::string message) {
    std::cerr << ("%error: "+ message) << std::endl;
  }

  /*void dumpAST(ASabstractSyntax* ast) {
    std::cout << "abstract syntax tree:" << std::endl << ast->toString() << std::endl;
  }*/

  /*void dumpST(TCsymTable* st) {
    std::cout << "symbol table:" << std::endl << st->toString() << std::endl;
  }*/

  /*    public static void dumpCode(TargetCode code) {
      std::cout << "abstract syntax tree:" << std::endl <<
	ast.toString() << std::endl;
        System.err.println("code:\n"+code);
    }
*/
  
  std::string pad(int n) {
    std::string s = ""; 
    for (int i = 1; i <= n; i++) s+=" ";
    return s;
  }

  int _pos = 0;
  int _INDENTSIZE=4;
  
  std::string spaces() { return pad(_pos); } 

  void indent() { _pos += _INDENTSIZE; }
  void outdent() { _pos -= _INDENTSIZE; }
}
