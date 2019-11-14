#include <iostream>
#include "LDC.h"

namespace toyc {

  LDC::LDC(int i) { ival = i; sval = ""; }
  LDC::LDC(std::string s) { sval = s; }
  std::string LDC::toString() {
    return ("\tldc " + (sval==""?std::to_string(ival):'"'+sval+'"'));
  }

}
