#include <iostream>
#include "IF_ICMPLT.h"
#include "label.h"

namespace toyc {

  IF_ICMPLT::IF_ICMPLT(label* lbl) { l = lbl; }
  std::string IF_ICMPLT::toString() {
    return "\tif_icmplt " + l->toString();
  }

}
