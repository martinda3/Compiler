#ifndef ALOAD_2_H
#define ALOAD_2_H

#include <iostream>
#include "JVMinstruction.h"
#include "JVMlineOfCode.h"

namespace toyc {

  class ALOAD_2 : public JVMinstruction, public JVMlineOfCode {
  public:
    ALOAD_2();
    std::string toString();
  };

}

#endif
