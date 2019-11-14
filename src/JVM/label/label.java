package codegen.JVM.label;

import compilers.LineOfCode;
import codegen.JVM.JVMlabel;
import codegen.JVM.JVMgenGlobals;
import codegen.JVM.JVMgenUtils;

public class label implements JVMlabel, LineOfCode{
  private String l;

  public label(){
    l = JVMgenGlobals.LABELTAG +
         JVMgenUtils.getUniqueInt();
  }

  public label(String s) { l = s; }

  public String getLabel() { return l; }

  public String toString() { return l; }
}
