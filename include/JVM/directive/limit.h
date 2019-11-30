#ifndef LIMIT_H
#define LIMIT_H

#include "JVMlineOfCode.h"
#include "JVMdirective.h"

namespace toyc {

  class limit : public JVMlineOfCode, JVMdirective {
  public:
    std::string directive;
    std::string type;
    int size;
    
    limit(std::string,int);
    std::string toString();
  };
}

#endif
