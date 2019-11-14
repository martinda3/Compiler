#ifndef TARGETFILECOMMENT_H
#define TARGETFILECOMMENT_H

#include "JVMlineOfCode.h"
#include "JVMmeta.h"

namespace toyc {
  class targetFileComment: public JVMmeta, public JVMlineOfCode{
  public:
    std::string target;

    targetFileComment(std::string s);
    std::string toString();
  };
}

#endif
