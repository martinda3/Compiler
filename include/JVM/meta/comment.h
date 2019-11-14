#ifndef COMMENT_H
#define COMMENT_H

#include "JVMlineOfCode.h"
#include "JVMmeta.h"

namespace toyc {
  class comment: public JVMmeta, public JVMlineOfCode{
  public:
    std::string text;

    comment(std::string s);
    std::string toString();
  };
}

#endif
