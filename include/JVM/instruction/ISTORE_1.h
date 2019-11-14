#ifndef ISTORE_1_H
#define ISTORE_1_H

#include <iostream>
#include "JVMinstruction.h"
#include "JVMlineOfCode.h"

namespace toyc {

  class ISTORE_1 : public JVMinstruction, public JVMlineOfCode {
  public:
    ISTORE_1();
    std::string toString();
  };

}

#endif

