#ifndef CGTARGETCODE_H
#define CGTARGETCODE_H

#include "CGlineOfCode.h"

namespace toyc {
  
  class CGtargetCode {
  public:
    virtual void add(CGlineOfCode *) = 0;
    virtual CGlineOfCode *getLineOfCode(int) = 0;
    virtual int getSize() = 0;
    virtual std::string toString() = 0;
    virtual void writeCode(CGtargetCode*,std::string) = 0;
  };

}
#endif
