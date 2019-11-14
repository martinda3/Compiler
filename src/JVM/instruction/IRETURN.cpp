#include <iostream>
#include "JVMinstruction.h"
#include "JVMlineOfCode.h"

namespace toyc {

  class IRETURN : public JVMinstruction, JVMlineOfCode {
  public:

    IRETURN() { }
    std::string toString() {
      return "\tireturn";
    }
  };

}

