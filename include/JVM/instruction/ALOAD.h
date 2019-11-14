#ifndef ALOAD_H
#define ALOAD_H

#include <iostream>
#include "JVMinstruction.h"
#include "JVMlineOfCode.h"

namespace toyc {

  class ALOAD : public JVMinstruction, public JVMlineOfCode {
  public:
    int index;

    ALOAD(int);
    std::string toString();
  };

}

#endif
