#include <iostream>
#include "IF_ICMPLE.h"
#include "label.h"

namespace toyc {

  IF_ICMPLE::IF_ICMPLE(label* lbl) { l = lbl; }
  std::string IF_ICMPLE::toString() {
    return "\tif_icmple " + l->toString();
  }

}
