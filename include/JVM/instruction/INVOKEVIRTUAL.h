#ifndef INVOKEVIRTUAL_H
#define INVOKEVIRTUAL_H

#include <iostream>
#include "JVMinstruction.h"
#include "JVMlineOfCode.h"

namespace toyc {

  class INVOKEVIRTUAL : public JVMinstruction, public JVMlineOfCode {
  public:
    std::string functionCall;

    INVOKEVIRTUAL(std::string);
    std::string toString();
  };

}

#endif
