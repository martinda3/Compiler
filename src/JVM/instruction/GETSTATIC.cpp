#include <iostream>

#include "GETSTATIC.h"

namespace toyc {

  GETSTATIC::GETSTATIC(std::string n, std::string t) {
      name = n; type = t;
  }
  
  std::string GETSTATIC::toString() {
      return "\tgetstatic " + name + " " + type;
  }

}


