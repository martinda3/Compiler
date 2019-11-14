#include <iostream>
#include "INVOKEVIRTUAL.h"

namespace toyc {

  INVOKEVIRTUAL::INVOKEVIRTUAL(std::string fc) { functionCall = fc; }
  std::string INVOKEVIRTUAL::toString() {
      return "\tinvokevirtual " + functionCall;
  }

}

