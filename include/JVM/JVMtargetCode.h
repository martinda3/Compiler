#ifndef JVMTARGETCODE_H
#define JVMTARGETCODE_H

#include "CGtargetCode.h"
#include "JVMlineOfCode.h"

#define MAXLINESOFCODE 500

namespace toyc {
  
  class JVMtargetCode: public CGtargetCode {
  public:
    JVMtargetCode();
    void add(CGlineOfCode* l);
    CGlineOfCode *getLineOfCode(int);
    int getSize();
    void writeCode(CGtargetCode*,std::string);    
    std::string toString();
  private:
    JVMlineOfCode *code[MAXLINESOFCODE];
    int size;
  };
 
}
#endif
