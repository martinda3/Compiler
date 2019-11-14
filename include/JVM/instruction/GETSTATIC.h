#ifndef GETSTATIC_H
#define GETSTATIC_H

#include <iostream>
#include "JVMinstruction.h"
#include "JVMlineOfCode.h"

namespace toyc {

  class GETSTATIC : public JVMinstruction, public JVMlineOfCode {
  public:
    std::string name;
    std::string type;
    
    GETSTATIC(std::string, std::string);
    std::string toString();
  };

}

#endif

