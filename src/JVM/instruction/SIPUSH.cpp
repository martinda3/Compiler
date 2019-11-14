#include <iostream>

#include "SIPUSH.h"

namespace toyc {

  SIPUSH::SIPUSH(int i) { index = i; }
  std::string SIPUSH::toString() {
    return "\tsipush " + std::to_string(index);
  }

}
