/*

   EGRE 591 Compiler Construction
   Abstract Syntax: Charles Dieztel

 */

#ifndef ASREADSTATE_H
#define ASREADSTATE_H

#include "ASstatement.h"
#include "ASexpression.h"

#define MAX_STATEMENTS 500 // arbitrary

namespace toyc
{

	class ASreadState : public ASstatement
	{
	public:
		ASreadState(ASexpression* [], int);

		ASexpression* getIdentifier(int);
		std::string toString();
		int getNumIdentifiers();

	private:
		ASexpression* identifierList[MAX_STATEMENTS];
		int numIdentifiers;
	};

}
#endif
