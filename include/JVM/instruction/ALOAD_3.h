#ifndef ALOAD_3_H
#define ALOAD_3_H

#include <iostream>
#include "JVMinstruction.h"
#include "JVMlineOfCode.h"

namespace toyc {

  class ALOAD_3 : public JVMinstruction, public JVMlineOfCode {
  public:
    ALOAD_3();
    std::string toString();
    
  };

}

#endif
