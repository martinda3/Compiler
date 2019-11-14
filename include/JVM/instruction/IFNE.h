#ifndef IFNE_H
#define IFNE_H

#include <iostream>
#include "JVMinstruction.h"
#include "JVMlineOfCode.h"
#include "label.h"

namespace toyc {

  class IFNE : public JVMinstruction, public JVMlineOfCode {
  public:
    label *l;

    IFNE(label*);
    std::string toString();
  };

}

#endif

