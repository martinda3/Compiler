#ifndef ICONST_3_H
#define ICONST_3_H

#include <iostream>
#include "JVMinstruction.h"
#include "JVMlineOfCode.h"

namespace toyc {

  class ICONST_3 : public JVMinstruction, public JVMlineOfCode {
  public:
    ICONST_3();
    std::string toString();
  };

}
#endif
