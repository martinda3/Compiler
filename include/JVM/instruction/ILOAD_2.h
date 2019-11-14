#ifndef ILOAD_2_H
#define ILOAD_2_H

#include <iostream>
#include "JVMinstruction.h"
#include "JVMlineOfCode.h"

namespace toyc {

  class ILOAD_2 : public JVMinstruction, public JVMlineOfCode {
  public:
    ILOAD_2();
    std::string toString();
  };

}

#endif
