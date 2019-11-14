#include <iostream>
#include "IF_ICMPEQ.h"
#include "label.h"

namespace toyc {

  IF_ICMPEQ::IF_ICMPEQ(label* lbl) { l = lbl; }
  std::string IF_ICMPEQ::toString() {
    return "\tif_icmpeq " + l->toString();
  }

}
