#ifndef ASEXPR_H
#define ASEXPR_H

#include "ASabstractSyntax.h"

namespace toyc {

    class ASexpr : public ASabstractSyntax {
    public:
        virtual std::string toString() = 0;
    };

}
#endif
