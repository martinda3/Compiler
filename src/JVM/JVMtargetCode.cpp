#include <iostream>
#include <fstream>
#include <stdlib.h>
#include "JVMtargetCode.h"
#include "CGlineOfCode.h"
#include "JVMlineOfCode.h"

#define MAXLINES 500

namespace toyc{

  JVMtargetCode::JVMtargetCode() {
    size = 0;
  }
   
  void JVMtargetCode::add(CGlineOfCode* l) {
    if(size >= MAXLINES) {
      std::cerr << "Error - too many JVM instructions" << std::endl;
      exit(EXIT_FAILURE);
    }
    code[size++] = (JVMlineOfCode *)l;
  }

  CGlineOfCode *JVMtargetCode::getLineOfCode(int i) {
    return code[i];
  }
  
  void JVMtargetCode::writeCode(CGtargetCode * code, std::string fname){
    std::ofstream out;
    out.open(fname);
    for(int i = 0; i < code->getSize(); i++)
      out << code->getLineOfCode(i)->toString() << std::endl;
    out.close();
  }
  
  int JVMtargetCode::getSize() { return size; }
  

  
  std::string JVMtargetCode::toString() {
    return "";
  }

}
