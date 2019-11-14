#ifndef ISTORE_0_H
#define ISTORE_0_H

#include <iostream>
#include "JVMinstruction.h"
#include "JVMlineOfCode.h"

namespace toyc {

  class ISTORE_0 : public JVMinstruction, public JVMlineOfCode {
  public:
    ISTORE_0();
    std::string toString();
  };

}

#endif
