#include <iostream>
#include "NEW.h"

namespace toyc {

  NEW::NEW(std::string cn) { className = cn; }
  std::string NEW::toString() { return "\tnew " + className;  }

}

