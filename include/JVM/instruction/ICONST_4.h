#ifndef ICONST_4_H
#define ICONST_4_H

#include <iostream>
#include "JVMinstruction.h"
#include "JVMlineOfCode.h"

namespace toyc {

  class ICONST_4 : public JVMinstruction, public JVMlineOfCode {
  public:
    ICONST_4();
    std::string toString();
  };

}
#endif
