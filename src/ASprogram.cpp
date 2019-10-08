
#include <iostream>

#include "ASprogram.h"
#include "TCoutput.h"

namespace toyc {

    ASprogram::ASprogram(std::string n, ASstatement *statements[], int num) {
        for (int i = 0; i < num; i++) statementList[i] = statements[i];
        name = n;
        numStatements = num;
    }

    std::string ASprogram::getName() { return name; }

    ASstatement *ASprogram::getStatement(int n) { return statementList[n]; }

    int ASprogram::getNumStatements() { return numStatements; }

    std::string ASprogram::toString() {
        if (numStatements == 0) return "prog([])";
        std::string s = "prog(\n";
        indent();
        s += spaces() + name + ",\n";
        s += spaces() + "[\n";
        indent();
        if (numStatements > 0) {
            s += (spaces() + statementList[0]->toString());
            for (int i = 1; i < numStatements; i++)
                s += ",\n" + spaces() + statementList[i]->toString();
        }
        outdent();
        s += "\n" + spaces() + "]\n";
        outdent();
        s += spaces() + ")\n";
        return s;
    }

}
