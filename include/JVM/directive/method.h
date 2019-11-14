#ifndef METHOD_H
#define METHOD_H

#include "JVMlineOfCode.h"
#include "JVMdirective.h"

namespace toyc {

  class method : public JVMlineOfCode, JVMdirective {
  public:
    std::string directive;
    std::string accessSpecs[20];
    int accessSize;
    std::string args[20];
    int argsSize;
    std::string name;
    std::string type;
  
    method(std::string, std::string);
    void addAccessSpec(std::string);
    void addArg(std::string);
    std::string toString();
  };
}

#endif
