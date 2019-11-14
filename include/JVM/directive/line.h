#ifndef LINE_H
#define LINE_H

#include "JVMlineOfCode.h"
#include "JVMdirective.h"

namespace toyc {

    class line : public JVMlineOfCode, JVMdirective {
    public:
        std::string directive;

        line(int);
        std::string toString();
    };
}


#endif
