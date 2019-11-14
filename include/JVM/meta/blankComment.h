#ifndef BLANKCOMMENT_H
#define BLANKCOMMENT_H

#include "JVMlineOfCode.h"
#include "JVMmeta.h"

namespace toyc {
  
  class blankComment: public JVMmeta, public JVMlineOfCode {
    std::string toString();
  };

}

#endif
