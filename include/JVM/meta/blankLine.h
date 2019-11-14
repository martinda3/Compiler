#ifndef BLANKLINE_H
#define BLANKLINE_H

#include "JVMmeta.h"
#include "JVMlineOfCode.h"

namespace toyc {
  
class blankLine: public JVMmeta, public JVMlineOfCode{
 public:
  std::string toString();
};

}

#endif

