#ifndef SWAP_H
#define SWAP_H

#include <iostream>
#include "JVMinstruction.h"
#include "JVMlineOfCode.h"

namespace toyc {

  class SWAP : public JVMinstruction, public JVMlineOfCode {
  public:
    SWAP();
    std::string toString();
  };

}

#endif

