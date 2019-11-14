#ifndef ILOAD_0_H
#define ILOAD_0_H

#include <iostream>
#include "JVMinstruction.h"
#include "JVMlineOfCode.h"

namespace toyc {

  class ILOAD_0 : public JVMinstruction, public JVMlineOfCode {
  public:
    ILOAD_0();
    std::string toString();
  };

}
#endif
