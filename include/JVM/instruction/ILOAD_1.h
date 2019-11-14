#ifndef ILOAD_1_H
#define ILOAD_1_H

#include <iostream>
#include "JVMinstruction.h"
#include "JVMlineOfCode.h"

namespace toyc {

  class ILOAD_1 : public JVMinstruction, public JVMlineOfCode {
  public:
    ILOAD_1();
    std::string toString();
  };

}

#endif
