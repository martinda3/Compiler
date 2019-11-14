#include <iostream>
#include "IFEQ.h"
#include "label.h"

namespace toyc {

  IFEQ::IFEQ(label* lbl) { l = lbl; }
  std::string IFEQ::toString() {
    return "\tifeq " + l->toString();
  }

}
