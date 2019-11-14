#include <iostream>

#include "sourceFileComment.h"

namespace toyc {

  sourceFileComment::sourceFileComment(std::string s) { source = s; }
  std::string sourceFileComment::toString() {
    std::string str = "; Source file: ";
    return (str + source);
  }
  
}
