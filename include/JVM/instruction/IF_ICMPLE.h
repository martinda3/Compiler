#ifndef IF_ICMPLE_H
#define IF_ICMPLE_H

#include <iostream>
#include "JVMinstruction.h"
#include "JVMlineOfCode.h"
#include "label.h"

namespace toyc {

  class IF_ICMPLE : public JVMinstruction, public JVMlineOfCode {
  public:
    label *l;

    IF_ICMPLE(label*);
    std::string toString();
  };

}

#endif
