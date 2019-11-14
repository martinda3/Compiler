#include <iostream>

#include "targetFileComment.h"

namespace toyc {

  targetFileComment::targetFileComment(std::string s) { target = s; }
  std::string targetFileComment::toString() {
    std::string str = "; Target file: ";
    return (str + target);
  }
  
}
