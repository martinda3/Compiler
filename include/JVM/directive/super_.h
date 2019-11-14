#ifndef SUPER_H
#define SUPER_H

#include "JVMlineOfCode.h"
#include "JVMdirective.h"

namespace toyc {

class super_: public JVMdirective, public JVMlineOfCode {
public: 
 std::string directive;
 std::string parent;

 super_(std::string);
 std::string toString();
};

}

#endif
