#ifndef SIPUSH_H
#define SIPUSH_H

#include <iostream>
#include "JVMinstruction.h"
#include "JVMlineOfCode.h"

namespace toyc {

  class SIPUSH : public JVMinstruction, public JVMlineOfCode {
  public:
    int index;

    SIPUSH(int);
    std::string toString();
  };

}

#endif
