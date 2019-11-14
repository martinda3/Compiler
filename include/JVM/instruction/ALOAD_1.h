#ifndef ALOAD_1_H
#define ALOAD_1_H

#include <iostream>
#include "JVMinstruction.h"
#include "JVMlineOfCode.h"

namespace toyc {

  class ALOAD_1 : public JVMinstruction, public JVMlineOfCode {
  public:
    ALOAD_1();
    std::string toString();
  };

}

#endif
