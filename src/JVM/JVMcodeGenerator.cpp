#include <iostream>
#include "ASabstractSyntax.h"
#include "ASprogram.h"
#include "CGtargetCode.h"
#include "JVMtargetCode.h"
#include "JVMcodeGenerator.h"
#include "JVMgenerateProgram.h"

namespace toyc{

  JVMcodeGenerator::JVMcodeGenerator() { tc = new JVMtargetCode(); }
  CGtargetCode* JVMcodeGenerator::generateCode(ASabstractSyntax *ast) {
    ASprogram *p = dynamic_cast<ASprogram*>(ast);
    JVMgenerateProgram::genProgram(p,tc);
    return (CGtargetCode *)tc;
  }

}
