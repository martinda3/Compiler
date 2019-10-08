#ifndef ASPROGRAM_H
#define ASPROGRAM_H

#include "ASabstractSyntax.h"
#include "ASstatement.h"

#define MAX_STATEMENTS 500 // arbitrary

namespace toyc {

    class ASprogram : public ASabstractSyntax {
    public:
        ASprogram(std::string, ASstatement *[], int);

        std::string toString();

        std::string getName();

        ASstatement *getStatement(int);

        int getNumStatements();

    private:
        ASstatement *statementList[MAX_STATEMENTS];
        std::string name;
        int numStatements;
    };

}
#endif
