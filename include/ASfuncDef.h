#ifndef ASFUNCDEF_H
#define ASFUNCDEF_H

#include "ASdefinition.h"
#include "ASexpression.h"
#include "AStype.h"
#include "ASvarDef.h"
#include "ASstatement.h"

#define MAX_STATEMENTS 500 // arbitrary

namespace toyc
{

	class ASfuncDef : public ASdefinition
	{
	public:
		ASfuncDef(ASexpression*, AStype*, ASvarDef* [], int, ASstatement*);

		ASexpression* getIdentifier();
		AStype* getType();
		ASvarDef* getVarDef(int);
		ASstatement* getStatement();
		std::string toString();
		int getNumVarDef();

	private:
		ASexpression* identifier;
		AStype* type;
		ASvarDef* varDefList[MAX_STATEMENTS];
		int numVarDef;
		ASstatement* statement;
	};

}
#endif
