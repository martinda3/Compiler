#ifndef ICONST_M1_H
#define ICONST_M1_H

#include <iostream>
#include "JVMinstruction.h"
#include "JVMlineOfCode.h"

namespace toyc {

  class ICONST_M1 : public JVMinstruction, public JVMlineOfCode {
  public:
    ICONST_M1();
    std::string toString();
  };

}

#endif

