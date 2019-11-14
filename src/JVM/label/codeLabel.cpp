#include <iostream>
#include "codeLabel.h"

namespace toyc {

  codeLabel::codeLabel(std::string n) { name = n; }
  std::string codeLabel::getLabel() { return name; }
  std::string codeLabel::toString() { return name + ":"; }
}
