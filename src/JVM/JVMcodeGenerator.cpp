#include <iostream>
#include "ASabstractSyntax.h"
#include "ASprogram.h"
#include "ASprog.h"
#include "CGtargetCode.h"
#include "JVMtargetCode.h"
#include "JVMcodeGenerator.h"
#include "JVMgenerateProgram.h"

namespace toyc{

  JVMcodeGenerator::JVMcodeGenerator() { tc = new JVMtargetCode(); }
  CGtargetCode* JVMcodeGenerator::generateCode(ASabstractSyntax *ast) {
    ASprog *p = dynamic_cast<ASprog*>(ast);
    JVMgenerateProgram::genProgram(p,tc);
    return (CGtargetCode *)tc;
  }

}
