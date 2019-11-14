#ifndef GOTO_H
#define GOTO_H

#include <iostream>
#include "JVMinstruction.h"
#include "JVMlineOfCode.h"
#include "label.h"

namespace toyc {

  class GOTO : public JVMinstruction, public JVMlineOfCode {
  public:
    label *l;

    GOTO(label*);
    std::string toString();
  };

}

#endif
