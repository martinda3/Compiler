#ifndef SOURCE_H
#define SOURCE_H

#include "JVMlineOfCode.h"
#include "JVMdirective.h"

namespace toyc {

class source: public JVMdirective, public JVMlineOfCode {
public: 
 std::string directive;
 std::string fileName;

 source(std::string);
 std::string toString();
};

}

#endif
