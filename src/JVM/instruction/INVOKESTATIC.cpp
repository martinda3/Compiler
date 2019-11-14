#include <iostream>
#include "INVOKESTATIC.h"

namespace toyc {

  INVOKESTATIC::INVOKESTATIC(std::string n, std::string t) {
    name = n; type = t; numArgs = 0;
  }

  void INVOKESTATIC::addArg(std::string arg) {
    if(numArgs==MAX_INVOKESTATIC_ARGS) {
      printf("INTERNAL ERROR: too many args for INVOKESTATIC\n");
      exit(EXIT_FAILURE);
    }
    args[numArgs++] = arg;
  }

  std::string INVOKESTATIC::toString() {
    std::string s = "\tinvokestatic " + name + "(";
    if (numArgs != 0)
      for (int i=0; i<numArgs; i++)
        s += args[i];
    s += ")" + type;
    return s;
  }
  
}


