#ifndef IADD_H
#define IADD_H

#include <iostream>
#include "JVMinstruction.h"
#include "JVMlineOfCode.h"

namespace toyc {

  class IADD : public JVMinstruction, public JVMlineOfCode {
  public:

    IADD();
    std::string toString();
  };

}

#endif
