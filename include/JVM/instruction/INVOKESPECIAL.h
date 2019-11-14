#ifndef INVOKESPECIAL_H
#define INVOKESPECIAL_H

#include <iostream>
#include "JVMinstruction.h"
#include "JVMlineOfCode.h"

namespace toyc {

  class INVOKESPECIAL : public JVMinstruction, public JVMlineOfCode {
  public:
    std::string constructor;

    INVOKESPECIAL(std::string);
    std::string toString();
  };

}

#endif

