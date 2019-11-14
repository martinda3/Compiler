#ifndef ASTORE_1_H
#define ASTORE_1_H

#include <iostream>
#include "JVMinstruction.h"
#include "JVMlineOfCode.h"

namespace toyc {

  class ASTORE_1 : public JVMinstruction, public JVMlineOfCode {
  public:
    ASTORE_1();
    std::string toString();
  };

}

#endif

