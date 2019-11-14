#ifndef IF_ICMPNE_H
#define IF_ICMPNE_H

#include <iostream>
#include "JVMinstruction.h"
#include "JVMlineOfCode.h"
#include "label.h"

namespace toyc {

  class IF_ICMPNE : public JVMinstruction, public JVMlineOfCode {
  public:
    label *l;

    IF_ICMPNE(label*);
    std::string toString();
  };

}

#endif

