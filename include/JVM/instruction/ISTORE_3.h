#ifndef ISTORE_3_H
#define ISTORE_3_H

#include <iostream>
#include "JVMinstruction.h"
#include "JVMlineOfCode.h"

namespace toyc {

  class ISTORE_3 : public JVMinstruction, public JVMlineOfCode {
  public:
    ISTORE_3();
    std::string toString();
  };

}

#endif


