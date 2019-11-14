#ifndef JVMINSTRUCTION_H
#define JVMINSTRUCTION_H

namespace toyc {
  
class JVMinstruction{
 public:
  virtual std::string toString() = 0;
};
 
}
#endif
