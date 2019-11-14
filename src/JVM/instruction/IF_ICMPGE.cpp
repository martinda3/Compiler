#include <iostream>
#include "IF_ICMPGE.h"
#include "label.h"

namespace toyc {

  IF_ICMPGE::IF_ICMPGE(label* lbl) { l = lbl; }
  std::string IF_ICMPGE::toString() {
    return "\tif_icmpge " + l->toString();
  }

}
