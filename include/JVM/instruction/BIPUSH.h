#ifndef BIPUSH_H
#define BIPUSH_H

#include <iostream>
#include "JVMinstruction.h"
#include "JVMlineOfCode.h"

namespace toyc {

  class BIPUSH : public JVMinstruction, public JVMlineOfCode {
  public:
    int index;

    BIPUSH(int);
    std::string toString();
  };

}


#endif

