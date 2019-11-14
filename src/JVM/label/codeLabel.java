package codegen.JVM.label;

import compilers.LineOfCode;
import codegen.JVM.JVMlabel;

public class codeLabel implements JVMlabel, LineOfCode {
    private String name;

    public codeLabel(String name) { this.name = name; }
  
    public String toString() { return name + ":"; }
}
