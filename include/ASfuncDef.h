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
		ASfuncDef(ASexpression*, AStype*, ASdefinition* [], int, ASstatement*);

		ASexpression* getIdentifier();
		AStype* getType();
		ASdefinition* getVarDef(int);
		ASstatement* getStatement();
		std::string toString();
		int getNumVarDef();

	private:
		ASexpression* identifier;
		AStype* type;
		ASdefinition* varDefList[MAX_STATEMENTS];
		int numVarDef;
		ASstatement* statement;
	};

}
#endif
