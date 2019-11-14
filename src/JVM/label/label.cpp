#include <iostream>
#include "JVMlabel.h"
#include "label.h"
#include "JVMlineOfCode.h"
#include "JVMgenGlobals.h"
#include "JVMgenUtils.h"

namespace toyc {
  static int _labelInt = 0;
  
  label::label(){
    l += (LABELTAG + std::to_string(_labelInt++));
  }

  label::label(std::string s) { l = s; }

  std::string label::getLabel() { return l; }

  std::string label::toString() { return l; }
}
