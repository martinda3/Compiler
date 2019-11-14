#ifndef ICONST_5_H
#define ICONST_5_H

#include <iostream>
#include "JVMinstruction.h"
#include "JVMlineOfCode.h"

namespace toyc {

  class ICONST_5 : public JVMinstruction, public JVMlineOfCode {
  public:
    ICONST_5();
    std::string toString();
  };

}

#endif
