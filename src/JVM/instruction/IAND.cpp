#include <iostream>
#include "JVMinstruction.h"
#include "JVMlineOfCode.h"

namespace toyc {

  class IAND : public JVMinstruction, JVMlineOfCode {
  public:

    IAND() { }
    std::string toString() {
      return "\tiand";
    }
  };

}

