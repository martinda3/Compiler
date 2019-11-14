#ifndef IF_ICMPGT_H
#define IF_ICMPGT_H

#include <iostream>
#include "JVMinstruction.h"
#include "JVMlineOfCode.h"
#include "label.h"

namespace toyc {

  class IF_ICMPGT : public JVMinstruction, public JVMlineOfCode {
  public:
    label *l;

    IF_ICMPGT(label*);
    std::string toString();
  };

}

#endif
