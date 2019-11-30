#include <iostream>

#include "limit.h"

namespace toyc {


limit::limit(std::string t, int s) {
    directive = ".limit";
    type = t; size = s;
  }
  
  std::string limit::toString() {
    std::string s = ("\t" + directive + " " + type + " " + std::to_string(size));
    return s;
  }

}

