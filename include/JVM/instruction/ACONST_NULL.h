#ifndef ACONST_NULL_H
#define ACONST_NULL_H

#include <iostream>
#include "JVMinstruction.h"
#include "JVMlineOfCode.h"

namespace toyc {

  class ACONST_NULL : public JVMinstruction, public JVMlineOfCode {
  public:
    ACONST_NULL() { }
    std::string toString() { return "\taconst_null"; }
  };

}

#endif

