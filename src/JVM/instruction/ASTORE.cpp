#include <iostream>
#include "ASTORE.h"

namespace toyc {

  ASTORE::ASTORE(int i) { index = i; }
  std::string ASTORE::toString() {
    return "\tastore " + std::to_string(index);
  }

}

