#ifndef ISTORE_2_H
#define ISTORE_2_H

#include <iostream>
#include "JVMinstruction.h"
#include "JVMlineOfCode.h"

namespace toyc {

  class ISTORE_2 : public JVMinstruction, public JVMlineOfCode {
  public:
    ISTORE_2();
    std::string toString();
  };

}

#endif
