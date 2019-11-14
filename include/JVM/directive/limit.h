#ifndef LIMIT_H
#define LIMIT_H

#include "JVMlineOfCode.h"
#include "JVMdirective.h"

namespace toyc {
  /*
public class limit implements JVMdirective, LineOfCode {
    private static final String directive = ".limit";
    public String type;
    public int size;

  public limit(String type, int size){
    this.type = type; this.size = size;
  }

  public String toString(){
    String s = "\t" + directive + " " + type + " " + size;
    return s;
  }
*/  
  class limit : public JVMlineOfCode, JVMdirective {
  public:
    std::string directive;
    std::string type;
    int size;
    
    limit(std::string,int);
    std::string toString();
  };
}

#endif
