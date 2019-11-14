#include <iostream>
#include "GOTO.h"
#include "label.h"

namespace toyc {

  GOTO::GOTO(label *lbl) { l = lbl; } 
  std::string GOTO::toString() {
    return "\tgoto " + l->toString();
  }

}
