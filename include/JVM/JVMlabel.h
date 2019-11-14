#ifndef JVMLABEL_H
#define JVMLABEL_H

namespace toyc {
  
class JVMlabel{
 public:
  virtual std::string toString() = 0;
  virtual std::string getLabel() = 0;
};
 
}
#endif
