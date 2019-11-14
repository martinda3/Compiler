#ifndef IF_ICMPEQ_H
#define IF_ICMPEQ_H

#include <iostream>
#include "JVMinstruction.h"
#include "JVMlineOfCode.h"
#include "label.h"

namespace toyc {

  class IF_ICMPEQ : public JVMinstruction, public JVMlineOfCode {
  public:
    label *l;

    IF_ICMPEQ(label*);
    std::string toString();
  };

}

#endif
