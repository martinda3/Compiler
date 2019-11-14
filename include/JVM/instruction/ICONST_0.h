#ifndef ICONST_0_H
#define ICONST_0_H

#include <iostream>
#include "JVMinstruction.h"
#include "JVMlineOfCode.h"

namespace toyc {

  class ICONST_0 : public JVMinstruction, public JVMlineOfCode {
  public:
    ICONST_0();
    std::string toString();
  };

}
#endif

