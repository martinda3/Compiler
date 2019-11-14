#include <iostream>

#include "end.h"

namespace toyc {

  end::end() { directive = ".end"; }
  std::string end::toString() { return (directive + " method"); }
  
}

