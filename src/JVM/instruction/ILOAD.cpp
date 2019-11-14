#include <iostream>
#include "ILOAD.h"

namespace toyc {

  ILOAD::ILOAD(int i) { index = i; }
  std::string ILOAD::toString() {
    return "\tiload " + std::to_string(index);
  }

}
