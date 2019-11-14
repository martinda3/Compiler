#include <iostream>

#include "line.h"

namespace toyc {

    line::line(int num) { directive = ".line " + std::to_string(num); }
    std::string line::toString() { return (directive); }
  
}

