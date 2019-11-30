#ifndef JVMGENERATEPROGRAM_H
#define JVMGENERATEPROGRAM_H

#include "CGtargetCode.h"
#include "JVMtargetCode.h"

#include "TCsymbol.h"
#include "TCsymTable.h"
#include "TCglobals.h"

#include "ASprogram.h"
#include "ASprog.h"
#include "ASstatement.h"
#include "ASwriteState.h"
#include "ASreadState.h"

namespace toyc {
  
class JVMgenerateProgram {
 public:
     static void genProgram(ASprog*,JVMtargetCode*);
     static void genIntro(JVMtargetCode*);
     static void genConstructor(JVMtargetCode*);
     static void genMainMethod(ASdefinition**,int,JVMtargetCode*);
     static void gen_intro_comments(std::string,std::string,JVMtargetCode*);
     static void gen_source_directive(std::string,JVMtargetCode*);
     static void gen_class_directive(std::string,JVMtargetCode*); 
     static void gen_super_directive(std::string,JVMtargetCode*);
     static void gen_main_header(JVMtargetCode*);
     static void gen_throws_directive(JVMtargetCode*);
     static bool thereIsInput(ASdefinition**,int);
     static bool thereIsOutput(ASdefinition**,int);
     static void gen_output_stream_store(JVMtargetCode*);
     static void gen_input_stream_store(JVMtargetCode*);
     static void gen_stack_limit_directive(JVMtargetCode*);
     static void gen_locals_limit_directive(JVMtargetCode*);    
    
};
 
}
#endif
