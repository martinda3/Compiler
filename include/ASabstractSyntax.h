/*

   EGRE 591 Compiler Construction
   Created By: Dan Relser
   Mostly unmodified

 */

#ifndef ASABSTRACTSYNTAX_H
#define ASABSTRACTSYNTAX_H

namespace toyc {

    class ASabstractSyntax {
    public:
        virtual std::string toString() = 0;
    };

}
#endif
