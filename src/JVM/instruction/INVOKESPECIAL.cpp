#include <iostream>
#include "INVOKESPECIAL.h"

namespace toyc {

  INVOKESPECIAL::INVOKESPECIAL(std::string c) { constructor = c; }
  std::string INVOKESPECIAL::toString() {
      return "\tinvokespecial " + constructor;
  }

}
