#ifndef ASTORE_3_H
#define ASTORE_3_H

#include <iostream>
#include "JVMinstruction.h"
#include "JVMlineOfCode.h"

namespace toyc {

  class ASTORE_3 : public JVMinstruction, public JVMlineOfCode {
  public:
    ASTORE_3();
    std::string toString();
  };

}

#endif

