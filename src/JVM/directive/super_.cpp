#include <iostream>

#include "super_.h"

namespace toyc {

  super_::super_(std::string s) {
    directive = ".super";
    parent = s;
  }
  std::string super_::toString() {
    std::string s = directive + " " + parent;
    return s;
  }
  
}
