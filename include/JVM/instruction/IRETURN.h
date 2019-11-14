#ifndef IRETURN_H
#define IRETURN_H

#include <iostream>
#include "JVMinstruction.h"
#include "JVMlineOfCode.h"

namespace toyc {

  class IRETURN : public JVMinstruction, public JVMlineOfCode {
  public:

    IRETURN();
    std::string toString();
  };

}

#endif
