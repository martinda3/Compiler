#include <iostream>

#include "ASskipState.h"

namespace toyc {
    ASskipState::ASskipState() { setType(SKIPstate); }

    std::string ASskipState::toString() { return "skip()"; }

}
