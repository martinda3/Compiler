#include <iostream>

#include "BIPUSH.h"

namespace toyc {

  BIPUSH::BIPUSH(int i) { index = i; }
  std::string BIPUSH::toString() {
    return "\tbipush " + std::to_string(index);
  }

}


