#ifndef JVMGENERATEEXPRESSION_H
#define JVMGENERATEEXPRESSION_H

#include "ASexpr.h"
#include "JVMtargetCode.h"

namespace toyc {

  class JVMgenerateExpression {
  public:
    static void genExpression(ASexpression*,JVMtargetCode*);
  };

}

#endif
