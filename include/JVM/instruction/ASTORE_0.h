#ifndef ASTORE_0_H
#define ASTORE_0_H

#include <iostream>
#include "JVMinstruction.h"
#include "JVMlineOfCode.h"

namespace toyc {

  class ASTORE_0 : public JVMinstruction, public JVMlineOfCode {
  public:
    ASTORE_0();
    std::string toString();
  };

}

#endif

