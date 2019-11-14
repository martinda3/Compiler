#ifndef CLASS_H
#define CLASS_H

#include "JVMlineOfCode.h"
#include "JVMdirective.h"

namespace toyc {

class class_: public JVMdirective, public JVMlineOfCode {
public: 
 std::string directive;
 std::string className;
 std::string accessSpecs[20];
 int accessSize;
 
 class_(std::string);
 void addAccessSpec(std::string);
 std::string toString();
};

}

#endif
