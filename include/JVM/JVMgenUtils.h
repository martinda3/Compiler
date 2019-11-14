#ifndef JVMGENUTILS_H
#define JVMGENUTILS_H

#include "TCsymbol.h"
#include "TCtoken.h"
#include "JVMtargetCode.h"

namespace toyc {

  class JVMgenUtils {
  public:
    static int uniqueInt; // is initialized to 0 by system
    
    static void gen_ISTORE(TCsymbol,JVMtargetCode*);
    static void gen_ILOAD(TCsymbol,JVMtargetCode*);
    static void gen_ASTORE(TCsymbol,JVMtargetCode*);
    static void gen_ALOAD(TCsymbol,JVMtargetCode*);
    static void gen_ICONST(int,JVMtargetCode*);
    static void gen_ADDOP(TCtoken,JVMtargetCode*);
    static void gen_MULOP(TCtoken,JVMtargetCode*);
    static void gen_RELOP(TCtoken,JVMtargetCode*);
    static void gen_OR(TCtoken,JVMtargetCode*);
    static void gen_AND(TCtoken,JVMtargetCode*);
    static int getUniqueInt() { return uniqueInt++; }

  };
}

#endif
