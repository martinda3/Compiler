#include <iostream>

#include <time.h>
#include "comment.h"

namespace toyc {

  comment::comment(std::string s) { text = s; }
  
  std::string comment::toString() {
    std::string str = "; " + text;
    return str;
  }
  
}
