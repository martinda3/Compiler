#ifndef IFEQ_H
#define IFEQ_H

#include <iostream>
#include "JVMinstruction.h"
#include "JVMlineOfCode.h"
#include "label.h"

namespace toyc {

  class IFEQ : public JVMinstruction, public JVMlineOfCode {
  public:
    label *l;

    IFEQ(label*);
    std::string toString();
  };

}

#endif
