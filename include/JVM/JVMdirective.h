#ifndef JVMDIRECTIVE_H
#define JVMDIRECTIVE_H

namespace toyc {

  class JVMdirective {
  public:
    virtual std::string toString() = 0;
  };

}
 
#endif
