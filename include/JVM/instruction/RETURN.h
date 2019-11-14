#ifndef RETURN_H
#define RETURN_H

#include <iostream>
#include "JVMinstruction.h"
#include "JVMlineOfCode.h"

namespace toyc {

  class RETURN : public JVMinstruction, public JVMlineOfCode {
  public:
    RETURN();
    std::string toString();
  };

}

#endif
