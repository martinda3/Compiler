#ifndef ASTORE_2_H
#define ASTORE_2_H

#include <iostream>
#include "JVMinstruction.h"
#include "JVMlineOfCode.h"

namespace toyc {

  class ASTORE_2 : public JVMinstruction, public JVMlineOfCode {
  public:
    ASTORE_2();
    std::string toString();
  };

}

#endif
