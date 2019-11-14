#ifndef CODELABEL_H
#define CODELABEL_H

#include <iostream>
#include "JVMlineOfCode.h"
#include "JVMlabel.h"

namespace toyc {

  class codeLabel : public JVMlineOfCode, public JVMlabel {
  public:
    std::string name;

    codeLabel(std::string);
    std::string getLabel();
    std::string toString();
  };

}

#endif

