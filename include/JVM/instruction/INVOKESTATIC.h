#ifndef INVOKESTATIC_H
#define INVOKESTATIC_H

#include <iostream>
#include "JVMinstruction.h"
#include "JVMlineOfCode.h"

#define MAX_INVOKESTATIC_ARGS 20 

namespace toyc {

  class INVOKESTATIC : public JVMinstruction, public JVMlineOfCode {
  public:
    std::string name;
    std::string type;
    std::string args[MAX_INVOKESTATIC_ARGS];
    int numArgs;
    
    INVOKESTATIC(std::string,std::string);
    void addArg(std::string);
    std::string toString();
  };

}

#endif
