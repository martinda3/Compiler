#include <iostream>
#include "JVMinstruction.h"
#include "JVMlineOfCode.h"

namespace toyc {

  class ACONST_NULL : public JVMinstruction, JVMlineOfCode {
  public:
    ACONST_NULL() { }
    std::string toString() { return "\taconst_null"; }
  };

}
