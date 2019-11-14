#ifndef JVMLINEOFCODE_H
#define JVMLINEOFCODE_H

#include "CGlineOfCode.h"

namespace toyc {
  
  class JVMlineOfCode:public CGlineOfCode {
  public:
    std::string toString();
  };
 
}
#endif
