#ifndef PUTSTATIC_H
#define PUTSTATIC_H

#include <iostream>
#include "JVMinstruction.h"
#include "JVMlineOfCode.h"

namespace toyc {

  class PUTSTATIC : public JVMinstruction, public JVMlineOfCode {
  public:
    std::string name;
    std::string type;

    PUTSTATIC(std::string,std::string);
    std::string toString();
  };

}

#endif
