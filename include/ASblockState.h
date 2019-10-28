#ifndef ASBLOCKSTATE_H
#define ASBLOCKSTATE_H

#include "ASstatement.h"
#include "ASsimpleExpr.h"
#include "AStype.h"
#include "ASdefinition.h"

#define MAX_STATEMENTS 500 // arbitrary

namespace toyc
{

	class ASblockState : public ASstatement
	{
	public:
		ASblockState(ASdefinition* [], int, ASstatement* [], int);

		ASdefinition* getVarDef(int);
		ASstatement* getStatement(int);
		std::string toString();
		int getNumVarDef();
		int getNumStatement();

	private:
		ASdefinition* varDefList[MAX_STATEMENTS];
		int numVarDef;
		ASstatement* statementList[MAX_STATEMENTS];
		int numStatements;
	};

}
#endif
