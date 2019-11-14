#include <iostream>
#include "JVMtargetCode.h"
#include "TCsymbol.h"
#include "TCtoken.h"

#include "JVMgenUtils.h"
#include "JVMtargetCode.h"

#include "TCsymbol.h"
#include "TCtoken.h"

#include "ISTORE_1.h"
#include "ISTORE_2.h"
#include "ISTORE_3.h"
#include "ISTORE.h"
#include "ILOAD_1.h"
#include "ILOAD_2.h"
#include "ILOAD_3.h"
#include "ILOAD.h"

#include "ASTORE_1.h"
#include "ASTORE_2.h"
#include "ASTORE_3.h"
#include "ASTORE.h"

#include "ALOAD_1.h"
#include "ALOAD_2.h"
#include "ALOAD_3.h"
#include "ALOAD.h"

#include "ICONST_M1.h"
#include "ICONST_0.h"
#include "ICONST_1.h"
#include "ICONST_2.h"
#include "ICONST_3.h"
#include "ICONST_4.h"
#include "ICONST_5.h"
#include "BIPUSH.h"
#include "SIPUSH.h"
#include "LDC.h"
#include "IADD.h"
#include "ISUB.h"
#include "IMUL.h"
#include "IDIV.h"
#include "IF_ICMPEQ.h"
#include "IF_ICMPNE.h"
#include "IF_ICMPLT.h"
#include "IF_ICMPLE.h"
#include "IF_ICMPGT.h"
#include "IF_ICMPGE.h"
#include "IFEQ.h"
#include "IFNE.h"
#include "GOTO.h"
#include "SWAP.h"
#include "POP.h"

#include "label.h"
#include "codeLabel.h"

namespace toyc {

  void JVMgenUtils::gen_ISTORE(TCsymbol id,JVMtargetCode *tc){
    int offset = id.getOffset();
    switch (offset) {
    case 1:  tc->add(new ISTORE_1()); break;
    case 2:  tc->add(new ISTORE_2()); break;
    case 3:  tc->add(new ISTORE_3()); break;
    default: tc->add(new ISTORE(offset)); 
    }

  }

  void JVMgenUtils::gen_ILOAD(TCsymbol id,JVMtargetCode *tc){ 
    int offset = id.getOffset();
    switch(offset){
    case 1:  tc->add(new ILOAD_1()); break;
    case 2:  tc->add(new ILOAD_2()); break;
    case 3:  tc->add(new ILOAD_3()); break;
    default: tc->add(new ILOAD(offset));
    }
  }

  void JVMgenUtils::gen_ASTORE(TCsymbol id,JVMtargetCode *tc){
    int offset = id.getOffset();
    switch (offset) {
    case 1:  tc->add(new ASTORE_1()); break;
    case 2:  tc->add(new ASTORE_2()); break;
    case 3:  tc->add(new ASTORE_3()); break;
    default: tc->add(new ASTORE(offset)); 
    }
  }
  
  void JVMgenUtils::gen_ALOAD(TCsymbol id,JVMtargetCode *tc){  
    int offset = id.getOffset();
    switch(offset){
    case 1:  tc->add(new ALOAD_1()); break;
    case 2:  tc->add(new ALOAD_2()); break;
    case 3:  tc->add(new ALOAD_3()); break;
    default: tc->add(new ALOAD(offset));
    }
  }

  void JVMgenUtils::gen_ICONST(int n,JVMtargetCode *tc){ 	
    switch(n){
    case -1: tc->add(new ICONST_M1()); break;
    case 0:  tc->add(new ICONST_0());  break;
    case 1:  tc->add(new ICONST_1());  break;
    case 2:  tc->add(new ICONST_2());  break;
    case 3:  tc->add(new ICONST_3());  break;
    case 4:  tc->add(new ICONST_4());  break;
    case 5:  tc->add(new ICONST_5());  break;
    default:
      if (n >= -128 && n <= 127)
        tc->add(new BIPUSH(n));
      else if (n >= -32768 && n <= 32767)
        tc->add(new SIPUSH(n));
      else tc->add(new LDC(n));
    }
  }

  void JVMgenUtils::gen_ADDOP(TCtoken tok, JVMtargetCode *tc) {
    if (tok.getLexeme()=="+")
      tc->add(new IADD());
    else if (tok.getLexeme()=="-")
      tc->add(new ISUB());
    else { // shouldn't happen
      std::cerr << "Error: gen_ADDOP: internal error" << std::endl;
      exit(EXIT_FAILURE);
    }
  }
 
  void JVMgenUtils::gen_MULOP(TCtoken tok, JVMtargetCode *tc) {
    if (tok.getLexeme()=="*")
      tc->add(new IMUL());
    else if (tok.getLexeme()=="/")
      tc->add(new IDIV());
    else { // shouldn't happen
      std::cerr << "Error: gen_MULOP: internal error" << std::endl;
      exit(EXIT_FAILURE);
    }
  }

  void JVMgenUtils::gen_RELOP(TCtoken tok, JVMtargetCode *tc) {
    label *l0 = new label(), *l1 = new label();
    if (tok.getLexeme()=="==")      tc->add(new IF_ICMPNE(l0));
    else if (tok.getLexeme()=="<>") tc->add(new IF_ICMPEQ(l0));
    else if (tok.getLexeme()=="<")  tc->add(new IF_ICMPGE(l0));
    else if (tok.getLexeme()=="<=") tc->add(new IF_ICMPGT(l0));
    else if (tok.getLexeme()==">")  tc->add(new IF_ICMPLE(l0));
    else if (tok.getLexeme()==">=") tc->add(new IF_ICMPLT(l0));
    else { // shouldn't happen
      std::cerr << "Error: gen_RELOP: internal error" << std::endl;
      exit(EXIT_FAILURE);
    }
    tc->add(new ICONST_1());
    tc->add(new GOTO(l1));
    tc->add(new codeLabel(l0->toString()+""));
    tc->add(new ICONST_0());
    tc->add(new codeLabel(l1->toString()+""));
  }
 

  void JVMgenUtils::gen_OR(TCtoken tok, JVMtargetCode *tc) {
    label *l0 = new label(), *l1 = new label(), *l2 = new label();
    tc->add(new SWAP());
    tc->add(new IFEQ(l0));
    tc->add(new POP());
    tc->add(new ICONST_1());
    tc->add(new GOTO(l2));
    tc->add(new codeLabel(l0->toString()));
    tc->add(new IFEQ(l1));
    tc->add(new ICONST_1());
    tc->add(new GOTO(l2));
    tc->add(new codeLabel(l1->toString()));
    tc->add(new ICONST_0());
    tc->add(new codeLabel(l2->toString()));
  }

  void JVMgenUtils::gen_AND(TCtoken tok, JVMtargetCode *tc) {
    label *l0 = new label(), *l1 = new label(), *l2 = new label();
    tc->add(new SWAP());
    tc->add(new IFNE(l0));
    tc->add(new POP());
    tc->add(new ICONST_0());
    tc->add(new GOTO(l2));
    tc->add(new codeLabel(l0->toString()));
    tc->add(new IFNE(l1));
    tc->add(new ICONST_0());
    tc->add(new GOTO(l2));
    tc->add(new codeLabel(l1->toString()));
    tc->add(new ICONST_1());
    tc->add(new codeLabel(l2->toString()));
  }

}


