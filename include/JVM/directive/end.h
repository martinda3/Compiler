#ifndef END_H
#define END_H

#include "JVMlineOfCode.h"
#include "JVMdirective.h"

namespace toyc {

  class end : public JVMlineOfCode, JVMdirective {
  public:
    std::string directive;

    end();
    std::string toString();
  };
}

#endif
