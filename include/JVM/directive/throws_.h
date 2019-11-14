#ifndef THROWS_H
#define THROWS_H

#include "JVMlineOfCode.h"
#include "JVMdirective.h"

namespace toyc {

class throws_: public JVMdirective, public JVMlineOfCode {
public: 
 std::string directive;
 std::string exception;

 throws_(std::string);
 std::string toString();
};

}

#endif
