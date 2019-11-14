#include <iostream>

#include "class_.h"

namespace toyc {

  class_::class_(std::string s) {
    directive = ".class";
    className = s;
    accessSize = 0;
  }

  void class_::addAccessSpec(std::string s) { accessSpecs[accessSize++] = s; }

  std::string class_::toString() {
    std::string s = directive + " ";
    for (int i=0; i<accessSize; i++) s += (accessSpecs[i] + " ");
    s += className;
    return s;
  }
  
}

