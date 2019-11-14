#include <iostream>
#include "IFNE.h"
#include "label.h"

namespace toyc {

  IFNE::IFNE(label* lbl) { l = lbl; }
  std::string IFNE::toString() {
    return "\tifne " + l->toString();
  }

}
