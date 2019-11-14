#ifndef ALOAD_0_H
#define ALOAD_0_H

#include <iostream>
#include "JVMinstruction.h"
#include "JVMlineOfCode.h"

namespace toyc {

  class ALOAD_0 : public JVMinstruction, public JVMlineOfCode {
  public:
    ALOAD_0();
    std::string toString();
  };

}

#endif
