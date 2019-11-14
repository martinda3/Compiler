#ifndef SOURCEFILECOMMENT_H
#define SOURCEFILECOMMENT_H

#include "JVMlineOfCode.h"
#include "JVMmeta.h"

namespace toyc {
  class sourceFileComment: public JVMmeta, public JVMlineOfCode{
  public:
    std::string source;

    sourceFileComment(std::string s);
    std::string toString();
  };
}

#endif
