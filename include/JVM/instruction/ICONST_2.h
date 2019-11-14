#ifndef ICONST_2_H
#define ICONST_2_H

#include <iostream>
#include "JVMinstruction.h"
#include "JVMlineOfCode.h"

namespace toyc {

  class ICONST_2 : public JVMinstruction, public JVMlineOfCode {
  public:
    ICONST_2();
    std::string toString();
  };

}
#endif
