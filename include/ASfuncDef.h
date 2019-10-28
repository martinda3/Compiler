#ifndef ASFUNCDEF_H
#define ASFUNCDEF_H

#include "ASdefinition.h"
#include "ASsimpleExpr.h"
#include "AStype.h"
#include "ASvarDef.h"
#include "ASstatement.h"

#define MAX_STATEMENTS 500 // arbitrary

namespace toyc
{

	class ASfuncDef : public ASdefinition
	{
	public:
		ASfuncDef(ASsimpleExpr*, AStype*, ASvarDef* [], int, ASstatement*);

		ASsimpleExpr* getIdentifier();
		AStype* getType();
		ASvarDef* getVarDef(int);
		ASstatement* getStatement();
		std::string toString();
		int getNumVarDef();

	private:
		ASsimpleExpr* identifier;
		AStype* type;
		ASvarDef* varDefList[MAX_STATEMENTS];
		int numVarDef;
		ASstatement* statement;
	};

}
#endif
