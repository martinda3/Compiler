#ifndef ILOAD_3_H
#define ILOAD_3_H

#include <iostream>
#include "JVMinstruction.h"
#include "JVMlineOfCode.h"

namespace toyc {

  class ILOAD_3 : public JVMinstruction, public JVMlineOfCode {
  public:
    ILOAD_3();
    std::string toString();
  };

}

#endif

