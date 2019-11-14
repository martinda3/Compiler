#ifndef IF_ICMPLT_H
#define IF_ICMPLT_H

#include <iostream>
#include "JVMinstruction.h"
#include "JVMlineOfCode.h"
#include "label.h"

namespace toyc {

  class IF_ICMPLT : public JVMinstruction, public JVMlineOfCode {
  public:
    label *l;

    IF_ICMPLT(label*);
    std::string toString();
  };

}

#endif


