#ifndef ASTORE_H
#define ASTORE_H

#include <iostream>
#include "JVMinstruction.h"
#include "JVMlineOfCode.h"

namespace toyc {

  class ASTORE : public JVMinstruction, public JVMlineOfCode {
  public:
    int index;

    ASTORE(int);
    std::string toString();
  };

}

#endif
