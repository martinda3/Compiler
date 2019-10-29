/*

   EGRE 591 Compiler Construction
   Abstract Syntax: Charles Dieztel
   Modifed By: Dajion Martin

 */

#ifndef ASFUNCDEF_H
#define ASFUNCDEF_H

#include "ASdefinition.h"
#include "ASexpression.h"
#include "AStype.h"
#include "ASdefinition.h"
#include "ASstatement.h"

#define MAX_STATEMENTS 500 // arbitrary

namespace toyc
{

	class ASfuncDef : public ASdefinition
	{
	public:
		ASfuncDef(AStype*, ASdefinition* [], int, ASstatement*);

		AStype* getIdentifier();
		ASdefinition* getVarDef(int);
		ASstatement* getStatement();
		std::string toString();
		int getNumVarDef();

	private:
		AStype* identifier;
		ASdefinition* varDefList[MAX_STATEMENTS];
		int numVarDef;
		ASstatement* statement;
	};

}
#endif
