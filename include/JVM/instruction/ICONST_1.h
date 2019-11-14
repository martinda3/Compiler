#ifndef ICONST_1_H
#define ICONST_1_H

#include <iostream>
#include "JVMinstruction.h"
#include "JVMlineOfCode.h"

namespace toyc {

  class ICONST_1 : public JVMinstruction, public JVMlineOfCode {
  public:
    ICONST_1();
    std::string toString();
  };

}

#endif

